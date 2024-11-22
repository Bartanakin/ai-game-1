//
// Created by bartanakin on 11/2/24.
//

#include "Behaviours/Wander.h"
#include "EnemyWanderBehaviours.h"

Behaviours::EnemyWanderBehaviours::EnemyWanderBehaviours(
    ObstacleAvoidance<Wall> obstacleAvoidance,
    GroupBehaviours<Enemy> groupBehaviours,
    Wander wander
) noexcept:
    obstacleAvoidance(std::move(obstacleAvoidance)),
    groupBehaviours(std::move(groupBehaviours)),
    wander(std::move(wander)) {}

Barta::Vector2f Behaviours::EnemyWanderBehaviours::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaTime
) const {
    auto avoidanceForce = this->obstacleAvoidance.changeBehaviour(behaviourDataAware, deltaTime);
    auto groupBehaviours = this->groupBehaviours.changeBehaviour(behaviourDataAware, deltaTime);
    auto wanderForce = this->wander.changeBehaviour(behaviourDataAware, deltaTime);

    return wanderForce + avoidanceForce + groupBehaviours;
}
