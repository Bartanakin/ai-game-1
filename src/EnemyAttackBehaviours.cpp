//
// Created by bartanakin on 11/16/24.
//

#include "EnemyAttackBehaviours.h"

Behaviours::EnemyAttackBehaviours::EnemyAttackBehaviours(
    ObstacleAvoidance<Wall> obstacleAvoidance,
    Pursuit pursuit,
    GroupBehaviours<Enemy> groupBehaviours
) noexcept:
    obstacleAvoidance(std::move(obstacleAvoidance)),
    pursuit(std::move(pursuit)),
    groupBehaviours(std::move(groupBehaviours)) {}

Barta::Vector2f Behaviours::EnemyAttackBehaviours::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaTime
) const {
    auto avoidanceForce = this->obstacleAvoidance.changeBehaviour(behaviourDataAware, deltaTime);

    auto pursuitForce = this->pursuit.changeBehaviour(behaviourDataAware, deltaTime);
    auto groupBehaviours = this->groupBehaviours.changeBehaviour(behaviourDataAware, deltaTime);

    return pursuitForce + avoidanceForce + groupBehaviours;
}
