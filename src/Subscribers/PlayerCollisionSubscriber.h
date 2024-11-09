//
// Created by bartanakin on 10/19/24.
//

#pragma once
#include "../Events/PlayerWallCollisionEvent.h"

class PlayerCollisionSubscriber: public PlayerWallSubscriber {
public:
    bool handle(PlayerWall& event) override;

    bool isValid() const noexcept override;
};
