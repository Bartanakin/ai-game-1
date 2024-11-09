#pragma once

#include "../Agents/Player.h"
#include "../Agents/Wall.h"
#include <Events/Events/CollisionEvent.h>
#include <Events/Subscribers/CollisionResponseSubscriber.h>
#include <Events/TemplateEventSubscriber.h>

using PlayerWall = Barta::CollisionEvent<Player, Wall>;

SUBSCRIBER_INTERFACE_DEFINITION(PlayerWall);

using PlayerWallSubscriber = Barta::EventSubscriber<PlayerWall>;
