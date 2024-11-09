//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include "../Events/EnemyWallCollisionEvent.h"

class EnemyCollisionSubscriber: public virtual EnemyWallSubscriberInterface {
public:
    bool handle(EnemyWall& event) override;

    bool isValid() const noexcept override;

private:
};
