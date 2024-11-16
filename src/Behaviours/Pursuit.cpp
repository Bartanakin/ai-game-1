//
// Created by bartanakin on 11/9/24.
//

#include "Pursuit.h"
#include "Seek.h"

Behaviours::Pursuit::Pursuit(
    const Barta::Vector2f& targetPosition,
    const Barta::Vector2f& targetVelocity
) noexcept:
    targetPosition(targetPosition),
    targetVelocity(targetVelocity) {}

Barta::Vector2f Behaviours::Pursuit::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaTime
) const {
    const auto& dynamics = behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT];
    auto toTarget = this->targetPosition - dynamics.massCenter;
    if (toTarget.zeroised() == Barta::Vector2f{}) {
        return {};
    }

    if (toTarget * dynamics.velocity > 0.f && this->targetVelocity * dynamics.velocity < -.95f) {
        return Seek(this->targetPosition).changeBehaviour(behaviourDataAware, deltaTime);
    }

    auto lookAheadTime =
        std::sqrt(toTarget.normSquare()) / (behaviourDataAware.getBehavioursData().maxSpeed + std::sqrt(this->targetVelocity.normSquare()));

    return Seek(this->targetPosition + this->targetVelocity * lookAheadTime).changeBehaviour(behaviourDataAware, deltaTime);
}
