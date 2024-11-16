//
// Created by bartanakin on 10/12/24.
//

#include "Player.h"
#include <Graphics/SpriteBuilder/SpriteMerger.h>

Player::Player(
    Barta::GraphicsData graphicsData,
    std::unique_ptr<Barta::HitboxInterface> hitbox,
    Barta::DynamicsDTO dynamicsDto,
    Barta::GraphicsData marker
):
    RigidObject(std::move(graphicsData), std::move(hitbox), dynamicsDto),
    marker(std::move(marker)),
    lastShot(std::chrono::steady_clock::now()),
    health(Player::INITIAL_HEALTH) {}

Barta::GraphicsDataAwareInterface::GraphicsDataList Player::getGraphicsData() {
    auto graphicsList = RigidObject::getGraphicsData();

    Barta::Color color = {255, static_cast<unsigned char>(255 / (Player::INITIAL_HEALTH - 1) * (this->health - 1)), 0};
    auto triangleSprite = Barta::TriangleSprite(
        {
            {10.f, 0.f },
            {0.f,  24.f},
            {20.f, 24.f}
    },
        color,
        color,
        color
    );
    auto merger = Barta::SpriteMerger();
    merger.addTriangle(triangleSprite);
    this->graphicsData.resource = merger.merge(false);
    graphicsList.push_back(&this->marker);

    return graphicsList;
}

Barta::Vector2f Player::getPosition() const {
    return this->graphicsData.transformable->getPosition();
}

Barta::Vector2f Player::getDirection() const {
    return this->direction;
}

void Player::setDirection(
    Barta::Vector2f direction
) {
    this->direction = direction;
}

bool Player::tryToShoot() noexcept {
    auto now = std::chrono::steady_clock::now();
    if (now - this->lastShot > Player::RELOAD_TIME) {
        this->lastShot = now;

        return true;
    }

    return false;
}

void Player::receiveShot() {
    this->health--;
}
