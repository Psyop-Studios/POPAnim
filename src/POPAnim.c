#include "POPAnim.h"


static GBL_RESULT POP_Anim_init_(GblInstance *pInstance) {
	POP_Anim *pSelf = POP_ANIM(pInstance);

	// here we can initialize variables to whatever we want the default values to be
	// notice how I cast GblInstance *pInstance to *pSelf (POP_Anim)
	// that way, we have access to this stuff:

	pSelf->Boomerang = false;
    pSelf->Active = true;
    pSelf->Position = (Vector2){0, 0}; // that's fine!
    pSelf->FPS = 6;
    pSelf->Rotation = 0;
    pSelf->Scale = 1;
    pSelf->RealTimer = 1 / 10;
    pSelf->Color = RAYWHITE;

	return GBL_RESULT_SUCCESS;
}

// cool, so we now need to handle props
// there are two separate property functions: set and read

// set
static GBL_RESULT POP_Anim_setProperty_(GblObject *pObject, const GblProperty *pProp, GblVariant *pValue) {
	POP_Anim *pSelf = POP_ANIM(pObject);

	// GBL_PROPERTIES(POP_Anim,
// 		(boomerang, GBL_GENERIC, (READ, WRITE), GBL_BOOL_TYPE),
//     (active, GBL_GENERIC, (READ, WRITE), GBL_BOOL_TYPE),
//     (speed, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),
// 		(scale, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),
//     (rotation, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),
//     (x, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE),
// 		(y, GBL_GENERIC, (READ, WRITE), GBL_FLOAT_TYPE)  
// )

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
			// this is wrong!
			break;
		default:
			printf("you're stupid and tried to set a property that doesn't exist! :cuck: \n"); // nice touch
			return GBL_RESULT_ERROR_INVALID_PROPERTY;
	}

	// we done?
	// kk, we need to handle setting them now
	// oh, you can handle position as a whole, but it's a bit more complex. you need to register Vector2 as a libGimbal type
	// we can do that later
	// yup, a bit more complex but nothing too crazy
	// let's finish this first though

	return GBL_RESULT_SUCCESS;
}

// read
static GBL_RESULT POP_Anim_property_(const GblObject *pObject, const GblProperty *pProp, GblVariant *pValue) {
	POP_Anim *pSelf = POP_ANIM(pObject);

	// we need to handle reading*

	// this is the same thing, but the other way around: the passed pValue gets written to, reading from the passed pProp
	// not exactly : valueCopy doesn't work here. you need to use GblVariant_setXXXXX
	// yeah
	// setFloat, setUint8, setintxx etc.
	

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
		default: 
			printf("you're stupid and tried to read a property that doesn't exist! :cuck: \n"); // nice touch
			break;

	}

	return GBL_RESULT_SUCCESS;
}

GBL_RESULT POP_Anim_activate_(POP_Anim *pSelf) {
	return GBL_RESULT_SUCCESS;
}

GBL_RESULT POP_Anim_deactivate_(POP_Anim *pSelf) {
	return GBL_RESULT_SUCCESS;
}

GBL_RESULT POP_Anim_update_(POP_Anim *pSelf) {
	return GBL_RESULT_SUCCESS;
}

GBL_RESULT POP_Anim_draw_(POP_Anim *pSelf) {
	return GBL_RESULT_SUCCESS;
}

static GBL_RESULT POP_AnimClass_init_(GblClass *pClass, const void *pData) {
	GBL_UNUSED(pData);

	if (!GblType_classRefCount(POP_ANIM_TYPE)) GBL_PROPERTIES_REGISTER(POP_Anim);

	GBL_OBJECT_CLASS(pClass)->pFnSetProperty = POP_Anim_setProperty_;
	GBL_OBJECT_CLASS(pClass)->pFnProperty 	 = POP_Anim_property_;

	POP_ANIM_CLASS(pClass)->pFnActivate 	= POP_Anim_activate_;
	POP_ANIM_CLASS(pClass)->pFnDeactivate 	= POP_Anim_deactivate_;
	POP_ANIM_CLASS(pClass)->pFnUpdate 		= POP_Anim_update_;
	POP_ANIM_CLASS(pClass)->pFnDraw 		= POP_Anim_draw_;

	return GBL_RESULT_SUCCESS;
}


GblType POP_Anim_type(void) {
	static GblType type = GBL_INVALID_TYPE;

	// will explain in a sec


	// okay so.
	// the internal libGimbal fuckery magic needs to know these things about our new type, so it knows how to handle it


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