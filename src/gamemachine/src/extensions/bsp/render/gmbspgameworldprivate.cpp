﻿#include "stdafx.h"
#include "gmbspgameworld.h"
#include "foundation/utilities/tools.h"
#include "gmengine/gameobjects/gmspritegameobject.h"

#define EACH_PAIR_OF_ENTITY(entity, pair) GMBSPEPair* pair = entity.epairs; for (; pair; pair = pair->next)

namespace
{
	GMString getClassname(const GMBSPEntity& entity)
	{
		GMBSPEPair* e = entity.epairs;
		while (e)
		{
			if (e->key == "classname")
				return e->value;
			e = e->next;
		}
		return "";
	}

	void import_worldspawn(const GMBSPEntity& entity, GMBSPGameWorld* world)
	{
		world->setDefaultLights();
	}

	void import_info_player_deathmatch(const GMBSPEntity& entity, GMBSPGameWorld* world)
	{
		static bool created = false; //TODO
		gm_info(_L("found playerstart"));

		if (created)
			return;

		BSPVector3 origin = BSPVector3(0);
		GMfloat yaw = 0;

		EACH_PAIR_OF_ENTITY(entity, e)
		{
			std::string value = e->value.toStdString();
			Scanner s(value.c_str());
			if (e->key == "origin")
			{
				s.nextFloat(&origin[0]);
				s.nextFloat(&origin[1]);
				s.nextFloat(&origin[2]);
			}
			else if (e->key == "angle")
			{
				s.nextFloat(&yaw);
			}
		}

		GMSpriteGameObject* sprite = new GMSpriteGameObject(6, glm::vec3(0, 10, 0));
		sprite->setPhysicsObject(world->getPhysicsWorld()->createPhysicsObject());
		world->addObjectAndInit(sprite);

		GMBSPPhysicsObject* physics = gmBSPPhysicsObjectCast(sprite->getPhysicsObject());

		GMMotionProperties& prop = physics->motions();
		physics->motions().translation = glm::vec3(origin[0], origin[2], -origin[1]);
		physics->motions().moveSpeed = glm::vec3(293);
		physics->motions().jumpSpeed = glm::vec3(0, 150, 0);
		physics->shapeProperties().stepHeight = 18.f;
		physics->shapeProperties().bounding[0] = glm::vec3(-15, -35, -15);
		physics->shapeProperties().bounding[1] = glm::vec3(15, 35, 15);
		created = true;
	}
}

void BSPGameWorldEntityReader::import(const GMBSPEntity& entity, GMBSPGameWorld* world)
{
	const GMString& classname = getClassname(entity);

	if (classname == "worldspawn")
		import_worldspawn(entity, world);
	else if (classname == "info_player_deathmatch")
		import_info_player_deathmatch(entity, world);
}