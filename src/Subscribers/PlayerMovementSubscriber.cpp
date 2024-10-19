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
    for (auto it = this->player.getWallNormVectors().begin(); it != this->player.getWallNormVectors().end();) {
        if (*it * newVelocity > 0.f) {
            it = this->player.getWallNormVectors().erase(it);

            continue;
        }

        if (*it * newVelocity < 0.f) {
            return false;
        }

        ++it;
    }

    player.getDynamicsDTO().velocity = playerSpeed.rotated(direction + playerSpeed.angleTo(this->player.getDirection()));

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
        player.getDynamicsDTO().velocity = {0.f, 0.f};
    }

    return true;
}

bool PlayerMovementSubscriber::handle(
    Barta::MouseMoveEvent& event
) {
    auto direction = event.getPosition() - this->player.getPosition();
    direction = direction.normalised();

    this->player.setDirection(direction);

    return false;
}

bool PlayerMovementSubscriber::isValid() const noexcept {
    return !this->player.isToBeDeleted();
}
