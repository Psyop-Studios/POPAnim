#include "POPAnim.h"


static GBL_RESULT POP_Anim_init_(GblInstance *pInstance) {
	POP_Anim *pSelf = POP_ANIM(pInstance);

	pSelf->Boomerang = false;
    pSelf->Active = true;
    pSelf->Position = (Vector2){0, 0}; // that's fine!
    pSelf->FPS = 6;
    pSelf->Rotation = 0;
    pSelf->Scale = 1;
    pSelf->RealTimer = 1 / 10;
    pSelf->Color = WHITE;
	//pSelf->textures = TODO[]
	pSelf->frames = 0;
	pSelf->currentFrame = 0;
	return GBL_RESULT_SUCCESS;
}

static GBL_RESULT POP_Anim_setProperty_(GblObject *pObject, const GblProperty *pProp, GblVariant *pValue) {
	POP_Anim *pSelf = POP_ANIM(pObject);

	switch(pProp->id) {
		case POP_Anim_Property_Id_boomerang:
			GblVariant_valueCopy(pValue, &pSelf->Boomerang);
			break;
        case POP_Anim_Property_Id_x:
			GblVariant_valueCopy(pValue, &pSelf->Position.x);
			break;
        case POP_Anim_Property_Id_y:
			GblVariant_valueCopy(pValue, &pSelf->Position.y);
			break;
        case POP_Anim_Property_Id_speed:
			GblVariant_valueCopy(pValue, &pSelf->FPS);
			break;
        case POP_Anim_Property_Id_active:
			GblVariant_valueCopy(pValue, &pSelf->Active);
			break;
        case POP_Anim_Property_Id_scale:
			GblVariant_valueCopy(pValue, &pSelf->Scale);
			break;
        case POP_Anim_Property_Id_rotation:
			GblVariant_valueCopy(pValue, &pSelf->Rotation);
			break; // we don't have a texture prop yet, because you'd need to register the Texture type into libGimbal's type system, we can do that in a sec
		case POP_Anim_Property_Id_frames:
			GblVariant_valueCopy(pValue, &pSelf->frames);
			break; 
		case POP_Anim_Property_Id_textures:
			GblVariant_valueCopy(pValue, &pSelf->textures); // wherever we allocate our memory for our anims will need to be in the heap, yes.
			// not necessarilly, there are a lot of ways of doing
			// right, I was gonna say, libGimbal has a lot of custom allocators we can use
			// much, MUCH faster than malloc()
			// yes, we will be ref counting our anims
			// do you know what that is?

			// yup. basically, we have a counter of how many instances of this particular anim are "alive", or being used.
			// everytime someone over at the game's code (outside this lib) creates or loads an anim, we increase that ref counter by 1
			// when it brings 0, we know we can free it
			// we are responsible for it, but libGimbal facilitates it
			// yeah, pretty much
			// in fact, follow me for a sec

			break; // :D
		default:
			printf("you're stupid and tried to set a property that doesn't exist! :cuck: \n"); // nice touch
			return GBL_RESULT_ERROR_INVALID_PROPERTY;
	}

	return GBL_RESULT_SUCCESS;
}

// sorry I got distracted, what are you guys talking about?
// something about loading textures

// not necessarily! it'll work with texture2ds just fine
// yeah, it's just a void*
// that's why I said props don't need to map to real data! exactly!

static GBL_RESULT POP_Anim_property_(const GblObject *pObject, const GblProperty *pProp, GblVariant *pValue) {
	POP_Anim *pSelf = POP_ANIM(pObject); // p stands for pointer, it's a naming convention

	switch (pProp->id) {
		case POP_Anim_Property_Id_boomerang:
			GblVariant_setBool(pValue, pSelf->Boomerang);
			break;
        case POP_Anim_Property_Id_speed:
			GblVariant_setFloat(pValue, pSelf->FPS);
			break;
        case POP_Anim_Property_Id_active:
			GblVariant_setBool(pValue, pSelf->Active);
			break;
        case POP_Anim_Property_Id_scale:
			GblVariant_setFloat(pValue, pSelf->Scale);
			break;
        case POP_Anim_Property_Id_rotation:
			GblVariant_setFloat(pValue, pSelf->Rotation);
			break;
        case POP_Anim_Property_Id_x:
			GblVariant_setFloat(pValue, pSelf->Position.x);
			break;
        case POP_Anim_Property_Id_y:
			GblVariant_setFloat(pValue, pSelf->Position.y);
			break;
		case POP_Anim_Property_Id_frames:
			GblVariant_setUint8(pValue, pSelf->frames); // this is fine
			break;
		case POP_Anim_Property_Id_textures:
			GblVariant_setPointer(pValue, POP_TEXTURE_TYPE, pSelf->textures);
			break;
		default: 
			printf("you're stupid and tried to read a property that doesn't exist! :cuck: \n"); // nice touch
			return GBL_RESULT_ERROR_INVALID_PROPERTY; 
	}

	return GBL_RESULT_SUCCESS;
}

