//
// Created by bartanakin on 10/22/24.
//

#pragma once
#include "../Behaviours/Wander.h"
#include "../Predefines.h"
#include <Dynamics/DynamicsUpdateStrategyInterface.h>

class SteeringBehaviourStrategy: public Barta::DynamicsUpdateStrategyInterface {
public:
    explicit SteeringBehaviourStrategy(
        ListManager& listManager,
        Behaviours::BehaviourInterface& enemyEvadeBehaviour,
        Behaviours::BehaviourInterface& enemyAttackBehaviour
    );

    void prepare(float) override;

    void update(bool runForward = true) override;

private:
    ListManager& listManager;
    Behaviours::BehaviourInterface& enemyEvadeBehaviour;
    Behaviours::BehaviourInterface& enemyAttackBehaviour;
};
