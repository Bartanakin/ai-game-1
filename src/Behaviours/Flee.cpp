//
// Created by bartanakin on 11/2/24.
//

#include "Flee.h"

Behaviours::Flee::Flee(
    Barta::Vector2f hunterPosition
) noexcept:
    hunterPosition(hunterPosition) {}

Barta::Vector2f Behaviours::Flee::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaTime
) const {
    auto desiredVelocity = (behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].massCenter - this->hunterPosition).normalised()
                           * behaviourDataAware.getBehavioursData().maxSpeed;

    return (desiredVelocity - behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].velocity)
           * behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].mass
           / behaviourDataAware.getBehavioursData().accelerationDelay;
}
