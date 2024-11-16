//
// Created by bartanakin on 11/2/24.
//

#include "Flee.h"

Behaviours::Flee::Flee(
    const Barta::Vector2f& hunterPosition
) noexcept:
    hunterPosition(hunterPosition) {}

Barta::Vector2f Behaviours::Flee::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaTime
) const {
    auto desiredVelocity = (behaviourDataAware.getCurrentDynamicsData().massCenter - this->hunterPosition).normalised()
                           * behaviourDataAware.getBehavioursData().maxSpeed;

    return (desiredVelocity - behaviourDataAware.getCurrentDynamicsData().velocity) * behaviourDataAware.getCurrentDynamicsData().mass
           / behaviourDataAware.getBehavioursData().accelerationDelay;
}
