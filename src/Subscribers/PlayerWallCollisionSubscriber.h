#pragma once

#include <Events/Events/CollisionEvent.h>
#include <Events/Subscribers/CollisionResponseSubscriber.h>
#include <Events/TemplateEventSubscriber.h>
#include <Objects/Rigid/RigidObject.h>
#include "../Agents/Player.h"
#include "../Agents/Wall.h"

using PlayerWall = Barta::CollisionEvent<Player, Wall>;

SUBSCRIBER_INTERFACE_DEFINITION(PlayerWall);

using PlayerWallSubscriber = Barta::EventSubscriber<PlayerWall>;
