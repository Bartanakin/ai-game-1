#pragma once
#include "Constants.h"
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

private:
    static std::unique_ptr<Barta::TimerInterface> gameTimer;
};
