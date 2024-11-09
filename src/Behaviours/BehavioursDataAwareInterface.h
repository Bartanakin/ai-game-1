//
// Created by bartanakin on 10/25/24.
//

#pragma once
#include "BehavioursData.h"
#include <Dynamics/DynamicsAwareInterface.h>

namespace Behaviours {
class BehavioursDataAwareInterface: public virtual Barta::DynamicsAwareInterface {
public:
    virtual ~BehavioursDataAwareInterface() = default;

    virtual BehaviourData& getBehavioursData() noexcept = 0;
};
}
