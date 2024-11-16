//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include "Arrive.h"
#include "BehaviourInterface.h"
#include "Evade.h"
#include <Hitbox/HitboxAwareInterface.h>
#include <StaticObjectManager.h>

namespace Behaviours {

template<Barta::HitboxAwareConcept ObstacleType>
class Hide: public virtual BehaviourInterface {
    using ListType = Barta::ListType<ObstacleType>;

public:
    Hide(
        const Barta::Vector2f& hunterPosition,
        const Barta::Vector2f& hunterVelocity,
        ListType& hitboxAwares
    ) noexcept:
        hunterPosition(hunterPosition),
        hunterVelocity(hunterVelocity),
        hitboxAwares(hitboxAwares) {}

    Barta::Vector2f changeBehaviour(
        BehavioursDataAwareInterface& behaviourDataAware,
        float deltaTime
    ) const override {
        auto distToClosest = std::numeric_limits<float>::max();
        auto bestHidingSpot = Barta::Vector2f{};
        auto bestObstacleCenter = Barta::Vector2f{};
        for (auto obstacle_ptr: this->hitboxAwares) {
            auto obb = obstacle_ptr->getHitbox()->getBoundingOBB();
            auto toOb = (obb.getCenter() - this->hunterPosition).normalised();
            auto distAway =
                behaviourDataAware.getBehavioursData().hide.distanceFromBoundary + std::max(obb.getWidthHeight().x, obb.getWidthHeight().y) * 0.5f;
            auto hidingPosition = toOb * distAway + obb.getCenter();
            auto dist = (hidingPosition - behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].massCenter).normSquare();
            if (dist < distToClosest) {
                distToClosest = dist;
                bestHidingSpot = hidingPosition;
                bestObstacleCenter = obb.getCenter();
            }
        }

        auto fromHidingToHunter = (this->hunterPosition - bestObstacleCenter).normalised();
        auto froMObstacleToMe = (behaviourDataAware.getCurrentDynamicsData().massCenter - bestObstacleCenter).normalised();
        auto fromHidingToMe = behaviourDataAware.getCurrentDynamicsData().massCenter - bestHidingSpot;
        auto fromHidingToObstacle = bestObstacleCenter - bestHidingSpot;
        if (fromHidingToHunter * froMObstacleToMe > std::acos(M_PI / 3.f) && fromHidingToMe.normSquare() < 7.f * fromHidingToObstacle.normSquare()) {
            return -Evade(this->hunterPosition, hunterVelocity).changeBehaviour(behaviourDataAware, deltaTime).length()
                   * fromHidingToHunter.perpendicular();
        }

        if (distToClosest == std::numeric_limits<float>::max()) {
            return Evade(this->hunterPosition, hunterVelocity).changeBehaviour(behaviourDataAware, deltaTime);
        }

        return Arrive(bestHidingSpot).changeBehaviour(behaviourDataAware, deltaTime);
    }

private:
    const Barta::Vector2f& hunterPosition;
    const Barta::Vector2f& hunterVelocity;
    ListType& hitboxAwares;
};

} // Behaviours
