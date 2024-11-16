//
// Created by bartanakin on 11/16/24.
//

#pragma once
#include "../Events/PlayerEnemyCollisionEvent.h"

class EnemyAttackSubscriber: public virtual PlayerEnemySubscriberInterface {
public:
    EnemyAttackSubscriber() = default;

    bool handle(PlayerEnemy& event) override;

    bool isValid() const noexcept override;

private:
};
