//
// Created by bartanakin on 11/2/24.
//

#include "PlayerPositionChangeSubscriber.h"

Subscribers::PlayerPositionChangeSubscriber::PlayerPositionChangeSubscriber(
    Behaviours::Flee& flee
) noexcept:
    flee(flee) {}

bool Subscribers::PlayerPositionChangeSubscriber::handle(
    Events::PlayerPositionChangeEvent& event
) {
    this->flee = {event.player.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].massCenter};

    return false;
}

bool Subscribers::PlayerPositionChangeSubscriber::isValid() const noexcept {
    return true;
}
