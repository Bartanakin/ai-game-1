//
// Created by bartanakin on 11/10/24.
//

#pragma once
#include "BehaviourInterface.h"
#include <Dynamics/DynamicsAwareListConcept.h>
#include <StaticObjectManager.h>

namespace Behaviours {

template<DynamicsAwareConcept T>
class Alignment: public virtual BehaviourInterface {
    using ListType = Barta::ListType<T>;

public:
    explicit Alignment(
        ListType& neighbours
    ) noexcept:
        neighbours(neighbours) {}

    Barta::Vector2f changeBehaviour(
        BehavioursDataAwareInterface& behaviourDataAware,
        float deltaTime
    ) const override {
        Barta::Vector2f averageHeading{};
        unsigned int neighbourCount = 0;
        for (auto neighbour: this->neighbours) {
            averageHeading += neighbour->getCurrentDynamicsData().velocity;
            ++neighbourCount;
        }

        if (neighbourCount <= 1) {
            return {};
        }

        return behaviourDataAware.getBehavioursData().groupBehaviours.alignmentCoefficient
               * (averageHeading / static_cast<float>(neighbourCount) - behaviourDataAware.getCurrentDynamicsData().velocity);
    }

private:
    ListType& neighbours;
};

} // Behaviours
