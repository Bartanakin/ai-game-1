//
// Created by bartanakin on 10/12/24.
//

#pragma once
#include <Objects/Rigid/RigidObject.h>


class Wall: public Barta::RigidObject {
public:
    Wall(
        Barta::GraphicsData graphicsData,
        std::unique_ptr<Barta::HitboxInterface> hitbox,
        Barta::DynamicsDTO dynamicsDto
    );
};
