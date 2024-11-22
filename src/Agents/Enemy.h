#pragma once
#include "../Behaviours/BehavioursDataAwareInterface.h"
#include <Objects/Rigid/RigidObject.h>

class Enemy: public Barta::RigidObject, public virtual Behaviours::BehavioursDataAwareInterface {
public:
    static constexpr float MAX_SPEED = 25.f;
    static constexpr int INITIAL_HEALTH = 4;
    static constexpr auto RELOAD_TIME = std::chrono::milliseconds{2000};

    enum class EnemyBehaviourType {
        WANDER = 0,
        HIDE = 1,
        ATTACK = 2
    };

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

    void doTrigger();

    std::chrono::time_point<std::chrono::steady_clock> getWanderHideChangeTime() const { return this->wanderHideChangeTime; }

    void setWanderHideChangeTime(
        const std::chrono::time_point<std::chrono::steady_clock>& wanderHideChangeTime
    ) {
        this->wanderHideChangeTime = wanderHideChangeTime;
    }

    EnemyBehaviourType getBehaviourType() const { return this->behaviourType; }

    void setBehaviourType(
        EnemyBehaviourType behaviourType
    ) {
        this->behaviourType = behaviourType;
    }

private:
    Behaviours::BehaviourData behaviourData;
    Barta::GraphicsData detectionBoxSprite;
    unsigned int health;
    Barta::Circle circle;
    std::chrono::time_point<std::chrono::steady_clock> lastTimeShot;
    EnemyBehaviourType behaviourType;
    std::chrono::time_point<std::chrono::steady_clock> wanderHideChangeTime;
};
