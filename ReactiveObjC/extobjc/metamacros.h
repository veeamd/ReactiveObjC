/**
 * Macros for metaprogramming
 * ExtendedC
 *
 * Copyright (C) 2012 Justin Spahr-Summers
 * Released under the MIT license
 */

/**
 * Executes one or more expressions (which may have a void type, such as a call
 * to a function that returns no value) and always returns true.
 */
#undef rac_metamacro_exprify
#define rac_metamacro_exprify(...) \
    ((__VA_ARGS__), true)

/**
 * Returns a string representation of VALUE after full macro expansion.
 */
#undef rac_metamacro_stringify
#define rac_metamacro_stringify(VALUE) \
        rac_metamacro_stringify_(VALUE)

/**
 * Returns A and B concatenated after full macro expansion.
 */
#undef rac_metamacro_concat
#define rac_metamacro_concat(A, B) \
        rac_metamacro_concat_(A, B)

/**
 * Returns the Nth variadic argument (starting from zero). At least
 * N + 1 variadic arguments must be given. N must be between zero and twenty,
 * inclusive.
 */
#undef rac_metamacro_at
#define rac_metamacro_at(N, ...) \
        rac_metamacro_concat(rac_metamacro_at, N)(__VA_ARGS__)

/**
 * Returns the number of arguments (up to twenty) provided to the macro. At
 * least one argument must be provided.
 *
 * Inspired by P99: http://p99.gforge.inria.fr
 */
