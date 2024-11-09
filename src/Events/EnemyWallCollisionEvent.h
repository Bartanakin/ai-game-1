#pragma once

#include "../Agents/Enemy.h"
#include "../Agents/Wall.h"
#include <Events/Events/CollisionEvent.h>
#include <Events/Subscribers/CollisionResponseSubscriber.h>
#include <Events/TemplateEventSubscriber.h>

using EnemyWall = Barta::CollisionEvent<Enemy, Wall>;

SUBSCRIBER_INTERFACE_DEFINITION(EnemyWall);

using EnemyWallSubscriberInterface = Barta::EventSubscriber<EnemyWall>;
