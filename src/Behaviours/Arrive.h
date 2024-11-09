//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include "BehaviourInterface.h"

namespace Behaviours {

class Arrive: public virtual BehaviourInterface {
    static constexpr float TARGET_SQUARE_RADIUS = 0.5f;

public:
    Arrive() noexcept = default;
    Arrive(Barta::Vector2f target) noexcept;

    Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaTime) const override;

private:
    Barta::Vector2f target;
};

} // Behaviours
