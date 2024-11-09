//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include "Behaviours/Flee.h"
#include "Behaviours/ObstacleAvoidance.h"

namespace Behaviours {

class EnemyBehaviours: public virtual BehaviourInterface {
public:
    EnemyBehaviours(ObstacleAvoidance& obstacleAvoidance, Flee& flee) noexcept;

    Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaTime) const override;

private:
    ObstacleAvoidance& obstacleAvoidance;
    Flee& flee;
};

} // Behaviours
