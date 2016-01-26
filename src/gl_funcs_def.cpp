#include "gl_funcs_def.hpp"

#define FUNCTION(TYPE, NAME) TYPE NAME;
#include "gl_funcs_helper.inc"
#undef FUNCTION

void LoadGlFuncs()
{
    #define FUNCTION(TYPE, NAME) NAME = (TYPE)wglGetProcAddress(#NAME);
    #include "gl_funcs_helper.inc"
    #undef FUNCTION
}