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

class EnemyEvadeBehaviours: public virtual BehaviourInterface {
    static constexpr float WANDER_BOUND = 20.f;

public:
    EnemyEvadeBehaviours(ObstacleAvoidance<Wall> obstacleAvoidance, Hide<Wall> hide, GroupBehaviours<Enemy> groupBehaviours, Wander wander) noexcept;

    Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaTime) const override;

private:
    ObstacleAvoidance<Wall> obstacleAvoidance;
    Hide<Wall> hide;
    GroupBehaviours<Enemy> groupBehaviours;
    Wander wander;
};

} // Behaviours
