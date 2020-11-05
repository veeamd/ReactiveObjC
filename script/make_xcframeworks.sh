#!/bin/bash

PROJECT_NAME="ReactiveObjC"
PROJECT_DIR="."
FRAMEWORK_FOLDER_NAME="xcframework"
FRAMEWORK_NAME="${PROJECT_NAME}.xcframework"
SCHEMA_NAME="ReactiveObjC-iOS"
#set workspace name
WORKSPACE_NAME="${PROJECT_NAME}.xcworkspace"
#xcframework path
FRAMEWORK_PATH="${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}/${FRAMEWORK_NAME}"
# set path for iOS simulator archive
SIMULATOR_ARCHIVE_PATH="${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}/simulator.xcarchive"
# set path for iOS device archive
IOS_DEVICE_ARCHIVE_PATH="${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}/iOS.xcarchive"
# set path for mac catelyst archive
MACOS_DEVICE_ARCHIVE_PATH="${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}/macos.xcarchive"
rm -rf "${PROJECT_DIR}/build"
rm -rf "${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}"
echo "Deleted ${FRAMEWORK_FOLDER_NAME}"
mkdir -p "${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}"
echo "Created ${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}"
echo "Archiving ${SCHEMA_NAME} at ${SIMULATOR_ARCHIVE_PATH}"
xcodebuild archive -workspace ${WORKSPACE_NAME} -scheme ${SCHEMA_NAME} -destination="generic/platform=iOS Simulator" -sdk iphonesimulator -archivePath ${SIMULATOR_ARCHIVE_PATH} SKIP_INSTALL=NO BUILD_LIBRARIES_FOR_DISTRIBUTION=YES | xcpretty
echo "Archiving ${SCHEMA_NAME} at ${IOS_DEVICE_ARCHIVE_PATH}"
xcodebuild archive -workspace ${WORKSPACE_NAME} -scheme ${SCHEMA_NAME} -destination="generic/platform=iOS" -sdk iphoneos -archivePath ${IOS_DEVICE_ARCHIVE_PATH} SKIP_INSTALL=NO BUILD_LIBRARIES_FOR_DISTRIBUTION=YES | xcpretty
echo "Archiving ${SCHEMA_NAME} at ${MACOS_DEVICE_ARCHIVE_PATH}"
xcodebuild archive -workspace ${WORKSPACE_NAME} -scheme ${SCHEMA_NAME} -destination="platform=macOS,variant=Mac\ Catelyst" -archivePath ${MACOS_DEVICE_ARCHIVE_PATH} SKIP_INSTALL=NO BUILD_LIBRARIES_FOR_DISTRIBUTION=YES | xcpretty
#Creating XCFramework
xcodebuild -create-xcframework -framework ${SIMULATOR_ARCHIVE_PATH}/Products/@rpath/${PROJECT_NAME}.framework -framework ${IOS_DEVICE_ARCHIVE_PATH}/Products/@rpath/${PROJECT_NAME}.framework -framework ${MACOS_DEVICE_ARCHIVE_PATH}/Products/@rpath/${PROJECT_NAME}.framework -output "${FRAMEWORK_PATH}" | xcpretty
rm -rf "${SIMULATOR_ARCHIVE_PATH}"
rm -rf "${IOS_DEVICE_ARCHIVE_PATH}"
rm -rf "${MACOS_DEVICE_ARCHIVE_PATH}"
open "${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}"

cd ${FRAMEWORK_FOLDER_NAME}
zip -qr "${FRAMEWORK_NAME}.zip" "${FRAMEWORK_NAME}"
echo "Computed check-sum:"
swift package compute-checksum "${FRAMEWORK_NAME}.zip"
