//
// Created by bartanakin on 11/9/24.
//

#include "Seek.h"

Behaviours::Seek::Seek(
    const Barta::Vector2f& targetPosition
) noexcept:
    targetPosition(targetPosition) {}

Barta::Vector2f Behaviours::Seek::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaTime
) const {
    const auto& dynamics = behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT];

    return (this->targetPosition - dynamics.massCenter).normalised() * behaviourDataAware.getBehavioursData().maxSpeed - dynamics.velocity;
}
