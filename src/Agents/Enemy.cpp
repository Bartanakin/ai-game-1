//
// Created by bartanakin on 10/20/24.
//

#include "Enemy.h"
#include "Graphics/GraphicsDataTransformer.h"

Enemy::Enemy(
    Barta::GraphicsData graphicsData,
    std::unique_ptr<Barta::HitboxInterface> hitbox,
    Barta::DynamicsDTO dynamicsDto,
    Behaviours::BehaviourData behaviourData
):
    RigidObject(std::move(graphicsData), std::move(hitbox), dynamicsDto),
    behaviourData(std::move(behaviourData)),
    detectionBoxSprite() {}

Behaviours::BehaviourData& Enemy::getBehavioursData() noexcept {
    return this->behaviourData;
}

Barta::GraphicsDataAwareInterface::GraphicsDataList Enemy::getGraphicsData() {
    this->detectionBoxSprite = Barta::GraphicsDataTransformer({0, 0, 255}).fromOBB(this->getDetectionBox());

    auto list = RigidObject::getGraphicsData();
    // list.push_back(&this->detectionBoxSprite);

    return list;
}

Barta::OBB Enemy::getDetectionBox() const noexcept {
    // clang-format off
    return {
        this->dynamicsDTOCollection[Barta::DynamicsDTOIteration::CURRENT].massCenter - Barta::Vector2f(0.f, .5f * this->behaviourData.detectionBoxWidth).rotated(-this->dynamicsDTOCollection[Barta::DynamicsDTOIteration::CURRENT].velocity.angleTo({1.f, 0.f})),
        {
            this->behaviourData.minDetectionBoxLength * (1.f + std::sqrt(this->dynamicsDTOCollection[Barta::DynamicsDTOIteration::CURRENT].velocity.normSquare()) / Enemy::MAX_SPEED),
            this->behaviourData.detectionBoxWidth
        },
        -this->dynamicsDTOCollection[Barta::DynamicsDTOIteration::CURRENT].velocity.angleTo({1.f, 0.f})
    };
    // clang-format on
}
