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
        direction *= 3.f;
    } else if (event.key == Barta::BartaKeyMap::S) {
        direction *= 1.f;
    } else if (event.key == Barta::BartaKeyMap::A) {
        direction *= 2.f;
    } else if (event.key == Barta::BartaKeyMap::D) {
        direction *= 0.f;
    } else {
        return false;
    }

    this->lastKeyPressed = event.key;
    player.getDynamicsDTO().velocity = playerSpeed.rotated(direction);

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

bool PlayerMovementSubscriber::isValid() const noexcept {
    return !this->player.isToBeDeleted();
}
