#ifndef _GL_FUNCS_DEF_HPP_
#define _GL_FUNCS_DEF_HPP_

#include <Windows.h>
#include <gl/GL.h>
#include "glext.h"
#include "wglext.h"

#define FUNCTION(TYPE, NAME) extern TYPE NAME;
#include "app/gl_funcs_helper.inc"
#undef FUNCTION

/** Load OpenGL and platform-specific functions */
void LoadGlFuncs();

#endif
