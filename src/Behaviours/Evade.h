//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include "BehaviourInterface.h"

namespace Behaviours {

class Evade: public virtual BehaviourInterface {
public:
    explicit Evade(Barta::Vector2f hunterPosition, Barta::Vector2f hunterVelocity) noexcept;

    Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaTime) const override;

private:
    Barta::Vector2f hunterPosition;
    Barta::Vector2f hunterVelocity;
};

} // Behabiours
