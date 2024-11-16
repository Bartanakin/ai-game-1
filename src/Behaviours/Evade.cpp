//
// Created by bartanakin on 11/2/24.
//

#include "Evade.h"
#include "Flee.h"

Behaviours::Evade::Evade(
    Barta::Vector2f hunterPosition,
    Barta::Vector2f hunterVelocity
) noexcept:
    hunterPosition(hunterPosition),
    hunterVelocity(hunterVelocity) {}

Barta::Vector2f Behaviours::Evade::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaTime
) const {
    auto toHunter = this->hunterPosition - behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].massCenter;
    auto lookAheadTime =
        std::sqrt(toHunter.normSquare()) / (behaviourDataAware.getBehavioursData().maxSpeed - std::sqrt(this->hunterVelocity.normSquare()));

    return Flee(this->hunterPosition + this->hunterVelocity * lookAheadTime).changeBehaviour(behaviourDataAware, deltaTime);
}
