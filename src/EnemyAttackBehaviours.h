//
// Created by bartanakin on 11/16/24.
//

#pragma once
#include "Agents/Enemy.h"
#include "Agents/Wall.h"
#include "Behaviours/BehaviourInterface.h"
#include "Behaviours/GroupBehaviours.h"
#include "Behaviours/ObstacleAvoidance.h"
#include "Behaviours/Pursuit.h"

namespace Behaviours {

class EnemyAttackBehaviours: public virtual BehaviourInterface {
    static constexpr float WANDER_BOUND = 20.f;

public:
    EnemyAttackBehaviours(ObstacleAvoidance<Wall> obstacleAvoidance, Pursuit pursuit, GroupBehaviours<Enemy> groupBehaviours) noexcept;

    Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaTime) const override;

private:
    ObstacleAvoidance<Wall> obstacleAvoidance;
    Pursuit pursuit;
    GroupBehaviours<Enemy> groupBehaviours;
};
}
