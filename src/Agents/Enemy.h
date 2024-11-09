#pragma once
#include "../Behaviours/BehavioursDataAwareInterface.h"
#include <Objects/Rigid/RigidObject.h>

class Enemy: public Barta::RigidObject, public virtual Behaviours::BehavioursDataAwareInterface {
public:
    static constexpr float MAX_SPEED = 25.f;
    Enemy(
        Barta::GraphicsData graphicsData,
        std::unique_ptr<Barta::HitboxInterface> hitbox,
        Barta::DynamicsDTO dynamicsDto,
        Behaviours::BehaviourData behaviourData
    );

    Behaviours::BehaviourData& getBehavioursData() noexcept override;

    GraphicsDataList getGraphicsData() override;

    Barta::OBB getDetectionBox() const noexcept;

private:
    Behaviours::BehaviourData behaviourData;
    Barta::GraphicsData detectionBoxSprite;
};
