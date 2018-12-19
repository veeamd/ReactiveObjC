//
//  RACNeverSignalSpec.m
//  ReactiveObjC
//
//  Created by Yaron Inger on 20/12/2018.
//  Copyright (c) 2018 GitHub, Inc. All rights reserved.
//

@import Quick;
@import Nimble;

#import "RACDisposable.h"
#import "RACNeverSignal.h"
#import "RACSubscriber+Private.h"

#import "RACSignal+Operations.h"

QuickSpecBegin(RACNeverSignalSpec)

qck_it(@"should not send next, completed or err", ^{
  RACSignal *signal = [RACNeverSignal never];

  __block BOOL sentEvent = NO;
  [signal subscribeNext:^(id _Nullable x) {
    sentEvent = YES;
  } error:^(NSError *_Nullable error) {
    sentEvent = YES;
  } completed:^{
    sentEvent = YES;
  }];

  expect(@(sentEvent)).to(beFalsy());
});

qck_it(@"should not dispose disposable on signal dealloc", ^{
  RACDisposable *disposable;

  @autoreleasepool {
    RACSignal *signal = [RACNeverSignal never];
    disposable = [signal subscribeNext:^(id _Nullable x) {}];
  }

  expect(@(disposable.isDisposed)).to(beFalsy());

  [disposable dispose];
});

qck_it(@"should not dispose disposable if returned disposable is weakly held", ^{
  __weak RACDisposable *disposable;

  @autoreleasepool {
    RACSignal *signal = [RACNeverSignal never];
    disposable = [signal subscribeNext:^(id _Nullable x) {}];
  }

  expect(disposable).notTo(beNil());
  expect(@(disposable.isDisposed)).to(beFalsy());

  [disposable dispose];
});

qck_it(@"should not deallocate subscriber if the disposable is not disposed", ^{
  RACSignal *signal = [RACNeverSignal never];

  RACDisposable *disposable;
  __weak RACSubscriber *weakSubscriber;

  @autoreleasepool {
    RACSubscriber *subscriber = [[RACSubscriber alloc] init];
    disposable = [signal subscribe:subscriber];

    weakSubscriber = subscriber;
  }

  expect(weakSubscriber).notTo(beNil());

  [disposable dispose];
});

qck_it(@"should not deallocate subscriber if the signal is deallocated", ^{
  __weak RACSubscriber *weakSubscriber;
  RACDisposable *disposable;

  @autoreleasepool {
    RACSignal *signal = [RACNeverSignal never];
    RACSubscriber *subscriber = [[RACSubscriber alloc] init];
    disposable = [signal subscribe:subscriber];

    weakSubscriber = subscriber;
  }

  expect(weakSubscriber).notTo(beNil());

  [disposable dispose];
});

qck_it(@"should deallocate subscriber on subscription disposal", ^{
  RACSignal *signal = [RACNeverSignal never];

  __weak RACSubscriber *weakSubcriber;
  @autoreleasepool {
    RACSubscriber *subscriber = [RACSubscriber subscriberWithNext:^(id x) {
    } error:^(NSError *error) {
    } completed:^{
    }];

    weakSubcriber = subscriber;

    [[signal subscribe:subscriber] dispose];
  }

  expect(weakSubcriber).to(beNil());
});

QuickSpecEnd
