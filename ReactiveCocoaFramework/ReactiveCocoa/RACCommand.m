//
//  RACCommand.m
//  ReactiveCocoa
//
//  Created by Josh Abernathy on 3/3/12.
//  Copyright (c) 2012 GitHub, Inc. All rights reserved.
//

#import "RACCommand.h"
#import "EXTScope.h"
#import "RACMulticastConnection.h"
#import "RACReplaySubject.h"
#import "RACScheduler.h"
#import "RACSignal+Operations.h"
#import "RACSubject.h"
#import "RACSubscriptingAssignmentTrampoline.h"
#import <libkern/OSAtomic.h>

@interface RACCommand () {
	RACSubject *_errors;

	// How many -execute: calls and signals are currently in-flight.
	//
	// This variable must only be read from the main thread, and should only be
	// modified through -incrementItemsInFlight and -decrementItemsInFlight.
	NSUInteger _itemsInFlight;
}

@property (atomic, assign, readwrite) BOOL canExecute;

// A signal of the values passed to -execute:.
//
// Subscriptions to the receiver will actually be redirected to this subject.
@property (nonatomic, strong, readonly) RACSubject *values;

// Improves the performance of KVO on the receiver.
//
// See the documentation for <NSKeyValueObserving> for more information.
@property (atomic) void *observationInfo;

// Increments _itemsInFlight.
- (void)incrementItemsInFlight;

// Decrements _itemsInFlight.
- (void)decrementItemsInFlight;

@end

@implementation RACCommand

#pragma mark Properties

- (BOOL)isExecuting {
	return _itemsInFlight > 0;
}

- (void)incrementItemsInFlight {
	[self willChangeValueForKey:@keypath(self.executing)];
	_itemsInFlight++;
	[self didChangeValueForKey:@keypath(self.executing)];
}

- (void)decrementItemsInFlight {
	NSCAssert(_itemsInFlight > 0, @"Unbalanced decrement of itemsInFlight");

	[self willChangeValueForKey:@keypath(self.executing)];
	_itemsInFlight--;
	[self didChangeValueForKey:@keypath(self.executing)];
}

- (NSString *)name {
	return self.values.name;
}

- (void)setName:(NSString *)name {
	self.values.name = name;
}

#pragma mark Lifecycle

- (void)dealloc {
	RACSubject *valuesSubject = _values;
	RACSubject *errorsSubject = _errors;

	void (^sendCompleted)() = ^{
		[valuesSubject sendCompleted];
		[errorsSubject sendCompleted];
	};

	// Make sure that all signal events are on the main thread, even if -dealloc
	// is called in the background.
	if (RACScheduler.currentScheduler == RACScheduler.mainThreadScheduler) {
		sendCompleted();
	} else {
		[RACScheduler.mainThreadScheduler schedule:sendCompleted];
	}
}

+ (instancetype)command {
	return [self commandWithCanExecuteSignal:nil];
}

+ (instancetype)commandWithCanExecuteSignal:(RACSignal *)canExecuteSignal {
	return [[self alloc] initWithCanExecuteSignal:canExecuteSignal];
}

- (id)init {
	return [self initWithCanExecuteSignal:nil];
}

- (id)initWithCanExecuteSignal:(RACSignal *)canExecuteSignal {
	self = [super init];
	if (self == nil) return nil;

	_values = [RACSubject subject];
	_errors = [RACSubject subject];

	RAC(self.canExecute) = [RACSignal
		combineLatest:@[
			[canExecuteSignal startWith:@YES] ?: [RACSignal return:@YES],
			RACAbleWithStart(self.allowsConcurrentExecution),
			RACAbleWithStart(self.executing)
		] reduce:^(NSNumber *canExecute, NSNumber *allowsConcurrency, NSNumber *executing) {
			BOOL blocking = !allowsConcurrency.boolValue && executing.boolValue;
			return @(canExecute.boolValue && !blocking);
		}];

	return self;
}

#pragma mark Execution

- (RACSignal *)addActionBlock:(RACSignal * (^)(id value))signalBlock {
	NSCParameterAssert(signalBlock != nil);

	@weakify(self);

	return [[[[self.values
		doNext:^(id _) {
			@strongify(self);
			[self incrementItemsInFlight];
		}]
		map:^(id value) {
			RACSignal *signal = signalBlock(value);
			NSCAssert(signal != nil, @"signalBlock returned a nil signal");

			RACMulticastConnection *connection = [signal multicast:[RACReplaySubject subject]];
			[connection connect];

			// Handle completion and error on the main thread.
			[[[connection.signal
				deliverOn:RACScheduler.mainThreadScheduler]
				finally:^{
					@strongify(self);
					[self decrementItemsInFlight];
				}]
				subscribeError:^(NSError *error) {
					@strongify(self);
					if (self != nil) [self->_errors sendNext:error];
				}];

			return [connection.signal catchTo:[RACSignal empty]];
		}]
		replayLast]
		setNameWithFormat:@"[%@] -addActionBlock:", self.name];
}

- (BOOL)execute:(id)value {
	if (!self.canExecute) return NO;

	[self incrementItemsInFlight];
	@onExit {
		[self decrementItemsInFlight];
	};

	[self.values sendNext:value];
	return YES;
}

#pragma mark RACSignal

- (RACDisposable *)subscribe:(id<RACSubscriber>)subscriber {
	return [self.values subscribe:subscriber];
}

#pragma mark NSKeyValueObserving

+ (BOOL)automaticallyNotifiesObserversForKey:(NSString *)key {
	// This key path is notified manually when _itemsInFlight is modified.
	if ([key isEqualToString:@keypath(RACCommand.new, executing)]) return NO;

	return [super automaticallyNotifiesObserversForKey:key];
}

@end

@implementation RACCommand (Deprecated)

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-implementations"

- (RACSignal *)addSignalBlock:(RACSignal * (^)(id value))signalBlock {
	NSCParameterAssert(signalBlock != nil);

	@weakify(self);

	return [[[[self.values
		doNext:^(id _) {
			@strongify(self);
			[self incrementItemsInFlight];
		}]
		map:^(id value) {
			RACSignal *signal = signalBlock(value);
			NSCAssert(signal != nil, @"signalBlock returned a nil signal");

			return [[[signal
				doError:^(NSError *error) {
					[RACScheduler.mainThreadScheduler schedule:^{
						@strongify(self);
						if (self != nil) [self->_errors sendNext:error];
					}];
				}]
				finally:^{
					@strongify(self);
					[self decrementItemsInFlight];
				}]
				replay];
		}]
		replayLast]
		setNameWithFormat:@"[%@] -addSignalBlock:", self.name];
}

#pragma clang diagnostic pop

@end
