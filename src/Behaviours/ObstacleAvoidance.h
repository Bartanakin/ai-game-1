//
// Created by bartanakin on 10/26/24.
//

#pragma once
#include "BehaviourInterface.h"
#include "Hitbox/OBB_Hitbox.h"
#include <Collisions/CollisionDetectionStrategies/StaticCollisionDetectionStrategy.h>
#include <Hitbox/HitboxAwareConcept.h>
#include <StaticObjectManager.h>

namespace Behaviours {

template<Barta::HitboxAwareConcept T>
class ObstacleAvoidance: public BehaviourInterface {
    using ListType = Barta::ListType<T>;

public:
    ObstacleAvoidance() = default;

    explicit ObstacleAvoidance(
        ListType& hitboxAwares
    ):
        hitboxAwares(hitboxAwares) {}

    Barta::Vector2f changeBehaviour(
        BehavioursDataAwareInterface& behaviourDataAware,
        float deltaType
    ) const override {
        const auto& velocity = behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].velocity;
        const auto& massCenter = behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].massCenter;
        const auto& minDetectionBoxLength = behaviourDataAware.getBehavioursData().obstacleAvoidance.minDetectionBoxLength;
        const auto& additionalDetectionBoxLength = behaviourDataAware.getBehavioursData().obstacleAvoidance.additionalDetectionBoxLength;
        const auto& maxSpeed = behaviourDataAware.getBehavioursData().maxSpeed;
        const auto& minDetectionBoxWidth = behaviourDataAware.getBehavioursData().obstacleAvoidance.minDetectionBoxWidth;
        const auto& additionalDetectionBoxWidth = behaviourDataAware.getBehavioursData().obstacleAvoidance.additionalDetectionBoxWidth;
        // clang-format off
        auto speedCoefficient = std::sqrt(velocity.normSquare()) / maxSpeed;
        auto boxWidth = additionalDetectionBoxWidth * speedCoefficient + minDetectionBoxWidth;
        auto detectionBox = Barta::OBB_Hitbox({
            massCenter - Barta::Vector2f(0.f, .5f * boxWidth).rotated(-velocity.angleTo({1.f, 0.f})),
            {minDetectionBoxLength + additionalDetectionBoxLength * speedCoefficient, boxWidth},
            -velocity.angleTo({1.f, 0})
        });
        // clang-format on

        auto collisionDetectionStrategy = Barta::StaticCollisionDetectionStrategy();
        std::vector<Barta::CollisionTestResult> collisionTestResults;
        std::vector<Barta::HitboxAware*> detectedHitboxes;
        for (const auto hitbox: this->hitboxAwares) {
            auto collisionTestResult = detectionBox.intersects(*hitbox->getHitbox(), collisionDetectionStrategy, {{}});
            if (collisionTestResult.collisionDetected) {
                collisionTestResults.push_back(collisionTestResult);
                detectedHitboxes.push_back(hitbox);
            }
        }

        if (collisionTestResults.empty()) {
            return {};
        }

        auto closestPoint = collisionTestResults[0].collisionPoint;
        for (size_t i = 1; i < collisionTestResults.size(); ++i) {
            if (collisionTestResults[i].collisionPoint.squareOfDistance(massCenter) < closestPoint.squareOfDistance(massCenter)) {
                closestPoint = collisionTestResults[i].collisionPoint;
            }
        }

        auto collisionTranslation = detectionBox.getOBB().rebaseVector(closestPoint - massCenter);

        return Barta::Vector2f(
                   0.2f * -collisionTranslation.x,
                   (-collisionTranslation.y / detectionBox.getOBB().getWidthHeight().x + 2.f) * -collisionTranslation.y
        )
            .rotated(detectionBox.getOBB().getRotation());
    }

private:
    ListType& hitboxAwares;
};

}
