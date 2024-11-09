//
// Created by bartanakin on 10/22/24.
//

#include "SteeringBehaviourStrategy.h"
#include <Dynamics/ConstVelocityDynamicsUpdateStrategy.h>

SteeringBehaviourStrategy::SteeringBehaviourStrategy(
    ListManager& listManager,
    Behaviours::BehaviourInterface& enemyBehaviour
):
    listManager(listManager),
    enemyBehaviour(enemyBehaviour) {}

void SteeringBehaviourStrategy::prepare(
    const float deltaTime
) {
    // enemies
    auto& enemyList = this->listManager.getList(static_cast<Enemy*>(nullptr));
    Barta::ConstVelocityDynamicsUpdateStrategy{enemyList}.prepare(deltaTime);

    for (auto enemy: enemyList) {
        enemy->getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].force =
            this->enemyBehaviour.changeBehaviour(*static_cast<Behaviours::BehavioursDataAwareInterface*>(enemy), deltaTime);
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
        if (enemy->getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].velocity.zeroised() != Barta::Vector2f{}) {
            enemy->getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].velocity =
                enemy->getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT].velocity.normalised().zeroised() * Enemy::MAX_SPEED;
        }

        enemy->getDynamicsDTOs().forward();
    }

    Barta::ConstVelocityDynamicsUpdateStrategy{this->listManager.getList(static_cast<Player*>(nullptr))}.update();
}
