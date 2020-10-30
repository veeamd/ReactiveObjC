#!/bin/bash

PROJECT_NAME="ReactiveObjC"
PROJECT_DIR="/Users/weiz/Dev/ReactiveObjC"
FRAMEWORK_FOLDER_NAME="xcframework"
SCHEMA_NAME="ReactiveObjC-iOS"
#set workspace name
WORKSPACE_NAME="${PROJECT_NAME}.xcworkspace"
#xcframework path
FRAMEWORK_PATH="${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}/${SCHEMA_NAME}.xcframework"
# set path for iOS simulator archive
SIMULATOR_ARCHIVE_PATH="${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}/simulator.xcarchive"
# set path for iOS device archive
IOS_DEVICE_ARCHIVE_PATH="${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}/iOS.xcarchive"
rm -rf "${PROJECT_DIR}/build"
rm -rf "${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}"
echo "Deleted ${FRAMEWORK_FOLDER_NAME}"
mkdir -p "${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}"
echo "Created ${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}"
echo "Archiving ${SCHEMA_NAME} at ${SIMULATOR_ARCHIVE_PATH}"
xcodebuild archive -workspace ${WORKSPACE_NAME} -scheme ${SCHEMA_NAME} -destination="generic/platform=iOS Simulator" -sdk iphonesimulator -archivePath ${SIMULATOR_ARCHIVE_PATH} SKIP_INSTALL=NO BUILD_LIBRARIES_FOR_DISTRIBUTION=YES | xcpretty
echo "Archiving ${SCHEMA_NAME} at ${IOS_DEVICE_ARCHIVE_PATH}"
xcodebuild archive -workspace ${WORKSPACE_NAME} -scheme ${SCHEMA_NAME} -destination="generic/platform=iOS" -sdk iphoneos -archivePath ${IOS_DEVICE_ARCHIVE_PATH} SKIP_INSTALL=NO BUILD_LIBRARIES_FOR_DISTRIBUTION=YES | xcpretty
#Creating XCFramework
xcodebuild -create-xcframework -framework ${SIMULATOR_ARCHIVE_PATH}/Products/@rpath/${PROJECT_NAME}.framework -framework ${IOS_DEVICE_ARCHIVE_PATH}/Products/@rpath/${PROJECT_NAME}.framework -output "${FRAMEWORK_PATH}" | xcpretty
rm -rf "${SIMULATOR_ARCHIVE_PATH}"
rm -rf "${IOS_DEVICE_ARCHIVE_PATH}"
open "${PROJECT_DIR}/${FRAMEWORK_FOLDER_NAME}"
