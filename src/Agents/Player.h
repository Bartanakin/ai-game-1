//
// Created by bartanakin on 10/12/24.
//

#pragma once
#include <Objects/Rigid/RigidObject.h>

class Player: public Barta::RigidObject {
public:
    Player(Barta::GraphicsData graphicsData, std::unique_ptr<Barta::HitboxInterface> hitbox, Barta::DynamicsDTO dynamicsDto);

    Barta::Vector2f getPosition() const;

    Barta::Vector2f getDirection() const;

    void setDirection(Barta::Vector2f direction);

    std::vector<Barta::Vector2f>& getWallNormVectors() noexcept { return this->wallNormVectors; }

private:
    Barta::Vector2f direction = {0.f, -1.f};
    std::vector<Barta::Vector2f> wallNormVectors = {};
};
