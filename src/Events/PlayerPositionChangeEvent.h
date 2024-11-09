//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include "../Agents/Player.h"
#include <Events/TemplateEventSubscriber.h>

namespace Events {
class PlayerPositionChangeEvent {
public:
    Player& player;
};
}

SUBSCRIBER_INTERFACE_DEFINITION(Events::PlayerPositionChangeEvent);

namespace Events {
typedef Barta::EventSubscriber<PlayerPositionChangeEvent> PlayerPositionChangeEventSubscriberInterface;
}
