#pragma once

#include "../Agents/Enemy.h"
#include "../Agents/Player.h"
#include <Events/Events/CollisionEvent.h>
#include <Events/Subscribers/CollisionResponseSubscriber.h>
#include <Events/TemplateEventSubscriber.h>

using PlayerEnemy = Barta::CollisionEvent<Player, Enemy>;

SUBSCRIBER_INTERFACE_DEFINITION(PlayerEnemy);

using PlayerEnemySubscriberInterface = Barta::EventSubscriber<PlayerEnemy>;
