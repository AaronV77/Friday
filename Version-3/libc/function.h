/*
 * This macro is used to keep the compiler from warning about 
 * - "unused variable warning". Basically a stub that will be
 * - called when a function doesn't need the passed in argument
 * - and this function will be called with the unused argument.
 */
#define UNUSED(x) (void)(x)
