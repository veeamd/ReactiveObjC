//
//  NSObject+RACPropertySubscribing.m
//  ReactiveObjC
//
//  Created by Josh Abernathy on 3/2/12.
//  Copyright (c) 2012 GitHub, Inc. All rights reserved.
//

#import "NSObject+RACPropertySubscribing.h"
#import <ReactiveObjC/EXTScope.h>
#import <ReactiveObjC/KVObserver.h>
#import "NSObject+RACDeallocating.h"
#import "NSObject+RACDescription.h"
#import "NSObject+RACKVOWrapper.h"
#import "RACCompoundDisposable.h"
#import "RACDisposable.h"
#import "RACKVOTrampoline.h"
#import "RACSubscriber.h"
#import "RACSignal+Operations.h"
#import "RACTuple.h"
#import <libkern/OSAtomic.h>

@implementation NSObject (RACPropertySubscribing)

- (RACSignal *)rac_valuesForKeyPath:(NSString *)keyPath observer:(__weak NSObject *)observer {
	return [[[self
		rac_valuesAndChangesForKeyPath:keyPath options:NSKeyValueObservingOptionInitial observer:observer]
		map:^(RACTuple *value) {
			// -map: because it doesn't require the block trampoline that -reduceEach: uses
			return value[0];
		}]
		setNameWithFormat:@"RACObserve(%@, %@)", RACDescription(self), keyPath];
}

- (RACSignal *)rac_valuesAndChangesForKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options observer:(__weak NSObject *)weakObserver {
	NSObject *strongObserver = weakObserver;

	RACSignal *selfDealloc = self.rac_willDeallocSignal;
	RACSignal *observerDealloc = strongObserver.rac_willDeallocSignal ?: [RACSignal never];

	return [[[RACSignal createSignal:^RACDisposable *(id<RACSubscriber> subscriber) {
		PMKVObserver *observer = [PMKVObserver
				observeObject:self observer:weakObserver keyPath:keyPath options:options | NSKeyValueObservingOptionNew
								block:^(id  _Nonnull observer, id  _Nonnull object, NSDictionary<NSKeyValueChangeKey, id> * _Nullable change, PMKVObserver * _Nonnull kvo) {
									id value;
									if ([change[NSKeyValueChangeKindKey] isEqualToNumber:@(NSKeyValueChangeSetting)]) {
										value = change[NSKeyValueChangeNewKey];
									} else {
										value = [object valueForKeyPath:keyPath];
									}
									RACTuple *tuple = [RACTwoTuple pack:value :change];
									[subscriber sendNext:tuple];
								}];

		return [RACDisposable disposableWithBlock:^{
			[observer cancel];
		}];
	}]
	takeUntil:[RACSignal zip:@[selfDealloc, observerDealloc]]]
	setNameWithFormat:@"%@ -rac_valueAndChangesForKeyPath: %@ options: %lu observer: %@", RACDescription(self), keyPath, (unsigned long)options, RACDescription(strongObserver)];
}

@end
