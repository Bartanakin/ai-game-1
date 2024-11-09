//
// Created by bartanakin on 11/2/24.
//

#include "Arrive.h"

Behaviours::Arrive::Arrive(
    Barta::Vector2f target
) noexcept:
    target(target) {}

Barta::Vector2f Behaviours::Arrive::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaTime
) const {
    auto toTarget = this->target - behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].massCenter;
    auto dist = std::sqrt(toTarget.normSquare());
    if (toTarget.normSquare() > Arrive::TARGET_SQUARE_RADIUS) {
        auto speed = dist / behaviourDataAware.getBehavioursData().accelerationDelay;
        speed = std::min(speed, behaviourDataAware.getBehavioursData().maxSpeed);
        auto desiredVelocity = toTarget * speed / dist;

        return (desiredVelocity - behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].velocity)
               * behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].mass
               / behaviourDataAware.getBehavioursData().accelerationDelay;
    }

    return {};
}
