//
// Created by bartanakin on 11/2/24.
//

#include "EnemyBehaviours.h"

Behaviours::EnemyBehaviours::EnemyBehaviours(
    ObstacleAvoidance& obstacleAvoidance,
    Flee& flee
) noexcept:
    obstacleAvoidance(obstacleAvoidance),
    flee(flee) {}

Barta::Vector2f Behaviours::EnemyBehaviours::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaTime
) const {
    auto fleeForce = this->flee.changeBehaviour(behaviourDataAware, deltaTime);
    auto avoidanceForce = this->obstacleAvoidance.changeBehaviour(behaviourDataAware, deltaTime);

    return fleeForce + avoidanceForce;
}
