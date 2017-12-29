﻿#ifndef __EVENT_ENUM
#define __EVENT_ENUM
BEGIN_NS

#define GM_SET_PROPERTY_EVENT_ENUM(name) GMEVENT_SET_##name
#define GM_CONTROL_EVENT_ENUM(name) GMEVENT_UI_##name

enum __ProperyChangedEvents
{
	// GMLight
	GM_SET_PROPERTY_EVENT_ENUM(Type),

	// GMTextureFrames
	GM_SET_PROPERTY_EVENT_ENUM(FrameCount),
	GM_SET_PROPERTY_EVENT_ENUM(AnimationMs),
	GM_SET_PROPERTY_EVENT_ENUM(MagFilter),
	GM_SET_PROPERTY_EVENT_ENUM(MinFilter),
	GM_SET_PROPERTY_EVENT_ENUM(WrapS),
	GM_SET_PROPERTY_EVENT_ENUM(WrapT),

	// Shader
	GM_SET_PROPERTY_EVENT_ENUM(SurfaceFlag),
	GM_SET_PROPERTY_EVENT_ENUM(Cull),
	GM_SET_PROPERTY_EVENT_ENUM(FrontFace),
	GM_SET_PROPERTY_EVENT_ENUM(BlendFactorSource),
	GM_SET_PROPERTY_EVENT_ENUM(BlendFactorDest),
	GM_SET_PROPERTY_EVENT_ENUM(Blend),
	GM_SET_PROPERTY_EVENT_ENUM(Nodraw),
	GM_SET_PROPERTY_EVENT_ENUM(NoDepthTest),
	GM_SET_PROPERTY_EVENT_ENUM(Texture),
	GM_SET_PROPERTY_EVENT_ENUM(LineWidth),
	GM_SET_PROPERTY_EVENT_ENUM(LineColor),
	GM_SET_PROPERTY_EVENT_ENUM(DrawBorder),
	GM_SET_PROPERTY_EVENT_ENUM(Material),

	// GMParticles
	GM_SET_PROPERTY_EVENT_ENUM(CurrentLife),
	GM_SET_PROPERTY_EVENT_ENUM(MaxLife),
	GM_SET_PROPERTY_EVENT_ENUM(Color),
	GM_SET_PROPERTY_EVENT_ENUM(Transform),

	// GMControlGameObject
	GM_SET_PROPERTY_EVENT_ENUM(Stretch),

	__LastPropertyEvent,
};

enum __UIEvents
{
	__FirstUIEvent = __LastPropertyEvent,
	GM_CONTROL_EVENT_ENUM(MouseHover),
	GM_CONTROL_EVENT_ENUM(MouseLeave),
	GM_CONTROL_EVENT_ENUM(MouseDown),
};

END_NS
#endif