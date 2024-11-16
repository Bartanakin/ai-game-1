//
// Created by bartanakin on 11/9/24.
//

#pragma once
#include "BehaviourInterface.h"

namespace Behaviours {

class Pursuit: public virtual BehaviourInterface {
public:
    Pursuit(const Barta::Vector2f& targetPosition, const Barta::Vector2f& targetVelocity) noexcept;

    Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaTime) const override;

private:
    const Barta::Vector2f& targetPosition;
    const Barta::Vector2f& targetVelocity;
};

} // Behaviours
