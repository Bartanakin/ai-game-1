//
// Created by bartanakin on 11/16/24.
//

#include "CheckEnemyTriggerSubscriber.h"
#include <format>

CheckEnemyTriggerSubscriber::CheckEnemyTriggerSubscriber(
    std::random_device& randomDevice
) noexcept:
    randomDevice(randomDevice) {}

bool CheckEnemyTriggerSubscriber::handle(
    CheckEnemyTriggerEvent& event
) {
    for (auto enemy_ptr: event.enemies) {
        if (enemy_ptr->isToBeDeleted()) {
            continue;
        }

        unsigned int triggerCount = 1;
        auto myRandomTime = enemy_ptr->getWanderHideChangeTime();
        if (enemy_ptr->getBehaviourType() != Enemy::EnemyBehaviourType::ATTACK) {
            for (auto enemy_ptr_inter: event.enemies) {
                if (enemy_ptr_inter->isToBeDeleted() || enemy_ptr == enemy_ptr_inter) {
                    continue;
                }

                if ((enemy_ptr->getCurrentDynamicsData().massCenter - enemy_ptr_inter->getCurrentDynamicsData().massCenter).normSquare()
                    < std::pow(CheckEnemyTriggerSubscriber::TRIGGER_RADIUS, 2)) {
                    triggerCount++;

                    if (enemy_ptr->getBehaviourType() == enemy_ptr_inter->getBehaviourType()
                        && myRandomTime > enemy_ptr_inter->getWanderHideChangeTime()) {
                        myRandomTime = enemy_ptr_inter->getWanderHideChangeTime();
                    }
                }

                if (triggerCount >= CheckEnemyTriggerSubscriber::TRIGGER_COUNT) {
                    break;
                }
            }
        }

        // set attack behaviour
        if (triggerCount >= CheckEnemyTriggerSubscriber::TRIGGER_COUNT || enemy_ptr->getBehaviourType() == Enemy::EnemyBehaviourType::ATTACK) {
            enemy_ptr->setBehaviourType(Enemy::EnemyBehaviourType::ATTACK);
            for (auto enemy_ptr_inter: event.enemies) {
                if (enemy_ptr_inter->isToBeDeleted()) {
                    continue;
                }

                if ((enemy_ptr->getCurrentDynamicsData().massCenter - enemy_ptr_inter->getCurrentDynamicsData().massCenter).normSquare()
                    < std::pow(CheckEnemyTriggerSubscriber::TRIGGER_RADIUS, 2)) {
                    enemy_ptr_inter->setBehaviourType(Enemy::EnemyBehaviourType::ATTACK);
                }
            }

            continue;
        }

        // change wander/hide behaviour if time passed
        if (enemy_ptr->getWanderHideChangeTime() < std::chrono::steady_clock::now()) {
            if (enemy_ptr->getBehaviourType() == Enemy::EnemyBehaviourType::HIDE) {
                enemy_ptr->setBehaviourType(Enemy::EnemyBehaviourType::WANDER);
            } else if (enemy_ptr->getBehaviourType() == Enemy::EnemyBehaviourType::WANDER) {
                enemy_ptr->setBehaviourType(Enemy::EnemyBehaviourType::HIDE);
            }

            std::default_random_engine generator(this->randomDevice());
            enemy_ptr->setWanderHideChangeTime(
                std::chrono::steady_clock::now() + std::uniform_int_distribution(10000, 40000)(generator) * std::chrono::milliseconds(1)
            );

            continue;
        }

        // change wander/hide behaviour if met others
        for (auto enemy_ptr_inter: event.enemies) {
            if (enemy_ptr_inter->isToBeDeleted()) {
                continue;
            }

            if ((enemy_ptr->getCurrentDynamicsData().massCenter - enemy_ptr_inter->getCurrentDynamicsData().massCenter).normSquare()
                    >= std::pow(CheckEnemyTriggerSubscriber::TRIGGER_RADIUS, 2)
                || enemy_ptr == enemy_ptr_inter) {
                continue;
            }

            if (enemy_ptr->getBehaviourType() == Enemy::EnemyBehaviourType::WANDER
                && enemy_ptr_inter->getBehaviourType() == Enemy::EnemyBehaviourType::HIDE) {
                enemy_ptr_inter->setBehaviourType(Enemy::EnemyBehaviourType::WANDER);
            }

            enemy_ptr_inter->setWanderHideChangeTime(myRandomTime);
        }
    }

    return false;
}

bool CheckEnemyTriggerSubscriber::isValid() const noexcept {
    return true;
}