#undef rac_metamacro_argcount
#define rac_metamacro_argcount(...) \
        rac_metamacro_at(40, __VA_ARGS__, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

/**
 * Identical to #metamacro_foreach_cxt, except that no CONTEXT argument is
 * given. Only the index and current argument will thus be passed to MACRO.
 */
#undef rac_metamacro_foreach
#define rac_metamacro_foreach(MACRO, SEP, ...) \
        rac_metamacro_foreach_cxt(rac_metamacro_foreach_iter, SEP, MACRO, __VA_ARGS__)

/**
 * For each consecutive variadic argument (up to twenty), MACRO is passed the
 * zero-based index of the current argument, CONTEXT, and then the argument
 * itself. The results of adjoining invocations of MACRO are then separated by
 * SEP.
 *
 * Inspired by P99: http://p99.gforge.inria.fr
 */
#undef rac_metamacro_foreach_cxt
#define rac_metamacro_foreach_cxt(MACRO, SEP, CONTEXT, ...) \
        rac_metamacro_concat(rac_metamacro_foreach_cxt, rac_metamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

/**
 * Identical to #metamacro_foreach_cxt. This can be used when the former would
 * fail due to recursive macro expansion.
 */
#undef rac_metamacro_foreach_cxt_recursive
#define rac_metamacro_foreach_cxt_recursive(MACRO, SEP, CONTEXT, ...) \
        rac_metamacro_concat(rac_metamacro_foreach_cxt_recursive, rac_metamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

/**
 * In consecutive order, appends each variadic argument (up to twenty) onto
 * BASE. The resulting concatenations are then separated by SEP.
 *
 * This is primarily useful to manipulate a list of macro invocations into instead
 * invoking a different, possibly related macro.
 */
#undef rac_metamacro_foreach_concat
#define rac_metamacro_foreach_concat(BASE, SEP, ...) \
        rac_metamacro_foreach_cxt(rac_metamacro_foreach_concat_iter, SEP, BASE, __VA_ARGS__)

/**
 * Iterates COUNT times, each time invoking MACRO with the current index
 * (starting at zero) and CONTEXT. The results of adjoining invocations of MACRO
 * are then separated by SEP.
 *
 * COUNT must be an integer between zero and twenty, inclusive.
 */
#undef rac_metamacro_for_cxt
#define rac_metamacro_for_cxt(COUNT, MACRO, SEP, CONTEXT) \
        rac_metamacro_concat(rac_metamacro_for_cxt, COUNT)(MACRO, SEP, CONTEXT)

/**
 * Returns the first argument given. At least one argument must be provided.
 *
 * This is useful when implementing a variadic macro, where you may have only
 * one variadic argument, but no way to retrieve it (for example, because \c ...
 * always needs to match at least one argument).
 *
 * @code

#undef varmacro
#define varmacro(...) \
    rac_metamacro_head(__VA_ARGS__)

 * @endcode
 */
#undef rac_metamacro_head
#define rac_metamacro_head(...) \
        rac_metamacro_head_(__VA_ARGS__, 0)

/**
 * Returns every argument except the first. At least two arguments must be
 * provided.
 */
#undef rac_metamacro_tail
#define rac_metamacro_tail(...) \
        rac_metamacro_tail_(__VA_ARGS__)

/**
 * Returns the first N (up to twenty) variadic arguments as a new argument list.
 * At least N variadic arguments must be provided.
 */
#undef rac_metamacro_take
#define rac_metamacro_take(N, ...) \
        rac_metamacro_concat(rac_metamacro_take, N)(__VA_ARGS__)

/**
 * Removes the first N (up to twenty) variadic arguments from the given argument
 * list. At least N variadic arguments must be provided.
 */
#undef rac_metamacro_drop
#define rac_metamacro_drop(N, ...) \
        rac_metamacro_concat(rac_metamacro_drop, N)(__VA_ARGS__)

/**
 * Decrements VAL, which must be a number between zero and forty, inclusive.
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#undef rac_metamacro_dec
#define rac_metamacro_dec(VAL) \
        rac_metamacro_at(VAL, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,38, 39)

/**
 * Increments VAL, which must be a number between zero and forty, inclusive.
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#undef rac_metamacro_inc
#define rac_metamacro_inc(VAL) \
        rac_metamacro_at(VAL, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41)

/**
 * If A is equal to B, the next argument list is expanded; otherwise, the
 * argument list after that is expanded. A and B must be numbers between zero
 * and twenty, inclusive. Additionally, B must be greater than or equal to A.
 *
 * @code

// expands to true
metamacro_if_eq(0, 0)(true)(false)

// expands to false
metamacro_if_eq(0, 1)(true)(false)

 * @endcode
 *
 * This is primarily useful when dealing with indexes and counts in
 * metaprogramming.
 */
#undef rac_metamacro_if_eq
#define rac_metamacro_if_eq(A, B) \
        rac_metamacro_concat(rac_metamacro_if_eq, A)(B)

/**
 * Identical to #metamacro_if_eq. This can be used when the former would fail
 * due to recursive macro expansion.
 */
#undef rac_metamacro_if_eq_recursive
#define rac_metamacro_if_eq_recursive(A, B) \
        rac_metamacro_concat(rac_metamacro_if_eq_recursive, A)(B)

/**
 * Returns 1 if N is an even number, or 0 otherwise. N must be between zero and
 * twenty, inclusive.
 *
 * For the purposes of this test, zero is considered even.
 */
#undef rac_metamacro_is_even
#define rac_metamacro_is_even(N) \
        rac_metamacro_at(N, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1)

/**
 * Returns the logical NOT of B, which must be the number zero or one.
 */
#undef rac_metamacro_not
#define rac_metamacro_not(B) \
        rac_metamacro_at(B, 1, 0)

// IMPLEMENTATION DETAILS FOLLOW!
// Do not write code that depends on anything below this line.
#undef rac_metamacro_stringify_
#define rac_metamacro_stringify_(VALUE) # VALUE
#undef rac_metamacro_concat_
#define rac_metamacro_concat_(A, B) A ## B
#undef rac_metamacro_foreach_iter
#define rac_metamacro_foreach_iter(INDEX, MACRO, ARG) MACRO(INDEX, ARG)
#undef rac_metamacro_head_
#define rac_metamacro_head_(FIRST, ...) FIRST
#undef rac_metamacro_tail_
#define rac_metamacro_tail_(FIRST, ...) __VA_ARGS__
#undef rac_metamacro_consume_
#define rac_metamacro_consume_(...)
#undef rac_metamacro_expand_
#define rac_metamacro_expand_(...) __VA_ARGS__

// implemented from scratch so that rac_metamacro_concat() doesn't end up nesting
#undef rac_metamacro_foreach_concat_iter
#define rac_metamacro_foreach_concat_iter(INDEX, BASE, ARG) rac_metamacro_foreach_concat_iter_(BASE, ARG)
#undef rac_metamacro_foreach_concat_iter_
#define rac_metamacro_foreach_concat_iter_(BASE, ARG) BASE ## ARG

// rac_metamacro_at expansions
#undef rac_metamacro_at0
#define rac_metamacro_at0(...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at1
#define rac_metamacro_at1(_0, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at2
#define rac_metamacro_at2(_0, _1, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at3
#define rac_metamacro_at3(_0, _1, _2, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at4
#define rac_metamacro_at4(_0, _1, _2, _3, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at5
#define rac_metamacro_at5(_0, _1, _2, _3, _4, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at6
#define rac_metamacro_at6(_0, _1, _2, _3, _4, _5, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at7
#define rac_metamacro_at7(_0, _1, _2, _3, _4, _5, _6, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at8
#define rac_metamacro_at8(_0, _1, _2, _3, _4, _5, _6, _7, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at9
#define rac_metamacro_at9(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at10
#define rac_metamacro_at10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at11
#define rac_metamacro_at11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at12
#define rac_metamacro_at12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at13
#define rac_metamacro_at13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at14
#define rac_metamacro_at14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at15
#define rac_metamacro_at15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at16
#define rac_metamacro_at16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at17
#define rac_metamacro_at17(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at18
#define rac_metamacro_at18(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at19
#define rac_metamacro_at19(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at20
#define rac_metamacro_at20(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at21
#define rac_metamacro_at21(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at22
#define rac_metamacro_at22(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at23
#define rac_metamacro_at23(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at24
#define rac_metamacro_at24(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at25
#define rac_metamacro_at25(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at26
#define rac_metamacro_at26(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at27
#define rac_metamacro_at27(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at28
#define rac_metamacro_at28(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at29
#define rac_metamacro_at29(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at30
#define rac_metamacro_at30(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at31
#define rac_metamacro_at31(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at32
#define rac_metamacro_at32(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at33
#define rac_metamacro_at33(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at34
#define rac_metamacro_at34(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at35
#define rac_metamacro_at35(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at36
#define rac_metamacro_at36(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at37
#define rac_metamacro_at37(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at38
#define rac_metamacro_at38(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at39
#define rac_metamacro_at39(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, ...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_at40
#define rac_metamacro_at40(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, ...) rac_metamacro_head(__VA_ARGS__)

// rac_metamacro_foreach_cxt expansions
#undef rac_metamacro_foreach_cxt0
#define rac_metamacro_foreach_cxt0(MACRO, SEP, CONTEXT)
#undef rac_metamacro_foreach_cxt1
#define rac_metamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#undef rac_metamacro_foreach_cxt2
#define rac_metamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
    rac_metamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) \
    SEP \
    MACRO(1, CONTEXT, _1)

#undef rac_metamacro_foreach_cxt3
#define rac_metamacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    rac_metamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
    SEP \
    MACRO(2, CONTEXT, _2)

#undef rac_metamacro_foreach_cxt4
#define rac_metamacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    rac_metamacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    SEP \
    MACRO(3, CONTEXT, _3)

#undef rac_metamacro_foreach_cxt5
#define rac_metamacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    rac_metamacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    SEP \
    MACRO(4, CONTEXT, _4)

#undef rac_metamacro_foreach_cxt6
#define rac_metamacro_foreach_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    rac_metamacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    SEP \
    MACRO(5, CONTEXT, _5)

#undef rac_metamacro_foreach_cxt7
#define rac_metamacro_foreach_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    rac_metamacro_foreach_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    SEP \
    MACRO(6, CONTEXT, _6)

#undef rac_metamacro_foreach_cxt8
#define rac_metamacro_foreach_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    rac_metamacro_foreach_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    SEP \
    MACRO(7, CONTEXT, _7)

#undef rac_metamacro_foreach_cxt9
#define rac_metamacro_foreach_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    rac_metamacro_foreach_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    SEP \
    MACRO(8, CONTEXT, _8)

#undef rac_metamacro_foreach_cxt10
#define rac_metamacro_foreach_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    rac_metamacro_foreach_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    SEP \
    MACRO(9, CONTEXT, _9)

#undef rac_metamacro_foreach_cxt11
#define rac_metamacro_foreach_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    rac_metamacro_foreach_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    SEP \
    MACRO(10, CONTEXT, _10)

#undef rac_metamacro_foreach_cxt12
#define rac_metamacro_foreach_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    rac_metamacro_foreach_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    SEP \
    MACRO(11, CONTEXT, _11)

#undef rac_metamacro_foreach_cxt13
#define rac_metamacro_foreach_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    rac_metamacro_foreach_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    SEP \
    MACRO(12, CONTEXT, _12)

#undef rac_metamacro_foreach_cxt14
#define rac_metamacro_foreach_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    rac_metamacro_foreach_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    SEP \
    MACRO(13, CONTEXT, _13)

#undef rac_metamacro_foreach_cxt15
#define rac_metamacro_foreach_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    rac_metamacro_foreach_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    SEP \
    MACRO(14, CONTEXT, _14)

#undef rac_metamacro_foreach_cxt16
#define rac_metamacro_foreach_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    rac_metamacro_foreach_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    SEP \
    MACRO(15, CONTEXT, _15)

#undef rac_metamacro_foreach_cxt17
#define rac_metamacro_foreach_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    rac_metamacro_foreach_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    SEP \
    MACRO(16, CONTEXT, _16)

#undef rac_metamacro_foreach_cxt18
#define rac_metamacro_foreach_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    rac_metamacro_foreach_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    SEP \
    MACRO(17, CONTEXT, _17)

#undef rac_metamacro_foreach_cxt19
#define rac_metamacro_foreach_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    rac_metamacro_foreach_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    SEP \
    MACRO(18, CONTEXT, _18)

#undef rac_metamacro_foreach_cxt20
#define rac_metamacro_foreach_cxt20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    rac_metamacro_foreach_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    SEP \
    MACRO(19, CONTEXT, _19)

#undef rac_metamacro_foreach_cxt21
#define rac_metamacro_foreach_cxt21(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) \
    rac_metamacro_foreach_cxt20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    SEP \
    MACRO(20, CONTEXT, _20)

#undef rac_metamacro_foreach_cxt22
#define rac_metamacro_foreach_cxt22(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) \
    rac_metamacro_foreach_cxt21(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) \
    SEP \
    MACRO(21, CONTEXT, _21)

#undef rac_metamacro_foreach_cxt23
#define rac_metamacro_foreach_cxt23(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) \
    rac_metamacro_foreach_cxt22(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) \
    SEP \
    MACRO(22, CONTEXT, _22)

#undef rac_metamacro_foreach_cxt24
#define rac_metamacro_foreach_cxt24(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) \
    rac_metamacro_foreach_cxt23(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22) \
    SEP \
    MACRO(23, CONTEXT, _23)

#undef rac_metamacro_foreach_cxt25
#define rac_metamacro_foreach_cxt25(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) \
    rac_metamacro_foreach_cxt24(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23) \
    SEP \
    MACRO(24, CONTEXT, _24)

#undef rac_metamacro_foreach_cxt26
#define rac_metamacro_foreach_cxt26(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) \
    rac_metamacro_foreach_cxt25(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24) \
    SEP \
    MACRO(25, CONTEXT, _25)

#undef rac_metamacro_foreach_cxt27
#define rac_metamacro_foreach_cxt27(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) \
    rac_metamacro_foreach_cxt26(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25) \
    SEP \
    MACRO(26, CONTEXT, _26)

#undef rac_metamacro_foreach_cxt28
#define rac_metamacro_foreach_cxt28(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) \
    rac_metamacro_foreach_cxt27(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26) \
    SEP \
    MACRO(27, CONTEXT, _27)

#undef rac_metamacro_foreach_cxt29
#define rac_metamacro_foreach_cxt29(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) \
    rac_metamacro_foreach_cxt28(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27) \
    SEP \
    MACRO(28, CONTEXT, _28)

#undef rac_metamacro_foreach_cxt30
#define rac_metamacro_foreach_cxt30(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) \
    rac_metamacro_foreach_cxt29(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28) \
    SEP \
    MACRO(29, CONTEXT, _29)

#undef rac_metamacro_foreach_cxt31
#define rac_metamacro_foreach_cxt31(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) \
    rac_metamacro_foreach_cxt30(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29) \
    SEP \
    MACRO(30, CONTEXT, _30)

#undef rac_metamacro_foreach_cxt32
#define rac_metamacro_foreach_cxt32(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) \
    rac_metamacro_foreach_cxt31(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30) \
    SEP \
    MACRO(31, CONTEXT, _31)

#undef rac_metamacro_foreach_cxt33
#define rac_metamacro_foreach_cxt33(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) \
    rac_metamacro_foreach_cxt32(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31) \
    SEP \
    MACRO(32, CONTEXT, _32)

#undef rac_metamacro_foreach_cxt34
#define rac_metamacro_foreach_cxt34(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) \
    rac_metamacro_foreach_cxt33(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32) \
    SEP \
    MACRO(33, CONTEXT, _33)

#undef rac_metamacro_foreach_cxt35
#define rac_metamacro_foreach_cxt35(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) \
    rac_metamacro_foreach_cxt34(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33) \
    SEP \
    MACRO(34, CONTEXT, _34)

#undef rac_metamacro_foreach_cxt36
#define rac_metamacro_foreach_cxt36(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) \
    rac_metamacro_foreach_cxt35(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34) \
    SEP \
    MACRO(35, CONTEXT, _35)

#undef rac_metamacro_foreach_cxt37
#define rac_metamacro_foreach_cxt37(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) \
    rac_metamacro_foreach_cxt36(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35) \
    SEP \
    MACRO(36, CONTEXT, _36)

#undef rac_metamacro_foreach_cxt38
#define rac_metamacro_foreach_cxt38(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) \
    rac_metamacro_foreach_cxt37(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36) \
    SEP \
    MACRO(37, CONTEXT, _37)

#undef rac_metamacro_foreach_cxt39
#define rac_metamacro_foreach_cxt39(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) \
    rac_metamacro_foreach_cxt38(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37) \
    SEP \
    MACRO(38, CONTEXT, _38)

#undef rac_metamacro_foreach_cxt40
#define rac_metamacro_foreach_cxt40(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39) \
    rac_metamacro_foreach_cxt39(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38) \
    SEP \
    MACRO(39, CONTEXT, _39)

// rac_metamacro_foreach_cxt_recursive expansions
#undef rac_metamacro_foreach_cxt_recursive0
#define rac_metamacro_foreach_cxt_recursive0(MACRO, SEP, CONTEXT)
#undef rac_metamacro_foreach_cxt_recursive1
#define rac_metamacro_foreach_cxt_recursive1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#undef rac_metamacro_foreach_cxt_recursive2
#define rac_metamacro_foreach_cxt_recursive2(MACRO, SEP, CONTEXT, _0, _1) \
    rac_metamacro_foreach_cxt_recursive1(MACRO, SEP, CONTEXT, _0) \
    SEP \
    MACRO(1, CONTEXT, _1)

#undef rac_metamacro_foreach_cxt_recursive3
#define rac_metamacro_foreach_cxt_recursive3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    rac_metamacro_foreach_cxt_recursive2(MACRO, SEP, CONTEXT, _0, _1) \
    SEP \
    MACRO(2, CONTEXT, _2)

#undef rac_metamacro_foreach_cxt_recursive4
#define rac_metamacro_foreach_cxt_recursive4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    rac_metamacro_foreach_cxt_recursive3(MACRO, SEP, CONTEXT, _0, _1, _2) \
    SEP \
    MACRO(3, CONTEXT, _3)

#undef rac_metamacro_foreach_cxt_recursive5
#define rac_metamacro_foreach_cxt_recursive5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    rac_metamacro_foreach_cxt_recursive4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
    SEP \
    MACRO(4, CONTEXT, _4)

#undef rac_metamacro_foreach_cxt_recursive6
#define rac_metamacro_foreach_cxt_recursive6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    rac_metamacro_foreach_cxt_recursive5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
    SEP \
    MACRO(5, CONTEXT, _5)

#undef rac_metamacro_foreach_cxt_recursive7
#define rac_metamacro_foreach_cxt_recursive7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    rac_metamacro_foreach_cxt_recursive6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
    SEP \
    MACRO(6, CONTEXT, _6)

#undef rac_metamacro_foreach_cxt_recursive8
#define rac_metamacro_foreach_cxt_recursive8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    rac_metamacro_foreach_cxt_recursive7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
    SEP \
    MACRO(7, CONTEXT, _7)

#undef rac_metamacro_foreach_cxt_recursive9
#define rac_metamacro_foreach_cxt_recursive9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    rac_metamacro_foreach_cxt_recursive8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
    SEP \
    MACRO(8, CONTEXT, _8)

#undef rac_metamacro_foreach_cxt_recursive10
#define rac_metamacro_foreach_cxt_recursive10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    rac_metamacro_foreach_cxt_recursive9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    SEP \
    MACRO(9, CONTEXT, _9)

#undef rac_metamacro_foreach_cxt_recursive11
#define rac_metamacro_foreach_cxt_recursive11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    rac_metamacro_foreach_cxt_recursive10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    SEP \
    MACRO(10, CONTEXT, _10)

#undef rac_metamacro_foreach_cxt_recursive12
#define rac_metamacro_foreach_cxt_recursive12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    rac_metamacro_foreach_cxt_recursive11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    SEP \
    MACRO(11, CONTEXT, _11)

#undef rac_metamacro_foreach_cxt_recursive13
#define rac_metamacro_foreach_cxt_recursive13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    rac_metamacro_foreach_cxt_recursive12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    SEP \
    MACRO(12, CONTEXT, _12)

#undef rac_metamacro_foreach_cxt_recursive14
#define rac_metamacro_foreach_cxt_recursive14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    rac_metamacro_foreach_cxt_recursive13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    SEP \
    MACRO(13, CONTEXT, _13)

#undef rac_metamacro_foreach_cxt_recursive15
#define rac_metamacro_foreach_cxt_recursive15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    rac_metamacro_foreach_cxt_recursive14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    SEP \
    MACRO(14, CONTEXT, _14)

#undef rac_metamacro_foreach_cxt_recursive16
#define rac_metamacro_foreach_cxt_recursive16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    rac_metamacro_foreach_cxt_recursive15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    SEP \
    MACRO(15, CONTEXT, _15)

#undef rac_metamacro_foreach_cxt_recursive17
#define rac_metamacro_foreach_cxt_recursive17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    rac_metamacro_foreach_cxt_recursive16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    SEP \
    MACRO(16, CONTEXT, _16)

#undef rac_metamacro_foreach_cxt_recursive18
#define rac_metamacro_foreach_cxt_recursive18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    rac_metamacro_foreach_cxt_recursive17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    SEP \
    MACRO(17, CONTEXT, _17)

#undef rac_metamacro_foreach_cxt_recursive19
#define rac_metamacro_foreach_cxt_recursive19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    rac_metamacro_foreach_cxt_recursive18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    SEP \
    MACRO(18, CONTEXT, _18)

#undef rac_metamacro_foreach_cxt_recursive20
#define rac_metamacro_foreach_cxt_recursive20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    rac_metamacro_foreach_cxt_recursive19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    SEP \
    MACRO(19, CONTEXT, _19)

// rac_metamacro_for_cxt expansions
#undef rac_metamacro_for_cxt0
#define rac_metamacro_for_cxt0(MACRO, SEP, CONTEXT)
#undef rac_metamacro_for_cxt1
#define rac_metamacro_for_cxt1(MACRO, SEP, CONTEXT) MACRO(0, CONTEXT)

#undef rac_metamacro_for_cxt2
#define rac_metamacro_for_cxt2(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt1(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(1, CONTEXT)

#undef rac_metamacro_for_cxt3
#define rac_metamacro_for_cxt3(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt2(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(2, CONTEXT)

#undef rac_metamacro_for_cxt4
#define rac_metamacro_for_cxt4(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt3(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(3, CONTEXT)

#undef rac_metamacro_for_cxt5
#define rac_metamacro_for_cxt5(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt4(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(4, CONTEXT)

#undef rac_metamacro_for_cxt6
#define rac_metamacro_for_cxt6(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt5(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(5, CONTEXT)

#undef rac_metamacro_for_cxt7
#define rac_metamacro_for_cxt7(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt6(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(6, CONTEXT)

#undef rac_metamacro_for_cxt8
#define rac_metamacro_for_cxt8(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt7(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(7, CONTEXT)

#undef rac_metamacro_for_cxt9
#define rac_metamacro_for_cxt9(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt8(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(8, CONTEXT)

#undef rac_metamacro_for_cxt10
#define rac_metamacro_for_cxt10(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt9(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(9, CONTEXT)

#undef rac_metamacro_for_cxt11
#define rac_metamacro_for_cxt11(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt10(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(10, CONTEXT)

#undef rac_metamacro_for_cxt12
#define rac_metamacro_for_cxt12(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt11(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(11, CONTEXT)

#undef rac_metamacro_for_cxt13
#define rac_metamacro_for_cxt13(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt12(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(12, CONTEXT)

#undef rac_metamacro_for_cxt14
#define rac_metamacro_for_cxt14(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt13(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(13, CONTEXT)

#undef rac_metamacro_for_cxt15
#define rac_metamacro_for_cxt15(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt14(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(14, CONTEXT)

#undef rac_metamacro_for_cxt16
#define rac_metamacro_for_cxt16(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt15(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(15, CONTEXT)

#undef rac_metamacro_for_cxt17
#define rac_metamacro_for_cxt17(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt16(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(16, CONTEXT)

#undef rac_metamacro_for_cxt18
#define rac_metamacro_for_cxt18(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt17(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(17, CONTEXT)

#undef rac_metamacro_for_cxt19
#define rac_metamacro_for_cxt19(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt18(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(18, CONTEXT)

#undef rac_metamacro_for_cxt20
#define rac_metamacro_for_cxt20(MACRO, SEP, CONTEXT) \
    rac_metamacro_for_cxt19(MACRO, SEP, CONTEXT) \
    SEP \
    MACRO(19, CONTEXT)

// rac_metamacro_if_eq expansions
#undef rac_metamacro_if_eq0
#define rac_metamacro_if_eq0(VALUE) \
    rac_metamacro_concat(rac_metamacro_if_eq0_, VALUE)

#undef rac_metamacro_if_eq0_0
#define rac_metamacro_if_eq0_0(...) __VA_ARGS__ rac_metamacro_consume_
#undef rac_metamacro_if_eq0_1
#define rac_metamacro_if_eq0_1(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_2
#define rac_metamacro_if_eq0_2(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_3
#define rac_metamacro_if_eq0_3(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_4
#define rac_metamacro_if_eq0_4(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_5
#define rac_metamacro_if_eq0_5(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_6
#define rac_metamacro_if_eq0_6(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_7
#define rac_metamacro_if_eq0_7(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_8
#define rac_metamacro_if_eq0_8(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_9
#define rac_metamacro_if_eq0_9(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_10
#define rac_metamacro_if_eq0_10(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_11
#define rac_metamacro_if_eq0_11(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_12
#define rac_metamacro_if_eq0_12(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_13
#define rac_metamacro_if_eq0_13(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_14
#define rac_metamacro_if_eq0_14(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_15
#define rac_metamacro_if_eq0_15(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_16
#define rac_metamacro_if_eq0_16(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_17
#define rac_metamacro_if_eq0_17(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_18
#define rac_metamacro_if_eq0_18(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_19
#define rac_metamacro_if_eq0_19(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq0_20
#define rac_metamacro_if_eq0_20(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_21(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_22(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_23(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_24(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_25(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_26(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_27(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_28(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_29(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_30(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_31(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_32(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_33(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_34(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_35(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_36(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_37(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_38(...) rac_metamacro_expand_
#define rac_metamacro_if_eq0_39(...) rac_metamacro_expand_

#undef rac_metamacro_if_eq1
#define rac_metamacro_if_eq1(VALUE) rac_metamacro_if_eq0(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq2
#define rac_metamacro_if_eq2(VALUE) rac_metamacro_if_eq1(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq3
#define rac_metamacro_if_eq3(VALUE) rac_metamacro_if_eq2(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq4
#define rac_metamacro_if_eq4(VALUE) rac_metamacro_if_eq3(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq5
#define rac_metamacro_if_eq5(VALUE) rac_metamacro_if_eq4(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq6
#define rac_metamacro_if_eq6(VALUE) rac_metamacro_if_eq5(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq7
#define rac_metamacro_if_eq7(VALUE) rac_metamacro_if_eq6(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq8
#define rac_metamacro_if_eq8(VALUE) rac_metamacro_if_eq7(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq9
#define rac_metamacro_if_eq9(VALUE) rac_metamacro_if_eq8(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq10
#define rac_metamacro_if_eq10(VALUE) rac_metamacro_if_eq9(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq11
#define rac_metamacro_if_eq11(VALUE) rac_metamacro_if_eq10(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq12
#define rac_metamacro_if_eq12(VALUE) rac_metamacro_if_eq11(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq13
#define rac_metamacro_if_eq13(VALUE) rac_metamacro_if_eq12(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq14
#define rac_metamacro_if_eq14(VALUE) rac_metamacro_if_eq13(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq15
#define rac_metamacro_if_eq15(VALUE) rac_metamacro_if_eq14(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq16
#define rac_metamacro_if_eq16(VALUE) rac_metamacro_if_eq15(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq17
#define rac_metamacro_if_eq17(VALUE) rac_metamacro_if_eq16(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq18
#define rac_metamacro_if_eq18(VALUE) rac_metamacro_if_eq17(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq19
#define rac_metamacro_if_eq19(VALUE) rac_metamacro_if_eq18(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq20
#define rac_metamacro_if_eq20(VALUE) rac_metamacro_if_eq19(rac_metamacro_dec(VALUE))

// rac_metamacro_if_eq_recursive expansions
#undef rac_metamacro_if_eq_recursive0
#define rac_metamacro_if_eq_recursive0(VALUE) \
    rac_metamacro_concat(rac_metamacro_if_eq_recursive0_, VALUE)

#undef rac_metamacro_if_eq_recursive0_0
#define rac_metamacro_if_eq_recursive0_0(...) __VA_ARGS__ rac_metamacro_consume_
#undef rac_metamacro_if_eq_recursive0_1
#define rac_metamacro_if_eq_recursive0_1(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_2
#define rac_metamacro_if_eq_recursive0_2(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_3
#define rac_metamacro_if_eq_recursive0_3(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_4
#define rac_metamacro_if_eq_recursive0_4(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_5
#define rac_metamacro_if_eq_recursive0_5(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_6
#define rac_metamacro_if_eq_recursive0_6(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_7
#define rac_metamacro_if_eq_recursive0_7(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_8
#define rac_metamacro_if_eq_recursive0_8(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_9
#define rac_metamacro_if_eq_recursive0_9(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_10
#define rac_metamacro_if_eq_recursive0_10(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_11
#define rac_metamacro_if_eq_recursive0_11(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_12
#define rac_metamacro_if_eq_recursive0_12(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_13
#define rac_metamacro_if_eq_recursive0_13(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_14
#define rac_metamacro_if_eq_recursive0_14(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_15
#define rac_metamacro_if_eq_recursive0_15(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_16
#define rac_metamacro_if_eq_recursive0_16(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_17
#define rac_metamacro_if_eq_recursive0_17(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_18
#define rac_metamacro_if_eq_recursive0_18(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_19
#define rac_metamacro_if_eq_recursive0_19(...) rac_metamacro_expand_
#undef rac_metamacro_if_eq_recursive0_20
#define rac_metamacro_if_eq_recursive0_20(...) rac_metamacro_expand_

#undef rac_metamacro_if_eq_recursive1
#define rac_metamacro_if_eq_recursive1(VALUE) rac_metamacro_if_eq_recursive0(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive2
#define rac_metamacro_if_eq_recursive2(VALUE) rac_metamacro_if_eq_recursive1(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive3
#define rac_metamacro_if_eq_recursive3(VALUE) rac_metamacro_if_eq_recursive2(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive4
#define rac_metamacro_if_eq_recursive4(VALUE) rac_metamacro_if_eq_recursive3(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive5
#define rac_metamacro_if_eq_recursive5(VALUE) rac_metamacro_if_eq_recursive4(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive6
#define rac_metamacro_if_eq_recursive6(VALUE) rac_metamacro_if_eq_recursive5(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive7
#define rac_metamacro_if_eq_recursive7(VALUE) rac_metamacro_if_eq_recursive6(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive8
#define rac_metamacro_if_eq_recursive8(VALUE) rac_metamacro_if_eq_recursive7(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive9
#define rac_metamacro_if_eq_recursive9(VALUE) rac_metamacro_if_eq_recursive8(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive10
#define rac_metamacro_if_eq_recursive10(VALUE) rac_metamacro_if_eq_recursive9(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive11
#define rac_metamacro_if_eq_recursive11(VALUE) rac_metamacro_if_eq_recursive10(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive12
#define rac_metamacro_if_eq_recursive12(VALUE) rac_metamacro_if_eq_recursive11(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive13
#define rac_metamacro_if_eq_recursive13(VALUE) rac_metamacro_if_eq_recursive12(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive14
#define rac_metamacro_if_eq_recursive14(VALUE) rac_metamacro_if_eq_recursive13(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive15
#define rac_metamacro_if_eq_recursive15(VALUE) rac_metamacro_if_eq_recursive14(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive16
#define rac_metamacro_if_eq_recursive16(VALUE) rac_metamacro_if_eq_recursive15(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive17
#define rac_metamacro_if_eq_recursive17(VALUE) rac_metamacro_if_eq_recursive16(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive18
#define rac_metamacro_if_eq_recursive18(VALUE) rac_metamacro_if_eq_recursive17(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive19
#define rac_metamacro_if_eq_recursive19(VALUE) rac_metamacro_if_eq_recursive18(rac_metamacro_dec(VALUE))
#undef rac_metamacro_if_eq_recursive20
#define rac_metamacro_if_eq_recursive20(VALUE) rac_metamacro_if_eq_recursive19(rac_metamacro_dec(VALUE))

// rac_metamacro_take expansions
#undef rac_metamacro_take0
#define rac_metamacro_take0(...)
#undef rac_metamacro_take1
#define rac_metamacro_take1(...) rac_metamacro_head(__VA_ARGS__)
#undef rac_metamacro_take2
#define rac_metamacro_take2(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take1(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take3
#define rac_metamacro_take3(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take2(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take4
#define rac_metamacro_take4(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take3(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take5
#define rac_metamacro_take5(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take4(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take6
#define rac_metamacro_take6(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take5(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take7
#define rac_metamacro_take7(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take6(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take8
#define rac_metamacro_take8(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take7(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take9
#define rac_metamacro_take9(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take8(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take10
#define rac_metamacro_take10(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take9(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take11
#define rac_metamacro_take11(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take10(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take12
#define rac_metamacro_take12(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take11(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take13
#define rac_metamacro_take13(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take12(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take14
#define rac_metamacro_take14(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take13(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take15
#define rac_metamacro_take15(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take14(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take16
#define rac_metamacro_take16(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take15(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take17
#define rac_metamacro_take17(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take16(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take18
#define rac_metamacro_take18(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take17(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take19
#define rac_metamacro_take19(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take18(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_take20
#define rac_metamacro_take20(...) rac_metamacro_head(__VA_ARGS__), rac_metamacro_take19(rac_metamacro_tail(__VA_ARGS__))

// rac_metamacro_drop expansions
#undef rac_metamacro_drop0
#define rac_metamacro_drop0(...) __VA_ARGS__
#undef rac_metamacro_drop1
#define rac_metamacro_drop1(...) rac_metamacro_tail(__VA_ARGS__)
#undef rac_metamacro_drop2
#define rac_metamacro_drop2(...) rac_metamacro_drop1(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop3
#define rac_metamacro_drop3(...) rac_metamacro_drop2(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop4
#define rac_metamacro_drop4(...) rac_metamacro_drop3(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop5
#define rac_metamacro_drop5(...) rac_metamacro_drop4(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop6
#define rac_metamacro_drop6(...) rac_metamacro_drop5(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop7
#define rac_metamacro_drop7(...) rac_metamacro_drop6(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop8
#define rac_metamacro_drop8(...) rac_metamacro_drop7(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop9
#define rac_metamacro_drop9(...) rac_metamacro_drop8(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop10
#define rac_metamacro_drop10(...) rac_metamacro_drop9(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop11
#define rac_metamacro_drop11(...) rac_metamacro_drop10(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop12
#define rac_metamacro_drop12(...) rac_metamacro_drop11(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop13
#define rac_metamacro_drop13(...) rac_metamacro_drop12(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop14
#define rac_metamacro_drop14(...) rac_metamacro_drop13(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop15
#define rac_metamacro_drop15(...) rac_metamacro_drop14(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop16
#define rac_metamacro_drop16(...) rac_metamacro_drop15(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop17
#define rac_metamacro_drop17(...) rac_metamacro_drop16(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop18
#define rac_metamacro_drop18(...) rac_metamacro_drop17(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop19
#define rac_metamacro_drop19(...) rac_metamacro_drop18(rac_metamacro_tail(__VA_ARGS__))
#undef rac_metamacro_drop20
#define rac_metamacro_drop20(...) rac_metamacro_drop19(rac_metamacro_tail(__VA_ARGS__))
