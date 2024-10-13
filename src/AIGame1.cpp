#include "AIGame1.h"
#include "Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h"
#include "Dynamics/ConstVelocityDynamicsUpdateStrategy.h"
#include "Geometrics/Math/BartaMathLibrary.h"
#include "Graphics/SFML_GraphicsBridge.h"
#include <Collisions/CollisionLogger.h>
#include <Dynamics/Timers/FrameLimitTimerProxy.h>
#include <Dynamics/Timers/SFML_Timer.h>
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <Hitbox/CircleHitbox.h>
#include <Objects/Rigid/RigidCompositeObject.h>
#include <Objects/Rigid/RigidObject.h>
#include <Objects/Rigid/RigidObjectRepository.h>
#include <Objects/SimpleObject.h>
#include "Repositories/AgentRepository.h"
#include "Subscribers/PlayerMovementSubscriber.h"

std::unique_ptr<Barta::TimerInterface> AIGame1::gameTimer =
    std::make_unique<Barta::FrameLimitTimerProxy>(std::make_unique<Barta::SFML_Timer>(), 0.0f);

AIGame1::AIGame1():
    Application(
        "AIGame1",
        std::make_unique<Barta::SFML_GraphicsBridge>(),
        *AIGame1::gameTimer,
        std::make_unique<Barta::ConstVelocityDynamicsUpdateStrategy>(),
        std::make_unique<Barta::DynamicCollisionDetectionStrategy>(std::make_unique<Barta::BartaMathLibrary>(), *AIGame1::gameTimer)
    ) {
    auto repository = AgentRepository(this->objectLists, *this->objectManager);

    auto boundColor = Barta::Color(50, 191, 66, 255);
    auto leftBound = repository.addNewBoundingWall({50.f, 650.f}, boundColor);
    leftBound->move({0.f, 0.f});
    auto topBound = repository.addNewBoundingWall({650.f, 50.f}, boundColor);
    topBound->move({50.f, 0.f});
    auto rightBound = repository.addNewBoundingWall({50.f, 650.f}, boundColor);
    rightBound->move({650.f, 50.f});
    auto bottomBound = repository.addNewBoundingWall({650.f, 50.f}, boundColor);
    bottomBound->move({0.f, 650.f});

    auto player = repository.addNewPlayer();
    player->move({150.f, 150.f});

    auto playerMovementSubscriber = std::make_shared<PlayerMovementSubscriber>(*player);
    this->eventLogger->logSubscriber(static_cast<std::shared_ptr<Barta::KeyPressedSubscriberInterface>>(playerMovementSubscriber));
    this->eventLogger->logSubscriber(static_cast<std::shared_ptr<Barta::KeyReleasedSubscriberInterface>>(playerMovementSubscriber));
}

AIGame1::~AIGame1() = default;

void AIGame1::run() {
    Application::run();
}
