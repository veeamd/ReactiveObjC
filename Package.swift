// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "ReactiveObjC",
    platforms: [.iOS(.v13)],
    products: [
        .library(name: "ReactiveObjC", targets: ["ReactiveObjC-iOS"])
    ],
    targets: [
        .target(name: "ReactiveObjC-iOS",
                path: "ReactiveObjC",
                exclude: ["Info.plist",
                          "NSControl+RACCommandSupport.m",
                          "NSControl+RACTextSignalSupport.m",
                          "NSObject+RACAppKitBindings.m",
                          "NSText+RACSignalSupport.m"],
                sources: ["RACEagerSequence.m",
                          "RACGroupedSignal.m",
                          "RACScheduler.m",
                          "RACSubscriptingAssignmentTrampoline.m",
                          "RACSubscriber.m",
                          "RACSignal+Operations.m",
                          "RACBehaviorSubject.m",
                          "UIGestureRecognizer+RACSignalSupport.m",
                          "NSURLConnection+RACSupport.m",
                          "RACSignalSequence.m",
                          "NSString+RACSupport.m",
                          "NSUserDefaults+RACSupport.m",
                          "RACCommand.m",
                          "UIControl+RACSignalSupportPrivate.m",
                          "NSObject+RACDescription.m",
                          "RACTargetQueueScheduler.m",
                          "NSEnumerator+RACSequenceAdditions.m",
                          "RACSerialDisposable.m",
                          "RACEmptySequence.m",
                          "RACDisposable.m",
                          "RACErrorSignal.m",
                          "NSInvocation+RACTypeParsing.m",
                          "RACCompoundDisposable.m",
                          "RACKVOProxy.m",
                          "RACUnarySequence.m",
                          "RACStringSequence.m",
                          "NSObject+RACPropertySubscribing.m",
                          "UITableViewCell+RACSignalSupport.m",
                          "MKAnnotationView+RACSignalSupport.m",
                          "RACEvent.m",
                          "NSArray+RACSequenceAdditions.m",
                          "NSNotificationCenter+RACSupport.m",
                          "UISegmentedControl+RACSignalSupport.m",
                          "UITableViewHeaderFooterView+RACSignalSupport.m",
                          "RACSequence.m",
                          "RACSignal.m",
                          "RACUnit.m",
                          "UICollectionReusableView+RACSignalSupport.m",
                          "extobjc/EXTRuntimeExtensions.m",
                          "UISwitch+RACSignalSupport.m",
                          "RACKVOChannel.m",
                          "RACKVOTrampoline.m",
                          "NSObject+RACLifting.m",
                          "RACSubscriptionScheduler.m",
                          "RACMulticastConnection.m",
                          "NSData+RACSupport.m",
                          "UIControl+RACSignalSupport.m",
                          "RACDynamicSequence.m",
                          "NSObject+RACSelectorSignal.m",
                          "UITextView+RACSignalSupport.m",
                          "NSDictionary+RACSequenceAdditions.m",
                          "RACReplaySubject.m",
                          "UIImagePickerController+RACSignalSupport.m",
                          "RACTestScheduler.m",
                          "RACTupleSequence.m",
                          "RACStream.m",
                          "RACReturnSignal.m",
                          "RACEmptySignal.m",
                          "NSIndexSet+RACSequenceAdditions.m",
                          "RACPassthroughSubscriber.m",
                          "NSObject+RACKVOWrapper.m",
                          "UIStepper+RACSignalSupport.m",
                          "NSOrderedSet+RACSequenceAdditions.m",
                          "UITextField+RACSignalSupport.m",
                          "RACTuple.m",
                          "NSString+RACSequenceAdditions.m",
                          "NSFileHandle+RACSupport.m",
                          "NSString+RACKeyPathUtilities.m",
                          "UIButton+RACCommandSupport.m",
                          "RACChannel.m",
                          "UIRefreshControl+RACCommandSupport.m",
                          "RACQueueScheduler.m",
                          "UIBarButtonItem+RACCommandSupport.m",
                          "RACArraySequence.m",
                          "RACScopedDisposable.m",
                          "UIDatePicker+RACSignalSupport.m",
                          "UISlider+RACSignalSupport.m",
                          "RACImmediateScheduler.m",
                          "RACDelegateProxy.m",
                          "RACDynamicSignal.m",
                          "NSObject+RACDeallocating.m",
                          "RACSubject.m",
                          "RACValueTransformer.m",
                          "RACIndexSetSequence.m",
                          "NSSet+RACSequenceAdditions.m",
                          "RACNeverSignal.m",
                          "RACCompoundDisposableProvider.d",
                          "RACSignalProvider.d"],
                cSettings: [
                    .headerSearchPath("extobjc"),
                ])
    ]
)
