//
// Created by bartanakin on 10/19/24.
//

#pragma once
#include "PlayerWallCollisionSubscriber.h"

class PlayerCollisionSubscriber: public PlayerWallSubscriber {
public:
    bool handle(PlayerWall& event) override;

    bool isValid() const noexcept override;
};
