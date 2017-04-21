#include <GL/Platform.hpp>
#include <glad/glad.h>

static bool hasTested = false;
static bool DSASupport;
static bool BindlessSupport;
static bool PersistentMapSupport;
static bool MultiDrawSupport;
static bool MultiDrawCountSupport;
static bool SparseSupported;

inline static void CheckTest()
{
	if (hasTested)
		return;

	BindlessSupport = glad_glMakeTextureHandleResidentARB != nullptr;
	PersistentMapSupport = glad_glMapBufferRange != nullptr;
	MultiDrawSupport = glad_glMultiDrawElementsIndirect != nullptr;
	MultiDrawCountSupport = glad_glMultiDrawElementsIndirectCountARB != nullptr;
	SparseSupported = glad_glTexPageCommitmentARB != nullptr;
	hasTested = true;
}

/*
bool GL::SupportsDSA()
{
	CheckTest();
	return DSASupport;
}

bool GL::SupportsBindless()
{
	CheckTest();
	return BindlessSupport;
}

bool GL::SupportsSparseTextures()
{
	CheckTest();
	return SparseSupported;
}*/
