#pragma once
#include "../Behaviours/BehavioursDataAwareInterface.h"
#include <Objects/Rigid/RigidObject.h>

class Enemy: public Barta::RigidObject, public virtual Behaviours::BehavioursDataAwareInterface {
public:
    static constexpr float MAX_SPEED = 25.f;
    static constexpr int INITIAL_HEALTH = 4;
    static constexpr auto RELOAD_TIME = std::chrono::milliseconds{2000};
    Enemy(
        Barta::GraphicsData graphicsData,
        std::unique_ptr<Barta::HitboxInterface> hitbox,
        Barta::DynamicsDTO dynamicsDto,
        Behaviours::BehaviourData behaviourData,
        Barta::Circle circle
    );

    Behaviours::BehaviourData& getBehavioursData() noexcept override;

    GraphicsDataList getGraphicsData() override;

    Barta::OBB getDetectionBox() const noexcept;

    void receiveShot() noexcept;

    bool isToBeDeleted() const override;

    bool tryToShoot();

    bool isTriggered() const noexcept;

    std::chrono::time_point<std::chrono::steady_clock> getTriggerTimePoint() const noexcept { return this->triggerTime; }

    void doTrigger(std::chrono::time_point<std::chrono::steady_clock> triggerTime);

private:
    Behaviours::BehaviourData behaviourData;
    Barta::GraphicsData detectionBoxSprite;
    unsigned int health;
    Barta::Circle circle;
    std::chrono::time_point<std::chrono::steady_clock> lastTimeShot;
    bool triggered;
    std::chrono::time_point<std::chrono::steady_clock> triggerTime;
};
