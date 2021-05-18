// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "ReactiveObjC",
    platforms: [.iOS(.v13)],
    products: [
        .library(name: "ReactiveObjC", targets: ["ReactiveObjC"])
    ],
    targets: [
        .binaryTarget(name: "ReactiveObjC",
                      url: "https://github.com/veeamd/ReactiveObjC/releases/download/4.0.1/ReactiveObjC.xcframework.zip",
                      checksum: "e9760a9e944d67a4979954e860410a54add43284cfceba5dc288c2223ed4c247")
    ]
)
