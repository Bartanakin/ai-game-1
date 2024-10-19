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

Barta::Vector2f Player::getPosition() const {
    return this->graphicsData.transformable->getPosition();
}

Barta::Vector2f Player::getDirection() const {
    return this->direction;
}

void Player::setDirection(
    Barta::Vector2f direction
) {
    this->setRotation(std::atan2(direction.y, direction.x) * 180.f / M_PI + 90.f);
    this->dynamicsDTO.velocity = this->dynamicsDTO.velocity.rotated(this->direction.angleTo(direction));

    this->direction = direction;
}
