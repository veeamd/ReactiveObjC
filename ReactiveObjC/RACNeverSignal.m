//
//  RACNeverSignal.m
//  ReactiveObjC-macOS
//
//  Created by Yaron Inger on 19/12/2018.
//  Copyright (c) 2018 GitHub, Inc. All rights reserved.
//

#import "RACNeverSignal.h"

#import <ReactiveObjC/EXTScope.h>

#import "RACCompoundDisposable.h"
#import "RACSubscriber.h"

@implementation RACNeverSignal

+ (RACSignal *)never {
  return [[[self alloc] init] setNameWithFormat:@"+never"];
}

- (nullable RACDisposable *)subscribe:(id<RACSubscriber>)subscriber {
  NSCParameterAssert(subscriber != nil);

  RACCompoundDisposable *disposable = [RACCompoundDisposable compoundDisposable];

  [disposable addDisposable:[RACDisposable disposableWithBlock:^{
    // Strongly hold the subscriber until the subscription is disposed. This is required since the
    // subscriber disposes its disposable on dealloc which will terminate the subscription to this
    // signal.
    id<RACSubscriber> __unused retainedSubscriber = subscriber;
  }]];

  [subscriber didSubscribeWithDisposable:disposable];

  return disposable;
}

@end
