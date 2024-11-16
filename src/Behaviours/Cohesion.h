//
// Created by bartanakin on 11/10/24.
//

#pragma once
#include "BehaviourInterface.h"
#include "Seek.h"
#include <Dynamics/DynamicsAwareListConcept.h>
#include <StaticObjectManager.h>

namespace Behaviours {

template<DynamicsAwareConcept T>
class Cohesion: public virtual BehaviourInterface {
    using ListType = Barta::ListType<T>;

public:
    explicit Cohesion(
        ListType& neighbours
    ) noexcept:
        neighbours(neighbours) {}

    Barta::Vector2f changeBehaviour(
        BehavioursDataAwareInterface& behaviourDataAware,
        float deltaTime
    ) const override {
        Barta::Vector2f massCenter{};
        unsigned int neighbourCount = 0;
        for (auto neighbour_ptr: this->neighbours) {
            if ((behaviourDataAware.getCurrentDynamicsData().massCenter - neighbour_ptr->getCurrentDynamicsData().massCenter).isZero()) {
                continue;
            }

            massCenter += neighbour_ptr->getCurrentDynamicsData().massCenter;
            ++neighbourCount;
        }

        if (neighbourCount == 0) {
            return {};
        }

        return behaviourDataAware.getBehavioursData().groupBehaviours.cohesionCoefficient
               * Seek(massCenter / static_cast<float>(neighbourCount)).changeBehaviour(behaviourDataAware, deltaTime);
    }

private:
    ListType& neighbours;
};

} // Behaviours
