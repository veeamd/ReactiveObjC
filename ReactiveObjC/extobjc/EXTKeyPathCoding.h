//
//  EXTKeyPathCoding.h
//  extobjc
//
//  Created by Justin Spahr-Summers on 19.06.12.
//  Copyright (C) 2012 Justin Spahr-Summers.
//  Released under the MIT license.
//

#import <Foundation/Foundation.h>
#if SWIFT_PACKAGE
#import "metamacros.h"
#else
#import <ReactiveObjC/metamacros.h>
#endif

/**
 * \@rac_keypath allows compile-time verification of key paths. Given a real object
 * receiver and key path:
 *
 * @code

NSString *UTF8StringPath = @rac_keypath(str.lowercaseString.UTF8String);
// => @"lowercaseString.UTF8String"

NSString *versionPath = @rac_keypath(NSObject, version);
// => @"version"

NSString *lowercaseStringPath = @rac_keypath(NSString.new, lowercaseString);
// => @"lowercaseString"

 * @endcode
 *
 * ... the macro returns an \c NSString containing all but the first path
 * component or argument (e.g., @"lowercaseString.UTF8String", @"version").
 *
 * In addition to simply creating a key path, this macro ensures that the key
 * path is valid at compile-time (causing a syntax error if not), and supports
 * refactoring, such that changing the name of the property will also update any
 * uses of \@rac_keypath.
 */
#define rac_keypath(...) \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Warc-repeated-use-of-weak\"") \
    (NO).boolValue ? ((NSString * _Nonnull)nil) : ((NSString * _Nonnull)@(rac_cStringKeypath(__VA_ARGS__))) \
    _Pragma("clang diagnostic pop") \

#define rac_cStringKeypath(...) \
    rac_metamacro_if_eq(1, rac_metamacro_argcount(__VA_ARGS__))(rac_keypath1(__VA_ARGS__))(rac_keypath2(__VA_ARGS__))

#define rac_keypath1(PATH) \
    (((void)(NO && ((void)PATH, NO)), strchr(# PATH, '.') + 1))

#define rac_keypath2(OBJ, PATH) \
    (((void)(NO && ((void)OBJ.PATH, NO)), # PATH))

/**
 * \@rac_collectionKeypath allows compile-time verification of key paths across collections NSArray/NSSet etc. Given a real object
 * receiver, collection object receiver and related keypaths:
 *
 * @code
 
 NSString *employessFirstNamePath = @rac_collectionKeypath(department.employees, Employee.new, firstName)
 // => @"employees.firstName"
 
 NSString *employessFirstNamePath = @rac_collectionKeypath(Department.new, employees, Employee.new, firstName)
 // => @"employees.firstName"

 * @endcode
 *
 */
#define rac_collectionKeypath(...) \
    rac_metamacro_if_eq(3, rac_metamacro_argcount(__VA_ARGS__))(rac_collectionKeypath3(__VA_ARGS__))(rac_collectionKeypath4(__VA_ARGS__))

#define rac_collectionKeypath3(PATH, COLLECTION_OBJECT, COLLECTION_PATH) \
    (YES).boolValue ? (NSString * _Nonnull)@((const char * _Nonnull)[[NSString stringWithFormat:@"%s.%s", rac_cStringKeypath(PATH), rac_cStringKeypath(COLLECTION_OBJECT, COLLECTION_PATH)] UTF8String]) : (NSString * _Nonnull)nil

#define rac_collectionKeypath4(OBJ, PATH, COLLECTION_OBJECT, COLLECTION_PATH) \
    (YES).boolValue ? (NSString * _Nonnull)@((const char * _Nonnull)[[NSString stringWithFormat:@"%s.%s", rac_cStringKeypath(OBJ, PATH), rac_cStringKeypath(COLLECTION_OBJECT, COLLECTION_PATH)] UTF8String]) : (NSString * _Nonnull)nil

