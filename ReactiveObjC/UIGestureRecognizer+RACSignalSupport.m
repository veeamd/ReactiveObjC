//
//  UIGestureRecognizer+RACSignalSupport.m
//  ReactiveObjC
//
//  Created by Josh Vera on 5/5/13.
//  Copyright (c) 2013 GitHub. All rights reserved.
//

#import "UIGestureRecognizer+RACSignalSupport.h"
#import <ReactiveObjC/EXTScope.h>
#import "NSObject+RACDeallocating.h"
#import "NSObject+RACDescription.h"
#import "RACCompoundDisposable.h"
#import "RACDisposable.h"
#import "RACSignal.h"
#import "RACSubscriber.h"

@implementation UIGestureRecognizer (RACSignalSupport)

- (RACSignal *)rac_gestureSignal {
  @rac_weakify(self);

  return [[RACSignal
    createSignal:^(id<RACSubscriber> subscriber) {
      @rac_strongify(self);

      [self addTarget:subscriber action:@selector(sendNext:)];
      [self.rac_deallocDisposable addDisposable:[RACDisposable disposableWithBlock:^{
        [subscriber sendCompleted];
      }]];

      return [RACDisposable disposableWithBlock:^{
        @rac_strongify(self);
        [self removeTarget:subscriber action:@selector(sendNext:)];
      }];
    }]
    setNameWithFormat:@"%@ -rac_gestureSignal", RACDescription(self)];
}

@end
