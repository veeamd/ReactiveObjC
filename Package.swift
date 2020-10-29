// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "ReactiveObjC",
    products: [
        .library(name: "ReactiveObjC", targets: ["ReactiveObjC-iOS"])
    ],
    dependencies: [],
    targets: [
        .binaryTarget(name: "ReactiveObjC-iOS",
                      url: "https://github.com/veeamd/ReactiveObjC/releases/download/4.0.0/ReactiveObjC.xcframework.zip")
    ]
)
