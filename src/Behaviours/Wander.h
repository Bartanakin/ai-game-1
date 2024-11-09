//
// Created by bartanakin on 10/25/24.
//

#pragma once
#include "BehaviourInterface.h"

namespace Behaviours {
class Wander: public BehaviourInterface {
public:
    explicit Wander(std::random_device& randomDevice);

    Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaType) const override;

private:
    float getRandom(std::mt19937& engine) const noexcept;
    std::random_device& randomDevice;
};
}
