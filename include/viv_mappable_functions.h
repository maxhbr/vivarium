#ifndef VIV_MAPPABLE_FUNCTIONS_H
#define VIV_MAPPABLE_FUNCTIONS_H

#include "viv_types.h"

// Forward-declare in order to be able to declare the individual union members alongside the
// functions they relate to. This is easier to read than declaring the payload structs separately
// from their functions.
union viv_mappable_payload;

#define GENERATE_PAYLOAD_STRUCT(FUNCTION_NAME, ARGS...) \
    struct viv_mappable_payload_ ## FUNCTION_NAME { ARGS };
#define GENERATE_DECLARATION(FUNCTION_NAME, ARGS...)                    \
    void viv_mappable_ ## FUNCTION_NAME(struct viv_workspace *workspace, union viv_mappable_payload payload); \
    GENERATE_PAYLOAD_STRUCT(FUNCTION_NAME, ARGS)

#define GENERATE_UNION_ENTRY(FUNCTION_NAME, ARGS...) struct viv_mappable_payload_ ## FUNCTION_NAME FUNCTION_NAME ;

// Mappable functions have a specific form to make them easy for a user to bind to keys, but this
// also means we need to generate both a declaration and a union parameter to pass to their generic
// keyword argument mechanism. This macro defines the table of mappable functions.
#define MACRO_FOR_EACH_MAPPABLE(MACRO)                                    \
    MACRO(do_exec, char executable[100]; char *args[100];) \
    MACRO(do_shell, char command[100];)                    \
    MACRO(increment_divide, float increment; )             \
    MACRO(terminate)                                       \
    MACRO(swap_out)                                        \
    MACRO(next_window)                                     \
    MACRO(prev_window)                                     \
    MACRO(shift_active_window_down)                        \
    MACRO(shift_active_window_up)                          \
    MACRO(tile_window)                                     \

// Declare each mappable function and generate a payload struct to pass as its argument
MACRO_FOR_EACH_MAPPABLE(GENERATE_DECLARATION)

union viv_mappable_payload {
    // Pack all the possible payload structs into a union type
    MACRO_FOR_EACH_MAPPABLE(GENERATE_UNION_ENTRY)
};

# endif
