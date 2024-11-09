//
// Created by bartanakin on 10/25/24.
//

#pragma once
#include "BehavioursDataAwareInterface.h"

namespace Behaviours {
/**
 * Behaviour objects should be stateless. All data can be stored in BehaviourData objects.
 */
class BehaviourInterface {
public:
    virtual ~BehaviourInterface() = default;

    virtual Barta::Vector2f changeBehaviour(BehavioursDataAwareInterface& behaviourDataAware, float deltaTime) const = 0;
};
}
