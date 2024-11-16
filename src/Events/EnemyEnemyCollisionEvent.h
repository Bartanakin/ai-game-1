#pragma once

#include "../Agents/Enemy.h"
#include <Events/Events/CollisionEvent.h>
#include <Events/Subscribers/CollisionResponseSubscriber.h>
#include <Events/TemplateEventSubscriber.h>

using EnemyEnemy = Barta::CollisionEvent<Enemy, Enemy>;

SUBSCRIBER_INTERFACE_DEFINITION(EnemyEnemy);

using EnemyEnemySubscriberInterface = Barta::EventSubscriber<EnemyEnemy>;
