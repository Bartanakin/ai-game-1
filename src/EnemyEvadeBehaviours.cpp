//
// Created by bartanakin on 11/2/24.
//

#include "Behaviours/Wander.h"
#include "EnemyEvadeBehaviours.h"

Behaviours::EnemyEvadeBehaviours::EnemyEvadeBehaviours(
    ObstacleAvoidance<Wall> obstacleAvoidance,
    Hide<Wall> hide,
    GroupBehaviours<Enemy> groupBehaviours
) noexcept:
    obstacleAvoidance(std::move(obstacleAvoidance)),
    hide(std::move(hide)),
    groupBehaviours(std::move(groupBehaviours)) {}

Barta::Vector2f Behaviours::EnemyEvadeBehaviours::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaTime
) const {
    auto avoidanceForce = this->obstacleAvoidance.changeBehaviour(behaviourDataAware, deltaTime);
    auto hideForce = this->hide.changeBehaviour(behaviourDataAware, deltaTime);
    auto groupBehaviours = this->groupBehaviours.changeBehaviour(behaviourDataAware, deltaTime);

    return hideForce + avoidanceForce + groupBehaviours;
}
