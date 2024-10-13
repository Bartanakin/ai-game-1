//
// Created by bartanakin on 10/12/24.
//
#pragma once
#include "../Agents/Player.h"
#include <Events/Events/KeyPressedEvent.h>
#include <Events/Events/KeyReleasedEvent.h>

class PlayerMovementSubscriber: public Barta::KeyPressedSubscriberInterface, public Barta::KeyReleasedSubscriberInterface {
public:
    explicit PlayerMovementSubscriber(Player& player) noexcept;

    bool handle(Barta::KeyPressedEvent& event) override;

    bool handle(Barta::KeyReleasedEvent& event) override;

    bool isValid() const noexcept override;

private:
    Player& player;
    Barta::BartaKeyMap lastKeyPressed = Barta::BartaKeyMap::UNDEFINED;
};
