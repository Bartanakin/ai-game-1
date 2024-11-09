//
// Created by bartanakin on 10/26/24.
//

#include "Hitbox/OBB_Hitbox.h"
#include "ObstacleAvoidance.h"
#include <Collisions/CollisionDetectionStrategies/StaticCollisionDetectionStrategy.h>
#include <Geometrics/Math/BartaMathLibrary.h>
#include <Geometrics/SFML_Transformable.h>
#include <Hitbox/HitboxAwareInterface.h>

Behaviours::ObstacleAvoidance::ObstacleAvoidance(
    std::vector<Barta::HitboxAware*> hitboxes
):
    hitboxes(std::move(hitboxes)) {}

Barta::Vector2f Behaviours::ObstacleAvoidance::changeBehaviour(
    BehavioursDataAwareInterface& behaviourDataAware,
    float deltaType
) const {
    const auto& velocity = behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].velocity;
    const auto& massCenter = behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].massCenter;
    const auto& minDetectionBoxLength = behaviourDataAware.getBehavioursData().minDetectionBoxLength;
    const auto& maxSpeed = behaviourDataAware.getBehavioursData().maxSpeed;
    const auto& detectionBoxWidth = behaviourDataAware.getBehavioursData().detectionBoxWidth;
    // clang-format off
    auto detectionBox = Barta::OBB_Hitbox({
        massCenter - Barta::Vector2f(0.f, .5f * detectionBoxWidth).rotated(-velocity.angleTo({1.f, 0.f})),
        {minDetectionBoxLength * (1.f + std::sqrt(velocity.normSquare()) / maxSpeed), detectionBoxWidth},
        -velocity.angleTo({1.f, 0})
    });
    // clang-format on

    auto collisionDetectionStrategy = Barta::StaticCollisionDetectionStrategy(std::make_unique<Barta::BartaMathLibrary>());
    std::vector<Barta::CollisionTestResult> collisionTestResults;
    std::vector<Barta::HitboxAware*> detectedHitboxes;
    for (const auto hitbox: this->hitboxes) {
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
