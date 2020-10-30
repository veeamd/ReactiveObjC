// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "ReactiveObjC",
    products: [
        .library(name: "ReactiveObjC", targets: ["ReactiveObjC-iOS"])
    ],
    targets: [
        .binaryTarget(name: "ReactiveObjC-iOS",
                      url: "https://github.com/veeamd/ReactiveObjC/releases/download/4.0.0/ReactiveObjC-iOS.xcframework.zip",
                      checksum: "8d9633cd21b3cf62d97292b49240c5f3eb0fd30c9bc4a51ffad21b4f1a7056c7")
    ]
)
