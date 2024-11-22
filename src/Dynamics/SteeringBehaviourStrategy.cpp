//
// Created by bartanakin on 10/22/24.
//

#include "SteeringBehaviourStrategy.h"
#include <Dynamics/ConstVelocityDynamicsUpdateStrategy.h>

SteeringBehaviourStrategy::SteeringBehaviourStrategy(
    ListManager& listManager,
    Behaviours::BehaviourInterface& enemyEvadeBehaviour,
    Behaviours::BehaviourInterface& enemyAttackBehaviour,
    Behaviours::BehaviourInterface& enemyWanderBehaviour
):
    listManager(listManager),
    enemyEvadeBehaviour(enemyEvadeBehaviour),
    enemyAttackBehaviour(enemyAttackBehaviour),
    enemyWanderBehaviour(enemyWanderBehaviour) {}

void SteeringBehaviourStrategy::prepare(
    const float deltaTime
) {
    // enemies
    auto& enemyList = this->listManager.getList(static_cast<Enemy*>(nullptr));
    Barta::ConstVelocityDynamicsUpdateStrategy{enemyList}.prepare(deltaTime);

    for (auto enemy: enemyList) {
        Behaviours::BehaviourInterface* behaviour;
        switch (enemy->getBehaviourType()) {
        case Enemy::EnemyBehaviourType::ATTACK: behaviour = &this->enemyAttackBehaviour; break;

        case Enemy::EnemyBehaviourType::HIDE: behaviour = &this->enemyEvadeBehaviour; break;

        case Enemy::EnemyBehaviourType::WANDER: behaviour = &this->enemyWanderBehaviour; break;
        }

        enemy->getNextDynamicsData().force = behaviour->changeBehaviour(*static_cast<Behaviours::BehavioursDataAwareInterface*>(enemy), deltaTime);
    }

    // player
    Barta::ConstVelocityDynamicsUpdateStrategy{this->listManager.getList(static_cast<Player*>(nullptr))}.prepare(deltaTime);
}

void SteeringBehaviourStrategy::update(
    bool runForward
) {
    auto& enemyList = this->listManager.getList(static_cast<Enemy*>(nullptr));
    Barta::ConstVelocityDynamicsUpdateStrategy{enemyList}.update(false);
    for (auto enemy: enemyList) {
        if (enemy->getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].velocity.zeroised().normSquare() >= std::pow(Enemy::MAX_SPEED, 2)) {
            enemy->getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].velocity =
                enemy->getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].velocity.zeroised().normalised() * Enemy::MAX_SPEED;
        }

        enemy->getDynamicsDTOs().forward();
    }

    Barta::ConstVelocityDynamicsUpdateStrategy{this->listManager.getList(static_cast<Player*>(nullptr))}.update();
}
