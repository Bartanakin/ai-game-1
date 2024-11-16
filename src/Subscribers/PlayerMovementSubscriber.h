//
// Created by bartanakin on 10/12/24.
//
#pragma once
#include "../Agents/Player.h"
#include <Events/Events/KeyPressedEvent.h>
#include <Events/Events/KeyReleasedEvent.h>
#include <Events/Events/MouseMoveEvent.h>

class PlayerMovementSubscriber:
    public Barta::KeyPressedSubscriberInterface,
    public Barta::KeyReleasedSubscriberInterface,
    public Barta::MouseMoveSubscriberInterface {
public:
    explicit PlayerMovementSubscriber(Player& player) noexcept;

    bool handle(Barta::KeyPressedEvent& event) override;

    bool handle(Barta::KeyReleasedEvent& event) override;

    bool handle(Barta::MouseMoveEvent& event) override;

    bool isValid() const noexcept override;

private:
    Player& player;

    Barta::Vector2f direction = {0.f, -1.f};
};
