//
// Created by bartanakin on 11/16/24.
//

#include "CheckEnemyTriggerSubscriber.h"

bool CheckEnemyTriggerSubscriber::handle(
    CheckEnemyTriggerEvent& event
) {
    for (auto enemy_ptr: event.enemies) {
        if (enemy_ptr->isToBeDeleted()) {
            continue;
        }

        unsigned int triggerCount = 1;
        if (!enemy_ptr->isTriggered()) {
            for (auto enemy_ptr_inter: event.enemies) {
                if (enemy_ptr_inter->isToBeDeleted() || enemy_ptr == enemy_ptr_inter) {
                    continue;
                }

                if ((enemy_ptr->getCurrentDynamicsData().massCenter - enemy_ptr_inter->getCurrentDynamicsData().massCenter).normSquare()
                    < std::pow(CheckEnemyTriggerSubscriber::TRIGGER_RADIUS, 2)) {
                    triggerCount++;
                }

                if (triggerCount >= CheckEnemyTriggerSubscriber::TRIGGER_COUNT) {
                    break;
                }
            }

            if (triggerCount < CheckEnemyTriggerSubscriber::TRIGGER_COUNT) {
                continue;
            }
        }

        std::chrono::time_point<std::chrono::steady_clock> timePoint;
        if (enemy_ptr->isTriggered()) {
            timePoint = enemy_ptr->getTriggerTimePoint();
        } else {
            std::default_random_engine generator(100);
            timePoint = std::chrono::steady_clock::now() + std::uniform_int_distribution(30000, 140000)(generator) * std::chrono::milliseconds(1);
            enemy_ptr->doTrigger(timePoint);
        }

        for (auto enemy_ptr_inter: event.enemies) {
            if (enemy_ptr_inter->isToBeDeleted()) {
                continue;
            }

            if ((enemy_ptr->getCurrentDynamicsData().massCenter - enemy_ptr_inter->getCurrentDynamicsData().massCenter).normSquare()
                < std::pow(CheckEnemyTriggerSubscriber::TRIGGER_RADIUS, 2)) {
                enemy_ptr_inter->doTrigger(timePoint);
            }
        }
    }

    return false;
}

bool CheckEnemyTriggerSubscriber::isValid() const noexcept {
    return true;
}
