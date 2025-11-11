#ifndef POP_ANIM_H
#define POP_ANIM_H

#include "../3rdpartylibs/libgimbal/lib/api/gimbal/gimbal_meta.h" // file needed for type system
#include <raylib.h> // can go backend agnostic later

#define POP_ANIM_TYPE 			(GBL_TYPEID 	(POP_Anim)) 		// gives you the type of pop_anim, will be useful later
#define POP_ANIM(self) 			(GBL_CAST 		(POP_Anim, self)) 	// casts the given GblObject-compatible thing to a POP_Anim
#define POP_ANIM_CLASS(klass) 	(GBL_CLASS_CAST	(POP_Anim, klass)) 	// casts the given GblObject-compatible *class* to a POP_Anim_Class
#define POP_ANIM_CLASSOF(self) 	(GBL_CLASSOF	(POP_Anim, self)) 	// casts the given GblObject-compatible *instance* to a POP_Anim_Class

#define GBL_SELF_TYPE POP_Anim

GBL_FORWARD_DECLARE_STRUCT(POP_Anim);

GBL_DECLS_BEGIN
GBL_CLASS_DERIVE(POP_Anim, GblObject)
	GBL_RESULT (*pFnActivate)	(GBL_SELF);
	GBL_RESULT (*pFnDeactivate)	(GBL_SELF);
	GBL_RESULT (*pFnUpdate)		(GBL_SELF);
	GBL_RESULT (*pFnDraw)		(GBL_SELF);
GBL_CLASS_END

GBL_INSTANCE_DERIVE(POP_Anim, GblObject)
	// we do the same as we did before, but we want to add data that we want to be INSTANCE SPECIFIC here
	// can you think of what to put here?
	// yuup. go ahead and add that!

	// nono, that's for functions
	// just add the variable declarations here :P
    bool Boomerang;
    bool Active;
	Vector2 Position;
    float FPS;
    float Rotation;
    float Scale;
    float RealTimer;
    Color Color;
    

GBL_INSTANCE_END

// okay, now we need to define properties, this is the stuff the user will interact with to create POP_Anims

GBL_PROPERTIES(POP_Anim,
	(boomerang, GBL_GENERIC, (READ, WRITE), GBL_BOOL_TYPE),
    (active, GBL_GENERIC, (READ, WRITE), GBL_BOOL_TYPE),
    (speed, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),
	(scale, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),
    (rotation, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),
    (x, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),
	(y, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE)  
)

// cool, that's our properties done
// now, we only need to add our functions!
// are there any functions you'd like to add (other than update / draw ) ?
// yeah we'll do that with the property system

// alright, so just the "defaults" I guess

// this is important, everything we wanna add to Gbl's type system needs to be registered, so we need to make this function:

GblType POP_Anim_type(void); // will implement in the .c file later

GBL_RESULT POP_Anim_update(void);
GBL_RESULT POP_Anim_draw(void);

// todo so I don't forget lol
// TODO: add functions to change props later

#define POP_Anim_create(...) GBL_NEW(POP_Anim __VA_OPT__(,) __VA_ARGS__)

GBL_DECLS_END
#undef GBL_SELF_TYPE

#endif

// That's actually it for this .h file! we just need to implement it.

// #define GBL_NIL_TYPE        (GBL_BUILTIN_TYPE(NIL))     //!< Builtin ID for nil GblVariant type
// #define GBL_BOOL_TYPE       (GBL_BUILTIN_TYPE(BOOL))    //!< Builtin ID for boolean GblVariant type
// #define GBL_CHAR_TYPE       (GBL_BUILTIN_TYPE(CHAR))    //!< Builtin ID for char GblVariant type
// #define GBL_UINT8_TYPE      (GBL_BUILTIN_TYPE(UINT8))   //!< Builtin ID for uint8_t GblVariant type
// #define GBL_INT16_TYPE      (GBL_BUILTIN_TYPE(INT16))   //!< Builtin ID for int16_t GblVariant type
// #define GBL_UINT16_TYPE     (GBL_BUILTIN_TYPE(UINT16))  //!< Builtin ID for uint16_t GblVariant type
// #define GBL_INT32_TYPE      (GBL_BUILTIN_TYPE(INT32))   //!< Builtin ID for int32_t GblVariant type
// #define GBL_UINT32_TYPE     (GBL_BUILTIN_TYPE(UINT32))  //!< Builtin ID for uint32_t GblVariant type
// #define GBL_INT64_TYPE      (GBL_BUILTIN_TYPE(INT64))   //!< Builtin ID for int64_t GblVariant type
// #define GBL_UINT64_TYPE     (GBL_BUILTIN_TYPE(UINT64))  //!< Builtin ID for uint64_t GblVariant type
// #define GBL_FLOAT_TYPE      (GBL_BUILTIN_TYPE(FLOAT))   //!< Builtin ID for float GblVariant type
// #define GBL_DOUBLE_TYPE     (GBL_BUILTIN_TYPE(DOUBLE))  //!< Builtin ID for double GblVariant type
// #define GBL_STRING_TYPE     (GBL_BUILTIN_TYPE(STRING))  //!< Builtin ID for string GblVariant type
// #define GBL_TYPE_TYPE       (GBL_TYPEID(GblType))       //!< Builtin ID for ::GblType GblVariant type
// #define GBL_BITMASK_TYPE    (GBL_TYPEID(GblBitMask))
