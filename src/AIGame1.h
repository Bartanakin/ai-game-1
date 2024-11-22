#pragma once
#include "Behaviours/Hide.h"
#include "EnemyAttackBehaviours.h"
#include "EnemyEvadeBehaviours.h"
#include "EnemyWanderBehaviours.h"
#include "Events/CheckEnemyTriggerEvent.h"
#include "Events/PlayerMarkerChangeEvent.h"
#include "Predefines.h"
#include <Application.h>
#include <Predefines.h>

class AIGame1: public Barta::Application<DefaultCollisionLogger, CollisionEventsLogger, ListManager, CollisionCoreExecutor> {
public:
    AIGame1();
    AIGame1(const AIGame1&) = delete;
    AIGame1(AIGame1&&) = delete;
    AIGame1& operator=(const AIGame1&) = delete;
    ~AIGame1() noexcept;

    void run() override;

    void preGarbageCollect() override;

    void postDynamicUpdate() override;

    bool isRunning() override;

private:
    static std::unique_ptr<Barta::TimerInterface> gameTimer;
    std::random_device randomDevice;

    Player* player; // Object manager dependency
    Behaviours::EnemyEvadeBehaviours* enemyEvadeBehaviours_ptr;
    Behaviours::EnemyAttackBehaviours* enemyAttackBehaviours_ptr;
    Behaviours::EnemyWanderBehaviours* enemyWanderBehaviours_ptr;

    Barta::EventMatcher<PlayerMarkerChangeEvent, CheckEnemyTriggerEvent> customEventMatcher;
};
