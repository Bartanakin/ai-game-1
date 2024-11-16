#include "AIGame1.h"
#include "Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h"
#include "Dynamics/ConstVelocityDynamicsUpdateStrategy.h"
#include "Dynamics/SteeringBehaviourStrategy.h"
#include "Events/Subscribers/CollisionBrakeSubscriber.h"
#include "Graphics/SFML_GraphicsBridge.h"
#include "Repositories/AgentRepository.h"
#include "Subscribers/CheckEnemyTriggerSubscriber.h"
#include "Subscribers/EnemyAttackSubscriber.h"
#include "Subscribers/PlayerCollisionSubscriber.h"
#include "Subscribers/PlayerMovementSubscriber.h"
#include "Subscribers/PlayerShotSubscriber.h"
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
        std::make_unique<Barta::StaticCollisionDetectionStrategy>()
    ),
    randomDevice(std::random_device{}),
    player(nullptr),
    enemyEvadeBehaviours_ptr(nullptr),
    enemyAttackBehaviours_ptr(nullptr) {
    auto repository = AgentRepository(this->objectLists, *this->objectManager);

    // walls
    auto boundColor = Barta::Color(28, 25, 181, 255);
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
    repository.addNewWall(30.f, {280.f, 400.f});
    repository.addNewWall(50.f, {490.f, 470.f});

    // enemies
    std::random_device randomDevice;
    repository.addNewEnemy({200.f, 280.f}, randomDevice);
    repository.addNewEnemy({300.f, 300.f}, randomDevice);
    repository.addNewEnemy({420.f, 60.f}, randomDevice);
    repository.addNewEnemy({530.f, 280.f}, randomDevice);
    repository.addNewEnemy({80.f, 280.f}, randomDevice);
    repository.addNewEnemy({250.f, 320.f}, randomDevice);
    repository.addNewEnemy({280.f, 580.f}, randomDevice);
    repository.addNewEnemy({310.f, 600.f}, randomDevice);
    repository.addNewEnemy({540.f, 610.f}, randomDevice);
    repository.addNewEnemy({600.f, 600.f}, randomDevice);
    repository.addNewEnemy({70.f, 530.f}, randomDevice);
    repository.addNewEnemy({280.f, 80.f}, randomDevice);
    repository.addNewEnemy({600.f, 80.f}, randomDevice);
    repository.addNewEnemy({420.f, 240.f}, randomDevice);
    repository.addNewEnemy({560.f, 420.f}, randomDevice);

    this->customEventMatcher.logSubscriber(std::make_shared<CheckEnemyTriggerSubscriber>());

    auto enemyAttackSubscriber = std::make_shared<EnemyAttackSubscriber>();
    this->collisionEventsLogger.logSubscriber(enemyAttackSubscriber);

    // player
    auto player = repository.addNewPlayer();
    player->move({200.f, 200.f});

    auto playerMovementSubscriber = std::make_shared<PlayerMovementSubscriber>(*player);
    this->player = player;

    this->eventLogger->logSubscriber(static_cast<std::shared_ptr<Barta::KeyPressedSubscriberInterface>>(playerMovementSubscriber));
    this->eventLogger->logSubscriber(static_cast<std::shared_ptr<Barta::KeyReleasedSubscriberInterface>>(playerMovementSubscriber));
    this->eventLogger->logSubscriber(static_cast<std::shared_ptr<Barta::MouseMoveSubscriberInterface>>(playerMovementSubscriber));
    auto playerShotSubscriber = std::make_shared<PlayerShotSubscriber>(
        *player,
        this->objectLists.getList(static_cast<Enemy*>(nullptr)),
        this->objectLists.getList(static_cast<Wall*>(nullptr))
    );
    this->customEventMatcher.logSubscriber(playerShotSubscriber);
    this->eventLogger->logSubscriber(playerShotSubscriber);

    auto playerCollisionBrakeSubscriber = std::make_shared<Barta::CollisionBrakeSubscriber<Player, Wall>>();
    this->collisionEventsLogger.logSubscriber(playerCollisionBrakeSubscriber);
    auto enemyWallCollisionBrakeSubscriber = std::make_shared<Barta::CollisionBrakeSubscriber<Enemy, Wall>>();
    this->collisionEventsLogger.logSubscriber(enemyWallCollisionBrakeSubscriber);
    auto playerEnemyCollisionBrakeSubscriber = std::make_shared<Barta::CollisionBrakeSubscriber<Player, Enemy>>();
    this->collisionEventsLogger.logSubscriber(playerEnemyCollisionBrakeSubscriber);
    auto enemyEnemyCollisionBrakeSubscriber = std::make_shared<Barta::CollisionBrakeSubscriber<Enemy, Enemy>>();
    this->collisionEventsLogger.logSubscriber(enemyEnemyCollisionBrakeSubscriber);

    this->enemyEvadeBehaviours_ptr = new Behaviours::EnemyEvadeBehaviours(
        Behaviours::ObstacleAvoidance(this->objectLists.getList(static_cast<Wall*>(nullptr))),
        Behaviours::Hide(
            this->player->getCurrentDynamicsData().massCenter,
            this->player->getCurrentDynamicsData().velocity,
            this->objectLists.getList(static_cast<Wall*>(nullptr))
        ),
        Behaviours::GroupBehaviours(this->objectLists.getList(static_cast<Enemy*>(nullptr))),
        Behaviours::Wander(this->randomDevice)
    );

    this->enemyAttackBehaviours_ptr = new Behaviours::EnemyAttackBehaviours(
        Behaviours::ObstacleAvoidance(this->objectLists.getList(static_cast<Wall*>(nullptr))),
        Behaviours::Pursuit(this->player->getCurrentDynamicsData().massCenter, this->player->getCurrentDynamicsData().velocity),
        Behaviours::GroupBehaviours(this->objectLists.getList(static_cast<Enemy*>(nullptr)))
    );

    this->dynamicsUpdateStrategy =
        std::make_unique<SteeringBehaviourStrategy>(this->objectLists, *this->enemyEvadeBehaviours_ptr, *this->enemyAttackBehaviours_ptr);
}

AIGame1::~AIGame1() {
    delete this->enemyEvadeBehaviours_ptr;
}

void AIGame1::run() {
    Application::run();
}

void AIGame1::preGarbageCollect() {
    if (this->player != nullptr && this->player->isToBeDeleted()) {
        delete this->enemyEvadeBehaviours_ptr;
        this->enemyEvadeBehaviours_ptr = nullptr;
        this->dynamicsUpdateStrategy = std::make_unique<Barta::DefaultDynamicsUpdateStrategy>(this->objectManager->getDynamicsList());
    }

    this->objectLists.StaticObjectManager<Enemy>::reduceDeleted();
    this->objectLists.StaticObjectManager<Player>::reduceDeleted();

    Application::preGarbageCollect();
}

void AIGame1::postDynamicUpdate() {
    this->customEventMatcher.logEvent(PlayerMarkerChangeEvent(this->player));
    this->customEventMatcher.logEvent(CheckEnemyTriggerEvent(this->objectLists.getList(static_cast<Enemy*>(nullptr))));
    this->customEventMatcher.runSubscribersRecurrently();
}

bool AIGame1::isRunning() {
    return this->player != nullptr && this->player->getHealth() > 0 && !this->objectLists.Barta::StaticObjectManager<Enemy>::getList(nullptr).empty();
}
