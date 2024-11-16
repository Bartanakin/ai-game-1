//
// Created by bartanakin on 11/15/24.
//

#pragma once
#include "../Agents/Player.h"
#include <Events/TemplateEventSubscriber.h>

class PlayerMarkerChangeEvent {
public:
    Player* player;

    PlayerMarkerChangeEvent(
        Player* player
    ):
        player(player) {}
};

SUBSCRIBER_INTERFACE_DEFINITION(PlayerMarkerChangeEvent);

typedef Barta::EventSubscriber<PlayerMarkerChangeEvent> PlayerMarkerChangeSubscriberInterface;
