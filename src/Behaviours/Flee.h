//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include "BehaviourInterface.h"

namespace Behaviours {

class Flee: public virtual BehaviourInterface {
public:
    Flee() = default;
    Flee(Barta::Vector2f hunterPosition) noexcept;

    Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaTime) const override;

private:
    Barta::Vector2f hunterPosition;
};

} // Behaviours
