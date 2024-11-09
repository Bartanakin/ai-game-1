//
// Created by bartanakin on 10/26/24.
//

#pragma once
#include "BehaviourInterface.h"
#include <Hitbox/HitboxAwareInterface.h>

namespace Behaviours {

class ObstacleAvoidance: public BehaviourInterface {
public:
    ObstacleAvoidance() = default;
    explicit ObstacleAvoidance(std::vector<Barta::HitboxAware*> hitboxes);

    Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaType) const override;

private:
    std::vector<Barta::HitboxAware*> hitboxes;
};

}
