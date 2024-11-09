//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include "Behaviours/Flee.h"
#include "Events/PlayerPositionChangeEvent.h"

namespace Subscribers {

class PlayerPositionChangeSubscriber: public virtual Events::PlayerPositionChangeEventSubscriberInterface {
public:
    explicit PlayerPositionChangeSubscriber(Behaviours::Flee& flee) noexcept;

    bool handle(Events::PlayerPositionChangeEvent& event) override;

    bool isValid() const noexcept override;

private:
    Behaviours::Flee& flee;
};

} // Subscribers
