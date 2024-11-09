//
// Created by bartanakin on 10/12/24.
//

#include "PlayerMovementSubscriber.h"

PlayerMovementSubscriber::PlayerMovementSubscriber(
    Player& player
) noexcept:
    player(player) {}

bool PlayerMovementSubscriber::handle(
    Barta::KeyPressedEvent& event
) {
    const Barta::Vector2f playerSpeed = {40.f, 0.f};
    float direction = M_PI / 2.f;
    if (event.key == Barta::BartaKeyMap::W) {
        direction *= 0.f;
    } else if (event.key == Barta::BartaKeyMap::S) {
        direction *= 2.f;
    } else if (event.key == Barta::BartaKeyMap::A) {
        direction *= 3.f;
    } else if (event.key == Barta::BartaKeyMap::D) {
        direction *= 1.f;
    } else {
        return false;
    }

    this->lastKeyPressed = event.key;
    auto newVelocity = Barta::Vector2f::zeroise(playerSpeed.rotated(direction + playerSpeed.angleTo(this->player.getDirection())), 0.5f);
    this->player.getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].velocity = newVelocity;

    return true;
}

bool PlayerMovementSubscriber::handle(
    Barta::KeyReleasedEvent& event
) {
    if (event.key != Barta::BartaKeyMap::W && event.key != Barta::BartaKeyMap::S && event.key != Barta::BartaKeyMap::A
        && event.key != Barta::BartaKeyMap::D) {
        return false;
    }

    if (this->lastKeyPressed == event.key) {
        this->player.getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].velocity = {};
    }

    return true;
}

bool PlayerMovementSubscriber::handle(
    Barta::MouseMoveEvent& event
) {
    auto direction = event.getPosition() - this->player.getPosition();
    if (direction.zeroised().isZero()) {
        return false;
    }

    direction = direction.normalised();

    player.setRotation(std::atan2(direction.y, direction.x) * 180.f / M_PI + 90.f);
    player.getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].velocity =
        player.getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].velocity.rotated(player.getDirection().angleTo(direction));
    player.setDirection(direction);

    return false;
}

bool PlayerMovementSubscriber::isValid() const noexcept {
    return !this->player.isToBeDeleted();
}
