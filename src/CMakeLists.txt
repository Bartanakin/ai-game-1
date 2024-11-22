add_executable(${PROJECT_NAME}
        main.cpp
        AIGame1.cpp
        Agents/Player.cpp
        Agents/Player.h
        Repositories/AgentRepository.cpp
        Repositories/AgentRepository.h
        Predefines.h
        Agents/Wall.cpp
        Agents/Wall.h
        Subscribers/PlayerMovementSubscriber.cpp
        Subscribers/PlayerMovementSubscriber.h
        Subscribers/PlayerCollisionSubscriber.cpp
        Subscribers/PlayerCollisionSubscriber.h
        Agents/Enemy.cpp
        Agents/Enemy.h
        Dynamics/SteeringBehaviourStrategy.cpp
        Dynamics/SteeringBehaviourStrategy.h
        Behaviours/BehavioursData.h
        Behaviours/BehavioursDataAwareInterface.h
        Behaviours/BehaviourInterface.h
        Behaviours/Wander.cpp
        Behaviours/Wander.h
        Behaviours/ObstacleAvoidance.h
        Behaviours/Hide.h
        Behaviours/Arrive.cpp
        Behaviours/Arrive.h
        Behaviours/Evade.cpp
        Behaviours/Evade.h
        Behaviours/Flee.cpp
        Behaviours/Flee.h
        EnemyEvadeBehaviours.cpp
        EnemyEvadeBehaviours.h
        EnemyWanderBehaviours.cpp
        EnemyWanderBehaviours.h
        Subscribers/EnemyCollisionSubscriber.cpp
        Subscribers/EnemyCollisionSubscriber.h
        Behaviours/Seek.cpp
        Behaviours/Seek.h
        Behaviours/Pursuit.cpp
        Behaviours/Pursuit.h
        Behaviours/GroupBehaviours.h
        Behaviours/Separation.h
        Behaviours/Alignment.h
        Behaviours/Cohesion.h
        Events/PlayerEnemyCollisionEvent.h
        Events/EnemyEnemyCollisionEvent.h
        Subscribers/PlayerShotSubscriber.cpp
        Subscribers/PlayerShotSubscriber.h
        Events/PlayerMarkerChangeEvent.h
        Subscribers/EnemyAttackSubscriber.cpp
        Subscribers/EnemyAttackSubscriber.h
        EnemyAttackBehaviours.cpp
        EnemyAttackBehaviours.h
        Events/CheckEnemyTriggerEvent.h
        Subscribers/CheckEnemyTriggerSubscriber.cpp
        Subscribers/CheckEnemyTriggerSubscriber.h
)

if(WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME}
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
endif()

#if(${ENABLE_WARNINGS})
#    target_set_warnings(
#        TARGET
#        ${SANDBOX_NAME}
#        ENABLE
#        ${ENABLE_WARNINGS}
#        AS_ERRORS
#        ${ENABLE_WARNINGS_AS_ERRORS})
#endif()

 if(${ENABLE_LTO})
     target_enable_lto(
         TARGET
         ${SANDBOX_NAME}
         ENABLE
         ON)
 endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${SANDBOX_NAME})
else()
    message(STATUS "Not activating clang-tidy in Sandbox")
endif()