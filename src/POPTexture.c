#include "POPTexture.h"

GblType POP_Texture_type(void) {
	static GblType type = GBL_INVALID_TYPE; // no, this LoC is not actually here.
	// it's the same as doing this:

	// not TRULY the same, because this variable is ONLY ACCESSIBLE in this function, so it's not "global"
	// but its lifetime is
	// however, assignment is only ever run once
	// yes, static keyword does that
	// not exactly global as I said, but it works like one whenever you're inside this function

	if (type == GBL_INVALID_TYPE) {
		type = GblPointer_register("POP_Texture");
	}

	// when the function gets called a 2nd time or after that
	// basically anytime that's not the first call

	// sorry say again? was distracted
	return type;
}

// this is literally all we need lol. that easy to register a type