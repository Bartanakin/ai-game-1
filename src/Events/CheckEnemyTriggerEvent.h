//
// Created by bartanakin on 11/16/24.
//

#pragma once
#include "../Agents/Enemy.h"
#include <Events/TemplateEventSubscriber.h>
#include <StaticObjectManager.h>

class CheckEnemyTriggerEvent {
    using EnemyList = Barta::ListType<Enemy>;

public:
    CheckEnemyTriggerEvent(
        EnemyList& enemies
    ) noexcept:
        enemies(enemies) {}

    EnemyList& enemies;
};

SUBSCRIBER_INTERFACE_DEFINITION(CheckEnemyTriggerEvent);

typedef Barta::EventSubscriber<CheckEnemyTriggerEvent> CheckEnemyTriggerSubscriberInterface;
