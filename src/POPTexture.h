#ifndef POP_TEXTURE_H
#define POP_TEXTURE_H

#include <gimbal/gimbal_meta.h> // no, this works! CMake is including this as a subdirectory, so this should work

GBL_FORWARD_DECLARE_STRUCT(POP_Texture);
GBL_DECLS_BEGIN

#define POP_TEXTURE_TYPE (GBL_TYPEID(POP_Texture)) // this is the macro we call over in the prop section, follow me again

GblType POP_Texture_type(void);

GBL_DECLS_END

// 100% basically
// some people (me included!) made PRs, but not much. he's made 99.999% of it
// when I eventually wanna learn C++, I'll still use libGimball for its containers + allocators and shit
// but yeah, we won't have much need for the type system


#endif // POP_TEXTURE_H