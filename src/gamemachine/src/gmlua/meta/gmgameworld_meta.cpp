﻿#include "stdafx.h"
#include "gmgameworld_meta.h"
#include <gamemachine.h>
#include <gmlua.h>
#include "irendercontext_meta.h"
#include "gmgameobject_meta.h"

BEGIN_NS

namespace luaapi
{

#define NAME "GMGameWorld"

	GM_PRIVATE_OBJECT_UNALIGNED(GMGameWorldProxy)
	{
		GM_LUA_PROXY_FUNC(renderScene);
		GM_LUA_PROXY_FUNC(addObjectAndInit);
		GM_LUA_PROXY_FUNC(addToRenderList);
	};

	bool GMGameWorldProxy::registerMeta()
	{
		GM_META_FUNCTION(renderScene);
		GM_META_FUNCTION(addObjectAndInit);
		GM_META_FUNCTION(addToRenderList);
		return Base::registerMeta();
	}

	GMGameWorldProxy::GMGameWorldProxy(GMLuaCoreState* l, GMObject* handler /*= nullptr*/)
		: Base(l, handler)
	{
		GM_CREATE_DATA();
	}

	/*
	 * renderScene([self])
	 */
	GM_LUA_PROXY_IMPL(GMGameWorldProxy, renderScene)
	{
		static const GMString s_invoker = NAME ".renderScene";
		GM_LUA_CHECK_ARG_COUNT(L, 1, NAME ".renderScene");
		GMGameWorldProxy self(L);
		GMArgumentHelper::popArgumentAsObject(L, self, s_invoker); //self
		if (self)
			self->renderScene();
		return gm::GMReturnValues();
	}

	/*
	 * addObjectAndInit([self], GMObject)
	 */
	GM_LUA_PROXY_IMPL(GMGameWorldProxy, addObjectAndInit)
	{
		static const GMString s_invoker = NAME ".addObjectAndInit";
		GM_LUA_CHECK_ARG_COUNT(L, 2, NAME ".addObjectAndInit");
		GMGameWorldProxy self(L);
		GMGameObjectProxy gameobject(L);
		GMArgumentHelper::popArgumentAsObject(L, gameobject, s_invoker); //GMObject
		GMArgumentHelper::popArgumentAsObject(L, self, s_invoker); //self
		if (self)
		{
			self->addObjectAndInit(gameobject.get());
			gameobject.setAutoRelease(false);
		}
		return gm::GMReturnValues();
	}

	/*
	 * addToRenderList([self], GMObject)
	 */
	GM_LUA_PROXY_IMPL(GMGameWorldProxy, addToRenderList)
	{
		static const GMString s_invoker = NAME ".addToRenderList";
		GM_LUA_CHECK_ARG_COUNT(L, 2, NAME ".addToRenderList");
		GMGameWorldProxy self(L);
		GMGameObjectProxy gameobject(L);
		GMArgumentHelper::popArgumentAsObject(L, gameobject, s_invoker); //GMObject
		GMArgumentHelper::popArgumentAsObject(L, self, s_invoker); //self
		if (self)
			self->addToRenderList(gameobject.get());
		return gm::GMReturnValues();
	}
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		// {{BEGIN META FUNCTION}}
		GM_LUA_NEW_IMPL_ARG(New, NAME ".new", GMGameWorldProxy, GMGameWorld, IRenderContextProxy);
		// {{END META FUNCTION}}

		GMLuaReg g_meta[] = {
			// {{BEGIN META DECLARATIONS}}
			{ "new", New },
			// {{END META DECLARATIONS}}
			{ 0, 0 }
		};
	}

	GM_LUA_REGISTER_IMPL(GMGameWorld_Meta, NAME, g_meta);
}

END_NS