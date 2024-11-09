//
// Created by bartanakin on 10/19/24.
//

#include "PlayerCollisionSubscriber.h"

bool PlayerCollisionSubscriber::handle(
    PlayerWall& event
) {
    // event.getTestResult().object1->getDynamicsDTO().velocity = {};
    // event.getTestResult().object1->getWallNormVectors().push_back(event.getTestResult().collisionTestResult.normVector);

    return true;
}

bool PlayerCollisionSubscriber::isValid() const noexcept {
    return true;
}
