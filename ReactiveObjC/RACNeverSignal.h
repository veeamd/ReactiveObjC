//
//  RACNeverSignal.h
//  ReactiveObjC
//
//  Created by Yaron Inger on 19/12/2018.
//  Copyright (c) 2018 GitHub, Inc. All rights reserved.
//

#import "RACSignal.h"

NS_ASSUME_NONNULL_BEGIN

// A private `RACSignal` subclasses that never completes, errs or sends a value to any subscriber.
@interface RACNeverSignal<__covariant ValueType> : RACSignal<ValueType>

/// Creates a new `RACNeverSignal`.
+ (RACSignal<ValueType> *)never;

@end

NS_ASSUME_NONNULL_END