GBL_RESULT POP_Anim_update_(POP_Anim *pSelf) {
	if(pSelf->Active){
		
		if(pSelf->Boomerang){
			// LMFAO
			// pro tip: do this:
			
			// REMEMBER CURRENT FRAME IS U8, 0 - 1 = 255

			// @Cypress dunno if you remember, but we dealt with this EXACT SAME problem in
			// BeachBox VMU animations lol
			// ding!

			if(pSelf->currentFrame + (pSelf->Forward ? 1 : -1) >= pSelf->frames) pSelf->Forward = !pSelf->Forward;
			pSelf->currentFrame += pSelf->Forward ? 1 : -1;
			
			
		} else {
			pSelf->currentFrame = (pSelf->currentFrame + 1) % pSelf->frames;
		}


	}

	// here's another looping example that avoids branching
	// I mean, making a new variable would mean you're using more RAM, per animation
	// if the solution isn't *too* complex, I'd say not having to make a new variable is good
	// specially since this is a lib we'll be using for our games
	// not at all! I was surprised on how little work it is to implement different backends.
	// you just need to do some work at first to make it all abstract, then it's smooth sailing
	// with a project as small as this one, it'll be easy
	// yeah go ahead

	// int max = pSelf->frames;  // Upper bound (oscillate between 0 and max)
    // int period = 2 * max;  // Full cycle length: 6
    // int i = max;  // Start at max to begin sequence at 0 going upward
    
    // for (int count = 0; count < 20; count++) {
    //     int value = abs(i - max);  // Compute oscillating value
    //     printf("%d\n", value);
        
    //     i = (i + 1) % period;  // Increment and wrap with modulo
    // }
	
	return GBL_RESULT_SUCCESS;
}

GBL_RESULT POP_Anim_draw_(POP_Anim *pSelf) {
	if(pSelf->Active) {
		DrawTextureEx(pSelf->textures[pSelf->currentFrame], pSelf->Position, pSelf->Rotation, pSelf->Scale, pSelf->Color);
	}
	return GBL_RESULT_SUCCESS;
}

static GBL_RESULT POP_AnimClass_init_(GblClass *pClass, const void *pData) {
	GBL_UNUSED(pData);

	if (!GblType_classRefCount(POP_ANIM_TYPE)) GBL_PROPERTIES_REGISTER(POP_Anim);

	GBL_OBJECT_CLASS(pClass)->pFnSetProperty = POP_Anim_setProperty_;
	GBL_OBJECT_CLASS(pClass)->pFnProperty 	 = POP_Anim_property_;


	POP_ANIM_CLASS(pClass)->pFnUpdate 		= POP_Anim_update_;
	POP_ANIM_CLASS(pClass)->pFnDraw 		= POP_Anim_draw_;

	return GBL_RESULT_SUCCESS;
}


GblType POP_Anim_type(void) {
	static GblType type = GBL_INVALID_TYPE;

	if (type == GBL_INVALID_TYPE) {
		type = GblType_register(GblQuark_internStatic("POP_Anim"), // name of the type
								GBL_OBJECT_TYPE, // type you're inheriting from
								// the type information.
								&(static GblTypeInfo){.classSize = sizeof(POP_AnimClass),  // size of class
													  .pFnClassInit = POP_AnimClass_init_, // pointer to the init function of the class (called when the very first instance of this class gets created)
													  .pFnInstanceInit = POP_Anim_init_,   // pointer to the init function of the instance (called EVERYTIME an instance is created)
													  .instanceSize = sizeof(POP_Anim)},   // the size of the instance
								GBL_TYPE_FLAG_TYPEINFO_STATIC); // dont worry about this for now lol
	}

	return type;
}