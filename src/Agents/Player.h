//
// Created by bartanakin on 10/12/24.
//

#pragma once
#include <Objects/Rigid/RigidObject.h>

class Player: public Barta::RigidObject {
public:
    static constexpr unsigned int INITIAL_HEALTH = 20;
    static constexpr std::chrono::milliseconds RELOAD_TIME = std::chrono::milliseconds(1800);

    Player(
        Barta::GraphicsData graphicsData,
        std::unique_ptr<Barta::HitboxInterface> hitbox,
        Barta::DynamicsDTO dynamicsDto,
        Barta::GraphicsData marker
    );

    GraphicsDataList getGraphicsData() override;

    Barta::Vector2f getPosition() const;

    Barta::Vector2f getDirection() const;

    void setDirection(Barta::Vector2f direction);

    std::vector<Barta::Vector2f>& getWallNormVectors() noexcept { return this->wallNormVectors; }

    bool tryToShoot() noexcept;

    void setMarker(
        Barta::GraphicsData marker
    ) {
        this->marker = std::move(marker);
    }

    std::chrono::time_point<std::chrono::steady_clock> getLastShotTime() noexcept { return this->lastShot; }

    void receiveShot();

    unsigned int getHealth() const noexcept { return this->health; }

private:
    Barta::Vector2f direction = {0.f, -1.f};
    std::vector<Barta::Vector2f> wallNormVectors = {};
    unsigned int health;
    std::chrono::time_point<std::chrono::steady_clock> lastShot;
    Barta::GraphicsData marker;
};
