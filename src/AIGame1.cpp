#include "AIGame1.h"
#include "Behaviours/Arrive.h"
#include "Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h"
#include "Dynamics/ConstVelocityDynamicsUpdateStrategy.h"
#include "Dynamics/SteeringBehaviourStrategy.h"
#include "Events/Subscribers/CollisionBrakeSubscriber.h"
#include "Geometrics/Math/BartaMathLibrary.h"
#include "Graphics/SFML_GraphicsBridge.h"
#include "PlayerPositionChangeSubscriber.h"
#include "Repositories/AgentRepository.h"
#include "Subscribers/PlayerCollisionSubscriber.h"
#include "Subscribers/PlayerMovementSubscriber.h"
#include <Application.h>
#include <Collisions/CollisionLogger.h>
#include <Dynamics/Timers/FrameLimitTimerProxy.h>
#include <Dynamics/Timers/SFML_Timer.h>
#include <Objects/Rigid/RigidCompositeObject.h>
#include <Objects/Rigid/RigidObject.h>
#include <Objects/Rigid/RigidObjectRepository.h>

std::unique_ptr<Barta::TimerInterface> AIGame1::gameTimer =
    std::make_unique<Barta::FrameLimitTimerProxy>(std::make_unique<Barta::SFML_Timer>(), 0.0f);

AIGame1::AIGame1():
    Application(
        "AIGame1",
        std::make_unique<Barta::SFML_GraphicsBridge>(),
        *AIGame1::gameTimer,
        nullptr,
        std::make_unique<Barta::DynamicCollisionDetectionStrategy>(std::make_unique<Barta::BartaMathLibrary>(), *AIGame1::gameTimer)
    ),
    randomDevice(std::random_device{}),
    customEventsLogger({}),
    enemyWander(this->randomDevice),
    enemyBehaviours(this->enemyObstacleAvoidance, this->flee) {
    auto repository = AgentRepository(this->objectLists, *this->objectManager);

    // walls
    auto boundColor = Barta::Color(50, 191, 66, 255);
    auto leftBound = repository.addNewBoundingWall({50.f, 650.f}, boundColor);
    leftBound->move({0.f, 0.f});
    auto topBound = repository.addNewBoundingWall({650.f, 50.f}, boundColor);
    topBound->move({50.f, 0.f});
    auto rightBound = repository.addNewBoundingWall({50.f, 650.f}, boundColor);
    rightBound->move({650.f, 50.f});
    auto bottomBound = repository.addNewBoundingWall({650.f, 50.f}, boundColor);
    bottomBound->move({0.f, 650.f});
    repository.addNewWall(30.f, {100.f, 120.f});
    repository.addNewWall(40.f, {400.f, 120.f});
    repository.addNewWall(30.f, {320.f, 380.f});
    repository.addNewWall(50.f, {490.f, 470.f});
    repository.addNewWall(40.f, {130.f, 510.f});

    // enemies
    repository.addNewEnemy({200.f, 280.f}, M_PI / 2.f);

    // player
    auto player = repository.addNewPlayer();
    player->move({200.f, 200.f});

    auto playerMovementSubscriber = std::make_shared<PlayerMovementSubscriber>(*player);
    this->eventLogger->logSubscriber(static_cast<std::shared_ptr<Barta::KeyPressedSubscriberInterface>>(playerMovementSubscriber));
    this->eventLogger->logSubscriber(static_cast<std::shared_ptr<Barta::KeyReleasedSubscriberInterface>>(playerMovementSubscriber));
    this->eventLogger->logSubscriber(static_cast<std::shared_ptr<Barta::MouseMoveSubscriberInterface>>(playerMovementSubscriber));
    auto playerCollisionBrakeSubscriber = std::make_shared<Barta::CollisionBrakeSubscriber<Player, Wall>>();
    this->collisionEventsLogger.logSubscriber(playerCollisionBrakeSubscriber);
    auto enemyWallCollisionBrakeSubscriber = std::make_shared<Barta::CollisionBrakeSubscriber<Enemy, Wall>>();
    this->collisionEventsLogger.logSubscriber(enemyWallCollisionBrakeSubscriber);

    std::vector<Barta::HitboxAware*> hitboxAwares{};
    for (auto wall: this->objectLists.getList(static_cast<Wall*>(nullptr))) {
        hitboxAwares.push_back(wall);
    }

    this->enemyObstacleAvoidance = Behaviours::ObstacleAvoidance(std::move(hitboxAwares));
    this->arrive = Behaviours::Arrive({300.f, 300.f});
    this->flee = Behaviours::Flee(player->getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].massCenter);

    this->dynamicsUpdateStrategy = std::make_unique<SteeringBehaviourStrategy>(this->objectLists, this->enemyBehaviours);

    this->customEventsLogger.logSubscriber(std::make_shared<Subscribers::PlayerPositionChangeSubscriber>(this->flee));
}

AIGame1::~AIGame1() = default;

void AIGame1::run() {
    Application::run();
}

void AIGame1::postDynamicUpdate() {
    Application::postDynamicUpdate();
    for (const auto& player: this->objectLists.getList(static_cast<Player*>(nullptr))) {
        if (player->getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].velocity.zeroised() != Barta::Vector2f()) {
            this->customEventsLogger.logEvent(Events::PlayerPositionChangeEvent(*player));
        }
    }

    this->customEventsLogger.runSubscribersRecurrently();
}
