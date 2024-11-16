//
// Created by bartanakin on 11/16/24.
//

#include "EnemyAttackSubscriber.h"

bool EnemyAttackSubscriber::handle(
    PlayerEnemy& event
) {
    auto& player = event.collisionResult.object1;
    auto& enemy = event.collisionResult.object2;
    if (player->isToBeDeleted() || enemy->isToBeDeleted()) {
        return true;
    }

    if (!enemy->tryToShoot()) {
        return false;
    }

    player->receiveShot();

    return false;
}

bool EnemyAttackSubscriber::isValid() const noexcept {
    return true;
}
