#include "render.h"

void* RACK::getResource(ResourceType type, string s) {
	switch (type)
	{
	case CONSTANTBUFFER:
		return map1[s];
	case SAMPLER:
		return map2[s];
	case CSHADER:
		return map6[s];
	case DSHADER:
		return map8[s];
	case GSHADER:
		return map4[s];
	case HSHADER:
		return map7[s];
	case PSHADER:
		return map5[s];
	case VSHADER:
		return map3[s];
	case SHADERRESOURCE:
		return map9[s];
	case UAV:
		return map10[s];
	case INPUTLAYOUT:
		return map11[s];
	case BLENDSTATE:
		return map12[s];
	case DEPTHSTENCILVIEW:
		return map13[s];
	case RENDERTARGET:
		return map14[s];
	case SCISSORRECTS:
		return map15[s];
	case STATE:
		return map16[s];
	case VIEWPORTS:
		return map17[s];
	case DEPTHSTENCILSTATE:
		return map18[s];
	}
	return 0;
}
RACK::~RACK()
{
	for (auto i = map1.begin(); i != map1.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map2.begin(); i != map2.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map3.begin(); i != map3.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map4.begin(); i != map4.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map5.begin(); i != map5.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map6.begin(); i != map6.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map7.begin(); i != map7.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map8.begin(); i != map8.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map9.begin(); i != map9.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map10.begin(); i != map10.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map11.begin(); i != map11.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map12.begin(); i != map12.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map13.begin(); i != map13.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map14.begin(); i != map14.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map15.begin(); i != map15.end(); ++i)
	{
		delete ((i)->second);
	}
	for (auto i = map16.begin(); i != map16.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	for (auto i = map17.begin(); i != map17.end(); ++i)
	{
		delete ((i)->second);
	}
	for (auto i = map18.begin(); i != map18.end(); ++i)
	{
		if (*((i)->second)) { (*((i)->second))->Release(); }
		delete ((i)->second);
	}
	delete[] info;
}
RACK::RACK(INT16 n) :num_of_objects{ n } {
	info = new VERTEXBUFFERINFO[num_of_objects];
}