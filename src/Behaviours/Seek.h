//
// Created by bartanakin on 11/9/24.
//

#pragma once
#include "BehaviourInterface.h"

namespace Behaviours {

class Seek: public virtual BehaviourInterface {
public:
    explicit Seek(const Barta::Vector2f& targetPosition) noexcept;

    Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaTime) const override;

private:
    const Barta::Vector2f& targetPosition;
};

} // Behaviours
