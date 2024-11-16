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
    if (event.key != Barta::BartaKeyMap::W) {
        return false;
    }

    constexpr Barta::Vector2f PLAYER_VELOCITY = {32.f, 0.f};
    auto newVelocity = Barta::Vector2f::zeroise(PLAYER_VELOCITY.rotated(PLAYER_VELOCITY.angleTo(this->player.getDirection())), 0.5f);
    this->player.getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].velocity = newVelocity;

    return true;
}

bool PlayerMovementSubscriber::handle(
    Barta::KeyReleasedEvent& event
) {
    if (event.key != Barta::BartaKeyMap::W) {
        return false;
    }

    this->player.getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].velocity = {};

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
