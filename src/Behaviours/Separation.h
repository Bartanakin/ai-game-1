//
// Created by bartanakin on 11/10/24.
//

#pragma once
#include "BehaviourInterface.h"
#include <Dynamics/DynamicsAwareListConcept.h>
#include <StaticObjectManager.h>

namespace Behaviours {

template<DynamicsAwareConcept T>
class Separation: public virtual BehaviourInterface {
    using ListType = Barta::ListType<T>;

public:
    explicit Separation(
        ListType& taggedObjects
    ) noexcept:
        taggedObjects(taggedObjects) {}

    Barta::Vector2f changeBehaviour(
        BehavioursDataAwareInterface& behaviourDataAware,
        float deltaTime
    ) const override {
        Barta::Vector2f steeringForce{};
        for (auto taggedObject_ptr: this->taggedObjects) {
            auto toAgent = behaviourDataAware.getCurrentDynamicsData().massCenter - taggedObject_ptr->getCurrentDynamicsData().massCenter;

            if (toAgent.isZero()) {
                continue;
            }

            auto dist = std::sqrt(toAgent.normSquare());
            auto direction = toAgent / dist;
            auto eps = 0.0008f;
            const auto& l_min = behaviourDataAware.getBehavioursData().groupBehaviours.minimalSeparationDistance;
            const auto& l_max = behaviourDataAware.getBehavioursData().groupBehaviours.neighborhoodRadius;
            if (dist > l_min) {
                eps += dist - l_min;
            }

            steeringForce += direction * (std::sqrt(l_min / eps) - 1.f / l_max);
        }

        return behaviourDataAware.getBehavioursData().groupBehaviours.separationCoefficient * steeringForce;
    }

private:
    ListType& taggedObjects;
};

} // Behaviours
