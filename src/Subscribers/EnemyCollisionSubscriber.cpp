//
// Created by bartanakin on 11/2/24.
//

#include "EnemyCollisionSubscriber.h"

bool EnemyCollisionSubscriber::handle(
    EnemyWall& event
) {
    return false;
}

bool EnemyCollisionSubscriber::isValid() const noexcept {
    return true;
}
