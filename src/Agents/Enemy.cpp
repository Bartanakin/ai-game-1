//
// Created by bartanakin on 10/20/24.
//

#include "Enemy.h"
#include "Graphics/GraphicsDataTransformer.h"
#include <Graphics/SpriteBuilder/SpriteMerger.h>

Enemy::Enemy(
    Barta::GraphicsData graphicsData,
    std::unique_ptr<Barta::HitboxInterface> hitbox,
    Barta::DynamicsDTO dynamicsDto,
    Behaviours::BehaviourData behaviourData,
    Barta::Circle circle
):
    RigidObject(std::move(graphicsData), std::move(hitbox), dynamicsDto),
    behaviourData(std::move(behaviourData)),
    detectionBoxSprite(),
    health(Enemy::INITIAL_HEALTH),
    circle(circle),
    lastTimeShot(std::chrono::steady_clock::now()),
    triggered(false) {}

Behaviours::BehaviourData& Enemy::getBehavioursData() noexcept {
    return this->behaviourData;
}

Barta::GraphicsDataAwareInterface::GraphicsDataList Enemy::getGraphicsData() {
    // this->detectionBoxSprite = Barta::GraphicsDataTransformer({0, 0, 255}).fromOBB(this->getDetectionBox());

    auto color =
        Barta::Color(255 - 255 / (Enemy::INITIAL_HEALTH - 1) * (this->health - 1), 255 / (Enemy::INITIAL_HEALTH - 1) * (this->health - 1), 0);
    this->graphicsData.resource = Barta::SpriteMerger().addCircleSprite({this->circle, color})->merge(false);
    auto list = RigidObject::getGraphicsData();
    // list.push_back(&this->detectionBoxSprite);

    return list;
}

Barta::OBB Enemy::getDetectionBox() const noexcept {
    // clang-format off
    auto speedCoefficient = std::sqrt(this->dynamicsDTOCollection[Barta::DynamicsDTOIteration::CURRENT].velocity.normSquare()) / Enemy::MAX_SPEED;
    auto boxWidth = this->behaviourData.obstacleAvoidance.additionalDetectionBoxWidth * speedCoefficient + this->behaviourData.obstacleAvoidance.minDetectionBoxWidth;
    auto leftTopTranslation = Barta::Vector2f(0.f, .5f * boxWidth)
        .rotated(-this->dynamicsDTOCollection[Barta::DynamicsDTOIteration::CURRENT].velocity.angleTo({1.f, 0.f}));

    return {
        this->dynamicsDTOCollection[Barta::DynamicsDTOIteration::CURRENT].massCenter - leftTopTranslation,
        {
            this->behaviourData.obstacleAvoidance.minDetectionBoxLength + this->behaviourData.obstacleAvoidance.additionalDetectionBoxLength * speedCoefficient,
            boxWidth
        },
        -this->dynamicsDTOCollection[Barta::DynamicsDTOIteration::CURRENT].velocity.angleTo({1.f, 0.f})
    };
    // clang-format on
}

void Enemy::receiveShot() noexcept {
    this->health--;
}

bool Enemy::isToBeDeleted() const {
    return this->health <= 0;
}

bool Enemy::tryToShoot() {
    if (!this->triggered || std::chrono::steady_clock::now() < this->triggerTime) {
        return false;
    }

    if (Enemy::RELOAD_TIME > std::chrono::steady_clock::now() - this->lastTimeShot) {
        return false;
    }

    this->lastTimeShot = std::chrono::steady_clock::now();

    return true;
}

bool Enemy::isTriggered() const noexcept {
    return this->triggered;
}

void Enemy::doTrigger(
    std::chrono::time_point<std::chrono::steady_clock> triggerTime
) {
    if (this->triggered && triggerTime > this->triggerTime) {
        return;
    }

    this->triggered = true;
    this->triggerTime = triggerTime;
}
