//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include "Agents/Enemy.h"
#include "Behaviours/GroupBehaviours.h"
#include "Behaviours/Hide.h"
#include "Behaviours/ObstacleAvoidance.h"
#include "Behaviours/Wander.h"
#include "Predefines.h"

namespace Behaviours {

class EnemyWanderBehaviours: public virtual BehaviourInterface {
    static constexpr float WANDER_BOUND = 20.f;

public:
    EnemyWanderBehaviours(ObstacleAvoidance<Wall> obstacleAvoidance, GroupBehaviours<Enemy> groupBehaviours, Wander wander) noexcept;

    Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaTime) const override;

private:
    ObstacleAvoidance<Wall> obstacleAvoidance;
    GroupBehaviours<Enemy> groupBehaviours;
    Wander wander;
};

} // Behaviours
