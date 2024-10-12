//
// Created by bartanakin on 10/12/24.
//
#pragma once

#include "Agents/Player.h"
#include <Collisions/CollisionExecutors/CollisionTestExecutor.h>
#include <Collisions/CollisionExecutors/FilterNoCollisionDecorator.h>
#include <Collisions/CollisionLogger.h>
#include <Events/BartaEventLoggerInterface.h>
#include <Objects/Rigid/RigidObjectInterface.h>
#include <ReduceableList.h>
#include <StaticObjectManager.h>
#include <pch.h>
#include "Subscribers/PlayerWallCollisionSubscriber.h"
#include <Objects/Rigid/RigidObjectCollisionSubscriber.h>

typedef Barta::FilterNoCollisionDecorator<Barta::CollisionTestExecutor> CollisionCoreExecutor;

/**
 * Always insert types in pairs. Each pair tell the logger which object types should be searched for collision.
 * This class runs collision test executors and logs the collisions to an event matcher.
 */
typedef Barta::CollisionLogger<Player, Wall> DefaultCollisionLogger;

/**
 * This class pairs the found collisions with respective subscribers.
 */
typedef Barta::EventMatcher<PlayerWall> CollisionEventsLogger; // <--

typedef Barta::StaticObjectManager<Player, Wall> ListManager; // <--
