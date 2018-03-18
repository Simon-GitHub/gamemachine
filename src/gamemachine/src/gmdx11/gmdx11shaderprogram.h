﻿#ifndef __GMDX11SHADERPROGRAM_H__
#define __GMDX11SHADERPROGRAM_H__
#include <gmcommon.h>
#include <gmcom.h>
#include <gmdxincludes.h>
BEGIN_NS

GM_PRIVATE_OBJECT(GMDx11EffectShaderProgram)
{
	GMComPtr<ID3DX11Effect> effect;
};

class GMDx11EffectShaderProgram : public IShaderProgram
{
	DECLARE_PRIVATE(GMDx11EffectShaderProgram)

public:
	GMDx11EffectShaderProgram(GMComPtr<ID3DX11Effect> effect);

public:
	virtual void useProgram() override;
	virtual void setMatrix4(const char* name, const GMMat4& value) override;
	virtual void setVec4(const char* name, const GMFloat4&) override;
	virtual void setVec3(const char* name, const GMfloat value[3]) override;
	virtual void setInt(const char* name, GMint value) override;
	virtual void setFloat(const char* name, GMfloat value) override;
	virtual void setBool(const char* name, bool value) override;

public:
	virtual bool getInterface(GameMachineInterfaceID id, void** out) override;
	virtual bool setInterface(GameMachineInterfaceID id, void* in) override;
};

END_NS
#endif