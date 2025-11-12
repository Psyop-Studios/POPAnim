#ifndef POP_ANIM_H
#define POP_ANIM_H

#include "../3rdpartylibs/libgimbal/lib/api/gimbal/gimbal_meta.h" // file needed for type system
#include "POPTexture.h"
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
    bool Boomerang;
	bool Forward;
    bool Active;
	Vector2 Position;
    float FPS;
    float Rotation;
    float Scale;
    float RealTimer;
    Color Color;
	Texture2D *textures; 
	uint8_t frames;
	uint8_t currentFrame;
GBL_INSTANCE_END

GBL_PROPERTIES(POP_Anim,
	(boomerang, GBL_GENERIC, (READ, WRITE), GBL_BOOL_TYPE),
    (active, GBL_GENERIC, (READ, WRITE), GBL_BOOL_TYPE),
    (speed, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),	
	(scale, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),
    (rotation, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),
    (x, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),
	(y, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),
	(frames, GBL_GENERIC, (READ, WRITE), GBL_UINT8_TYPE),
	(textures, GBL_GENERIC, (READ, WRITE), POP_TEXTURE_TYPE)
)

GblType POP_Anim_type(void);

GBL_RESULT POP_Anim_update(void);
GBL_RESULT POP_Anim_draw(void);

// todo so I don't forget lol
// TODO: add functions to change props later

#define POP_Anim_create(...) GBL_NEW(POP_Anim __VA_OPT__(,) __VA_ARGS__)

GBL_DECLS_END
#undef GBL_SELF_TYPE

#endif