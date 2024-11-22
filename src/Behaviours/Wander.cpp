//
// Created by bartanakin on 10/25/24.
//

#include "Wander.h"

Behaviours::Wander::Wander(
    std::random_device& randomDevice
):
    randomDevice(randomDevice) {}

Barta::Vector2f Behaviours::Wander::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaType
) const {
    std::mt19937 engine(this->randomDevice());

    auto wanderTarget = behaviourDataAware.getBehavioursData().wander.target;
    wanderTarget += behaviourDataAware.getBehavioursData().wander.jitter * Barta::Vector2f(this->getRandom(engine), this->getRandom(engine));
    wanderTarget = behaviourDataAware.getBehavioursData().wander.radius * wanderTarget.normalised();

    behaviourDataAware.getBehavioursData().wander.target = wanderTarget;

    auto direction = behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].velocity;
    if (direction.isZero()) {
        direction = {1.f, 0.f};
    std::cout << direction << std::endl;
    }

    return wanderTarget + direction.normalised() * behaviourDataAware.getBehavioursData().wander.distance;
}

float Behaviours::Wander::getRandom(
    std::mt19937& engine
) const noexcept {
    return std::uniform_real_distribution(0.f, 2.f)(engine) - 1.f;
}
