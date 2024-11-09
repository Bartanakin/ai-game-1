#pragma once
#include "Behaviours/Arrive.h"
#include "Behaviours/Flee.h"
#include "Behaviours/ObstacleAvoidance.h"
#include "Behaviours/Wander.h"
#include "Constants.h"
#include "EnemyBehaviours.h"
#include "Events/PlayerPositionChangeEvent.h"
#include "Predefines.h"
#include <Application.h>

class AIGame1: public Barta::Application<DefaultCollisionLogger, CollisionEventsLogger, ListManager, CollisionCoreExecutor> {
public:
    AIGame1();
    AIGame1(const AIGame1&) = delete;
    AIGame1(AIGame1&&) = delete;
    AIGame1& operator=(const AIGame1&) = delete;
    ~AIGame1() noexcept;

    void run() override;

    void postDynamicUpdate() override;

private:
    static std::unique_ptr<Barta::TimerInterface> gameTimer;
    std::random_device randomDevice;
    Barta::EventMatcher<Events::PlayerPositionChangeEvent> customEventsLogger;

    Behaviours::Wander enemyWander;
    Behaviours::ObstacleAvoidance enemyObstacleAvoidance;
    Behaviours::Arrive arrive;
    Behaviours::Flee flee;
    Behaviours::EnemyBehaviours enemyBehaviours;
};
