//
// Created by bartanakin on 10/12/24.
//

#include "Player.h"

Player::Player(
    Barta::GraphicsData graphicsData,
    std::unique_ptr<Barta::HitboxInterface> hitbox,
    Barta::DynamicsDTO dynamicsDto
):
    RigidObject(std::move(graphicsData), std::move(hitbox), dynamicsDto) {}
