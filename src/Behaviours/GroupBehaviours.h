//
// Created by bartanakin on 11/10/24.
//

#pragma once
#include "Alignment.h"
#include "BehaviourInterface.h"
#include "Cohesion.h"
#include "Separation.h"
#include <Dynamics/DynamicsAwareListConcept.h>
#include <StaticObjectManager.h>

namespace Behaviours {

template<DynamicsAwareConcept T>
class GroupBehaviours: public virtual BehaviourInterface {
    using ListType = Barta::ListType<T>;

public:
    explicit GroupBehaviours(
        ListType& objects
    ) noexcept:
        objects(objects) {}

    Barta::Vector2f changeBehaviour(
        BehavioursDataAwareInterface& behaviourDataAware,
        float deltaTime
    ) const override {
        ListType taggedObjects = {};
        for (auto object_ptr: this->objects) {
            if (object_ptr->isToBeDeleted()) {
                continue;
            }

            auto dist = (object_ptr->getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].massCenter
                         - behaviourDataAware.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].massCenter)
                            .normSquare();
            if (dist < std::pow(behaviourDataAware.getBehavioursData().groupBehaviours.neighborhoodRadius, 2)) {
                taggedObjects.push_back(object_ptr);
            }
        }

        if (taggedObjects.empty()) {
            return {};
        }

        auto separation = Separation<T>(taggedObjects).changeBehaviour(behaviourDataAware, deltaTime);
        auto alignment = Alignment<T>(taggedObjects).changeBehaviour(behaviourDataAware, deltaTime);
        auto cohesion = Cohesion<T>(taggedObjects).changeBehaviour(behaviourDataAware, deltaTime);

        return separation + alignment + cohesion;
    }

private:
    ListType& objects;
};

} // Behaviours
