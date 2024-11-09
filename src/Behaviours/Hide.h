//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include "BehaviourInterface.h"
#include <Hitbox/HitboxAwareInterface.h>

namespace Behaviours {

class Hide: public virtual BehaviourInterface {
public:
    Hide(const Barta::Vector2f& hunter_position, const std::vector<Barta::HitboxAware*>& obstacles);

    Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaTime) const override;

private:
    const Barta::Vector2f& hunterPosition;
    std::vector<Barta::HitboxAware*> obstacles;
};

} // Behaviours
