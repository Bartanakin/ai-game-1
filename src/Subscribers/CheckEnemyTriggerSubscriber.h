//
// Created by bartanakin on 11/16/24.
//

#pragma once
#include "../Events/CheckEnemyTriggerEvent.h"

class CheckEnemyTriggerSubscriber: public virtual CheckEnemyTriggerSubscriberInterface {
public:
    static constexpr unsigned int TRIGGER_COUNT = 4;
    static constexpr float TRIGGER_RADIUS = 80.f;

    CheckEnemyTriggerSubscriber(std::random_device& randomDevice) noexcept;

    bool handle(CheckEnemyTriggerEvent& event) override;

    bool isValid() const noexcept override;

private:
    std::random_device& randomDevice;
};
