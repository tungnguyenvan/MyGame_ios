cmake_minimum_required(VERSION 3.6)

set(APP_NAME template)

project(${APP_NAME})

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/common/appdelegate/AppDelegate.cpp
     Classes/scenes/gameplay/GamePlayScene.cpp
     )
list(APPEND GAME_HEADER
    Classes/common/appdelegate/AppDelegate.h
    Classes/scenes/gameplay/GamePlayScene.h
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
        Classes/common/Definition.h
        Classes/common/DefinitionUI.h
        Classes/common/appdelegate/AppDelegate.h
        Classes/common/appdelegate/AppDelegate.cpp
        Classes/models/core/CoreModel.h
        Classes/models/core/CoreModel.cpp
        Classes/models/levels/core/corelevel/CoreLevel.h
        Classes/models/levels/core/corelevel/CoreLevel.cpp
        Classes/models/levels/core/corelevelframe/CoreLevelFrame.h
        Classes/models/levels/core/corelevelframe/CoreLevelFrame.cpp
        Classes/models/paths/core/CorePath.h
        Classes/models/paths/core/CorePath.cpp
        Classes/models/paths/circle/CirclePath.h
        Classes/models/paths/circle/CirclePath.cpp
        Classes/models/paths/horizontalline/HorizontalLinePath.h
        Classes/models/paths/horizontalline/HorizontalLinePath.cpp
        Classes/models/paths/square/SquarePath.h
        Classes/models/paths/square/SquarePath.cpp
        Classes/models/paths/triangular/TriangularPath.h
        Classes/models/paths/triangular/TriangularPath.cpp
        Classes/models/paths/verticalline/VerticalLinePath.h
        Classes/models/paths/verticalline/VerticalLinePath.cpp
        Classes/scenes/gameplay/GamePlayScene.h
        Classes/scenes/gameplay/GamePlayScene.cpp
        Classes/scenes/intro/IntroStart.h
        Classes/scenes/intro/IntroStart.cpp
        Classes/scenes/intro/IntroEnd.h
        Classes/scenes/intro/IntroEnd.cpp
        Classes/scenes/ui/menu/MenuScene.h
        Classes/scenes/ui/menu/MenuScene.cpp
        Classes/scenes/ui/splash/SplashScreenScene.h
        Classes/scenes/ui/splash/SplashScreenScene.cpp
        Classes/utils/helper/Helper.h
        Classes/utils/helper/Helper.cpp
        Classes/utils/physics/CustomPhysicsBody.cpp
        Classes/utils/physics/CustomPhysicsBody.h
        Classes/models/levels/level3/Level3.cpp
        Classes/models/levels/level3/Level3.h
        Classes/models/levels/level3/frames/frame1/Level3Frame1.cpp
        Classes/models/levels/level3/frames/frame1/Level3Frame1.h
        Classes/models/levels/level3/frames/frame2/Level3Frame2.h
        Classes/models/levels/level3/frames/frame2/Level3Frame2.cpp
        Classes/models/levels/level3/frames/frame3/Level3Frame3.h
        Classes/models/levels/level3/frames/frame3/Level3Frame3.cpp
        Classes/models/levels/level3/frames/frame4/Level3Frame4.h
        Classes/models/levels/level3/frames/frame4/Level3Frame4.cpp
        Classes/models/objects/obstacles/level3/circle/CircleObstacleModel.cpp
        Classes/models/objects/obstacles/level3/circle/CircleObstacleModel.h
        Classes/models/objects/obstacles/level3/circleline/CircleLineModel.cpp
        Classes/models/objects/obstacles/level3/circleline/CircleLineModel.h
        Classes/common/definitionlevels/DefinitionLevel3.h
        Classes/models/objects/obstacles/level3/coin/CoinModel.cpp
        Classes/models/objects/obstacles/level3/coin/CoinModel.h
        Classes/utils/levels/level3/animation/GetAnimation.cpp
        Classes/utils/levels/level3/animation/GetAnimation.h
        Classes/models/objects/obstacles/level3/rectagle/RectangleObstacleModel.cpp
        Classes/models/objects/obstacles/level3/rectagle/RectangleObstacleModel.h
        Classes/models/objects/obstacles/level3/rectagleline/RectangleLine.h
        Classes/models/objects/obstacles/level3/rectagleline/RectangleLine.cpp
        Classes/models/objects/obstacles/level3/horizontalline/HorizontalLine.h
        Classes/models/objects/obstacles/level3/horizontalline/HorizontalLine.cpp
        Classes/models/objects/obstacles/level3/triangular/TriangularObstacleModel.h
        Classes/models/objects/obstacles/level3/triangular/TriangularObstacleModel.cpp
        Classes/models/objects/obstacles/level3/triangularline/TriangularLine.h
        Classes/models/objects/obstacles/level3/triangularline/TriangularLine.cpp
        Classes/common/definitionlevels/DefinitionLevel5.h
        Classes/common/definitionlevels/DefinitionLevel8.h
        Classes/common/definitionpaths/verticalline/DefinitionVerticalLine.h
        Classes/models/levels/level5/Level5.h
        Classes/models/levels/level5/Level5.cpp
        Classes/models/levels/level8/Level8.h
        Classes/models/levels/level8/Level8.cpp
        Classes/models/objects/obstacles/level5/LineFrame.h
        Classes/models/objects/obstacles/level5/LineFrame.cpp
        Classes/models/objects/obstacles/level8/core/CoreObstacle.h
        Classes/models/objects/obstacles/level8/core/CoreObstacle.cpp
        Classes/models/objects/obstacles/level8/Bar.h
        Classes/models/objects/obstacles/level8/Bar.cpp
        Classes/models/objects/obstacles/level8/Boom.h
        Classes/models/objects/obstacles/level8/Boom.cpp
        Classes/models/objects/obstacles/level8/Rock.h
        Classes/models/objects/obstacles/level8/Rock.cpp
        Classes/models/objects/obstacles/level8/Spike.h
        Classes/models/objects/obstacles/level8/Spike.cpp
        Classes/models/objects/other/level8/ObstaclesCreation.h
        Classes/models/objects/other/level8/ObstaclesCreation.cpp
        Classes/utils/levels/level8/Level8Helper.h
        Classes/utils/levels/level8/Level8Helper.cpp
        Classes/utils/physics/CustomPhysicsBody.h
        Classes/utils/physics/CustomPhysicsBody.cpp
        Classes/utils/physics/MyBodyParser.h
        Classes/utils/physics/MyBodyParser.cpp
        Classes/models/levels/level4/Level4.cpp
        Classes/models/levels/level4/Level4.h
        Classes/models/levels/level4/frames/frame1/Level4Frame1.cpp
        Classes/models/levels/level4/frames/frame1/Level4Frame1.h
        Classes/common/definitionlevels/DefinitionLevel4.h
        Classes/models/levels/level4/frames/frame2/Level4Frame2.cpp
        Classes/models/levels/level4/frames/frame2/Level4Frame2.h
        Classes/models/objects/obstacles/level4/lineobstacle/LineObstacleModel.cpp
        Classes/models/objects/obstacles/level4/lineobstacle/LineObstacleModel.h
        Classes/models/objects/obstacles/level4/circleobstacle/CircleLineObstacle.cpp
        Classes/models/objects/obstacles/level4/circleobstacle/CircleLineObstacle.h
        Classes/models/levels/level9/Level9.h
        Classes/models/levels/level9/Level9.cpp
        Classes/common/definitionlevels/DefinitionLevel9.h
        Classes/models/objects/obstacles/level9/core/CoreDestroyer.h
        Classes/models/objects/obstacles/level9/core/CoreDestroyer.cpp
        Classes/models/objects/obstacles/level9/Archer.h
        Classes/models/objects/obstacles/level9/Archer.cpp
        Classes/models/objects/obstacles/level9/Cannon.h
        Classes/models/objects/obstacles/level9/Cannon.cpp
        Classes/models/objects/obstacles/level9/Shooter.h
        Classes/models/objects/obstacles/level9/Shooter.cpp
        Classes/models/objects/other/level8and9/Creator.h
        Classes/models/objects/other/level9/destroyer_moving_path/DestroyersMovingPath.h
        Classes/models/objects/other/level9/destroyer_moving_path/DestroyersMovingPath.cpp
        Classes/models/objects/other/level9/DestroyersCreation.h
        Classes/models/objects/other/level9/DestroyersCreation.cpp
        Classes/models/objects/other/level9/destroying_weapons/core/DestroyingWeapon.h
        Classes/models/objects/other/level9/destroying_weapons/core/DestroyingWeapon.cpp
        Classes/models/objects/other/level9/destroying_weapons/Arrow.h
        Classes/models/objects/other/level9/destroying_weapons/Arrow.cpp
        Classes/models/objects/other/level9/destroying_weapons/Bullet.cpp
        Classes/models/objects/other/level9/destroying_weapons/Bullet.h
        Classes/models/objects/other/level9/destroying_weapons/Missle.h
        Classes/models/objects/other/level9/destroying_weapons/Missle.cpp
        Classes/utils/levels/level9/Level9Helper.h
        Classes/utils/levels/level9/Level9Helper.cpp
        Classes/common/definitionlevels/DefinitionLevel7.h
        Classes/models/objects/obstacles/level7/Barrier.h
        Classes/models/objects/obstacles/level7/Barrier.cpp
        Classes/models/objects/other/level7/BarriersCreation.h
        Classes/models/objects/other/level7/BarriersCreation.cpp
        Classes/models/levels/level7/Level7.h
        Classes/models/levels/level7/Level7.cpp
        Classes/scenes/ui/panels/gameover/GameOverPanel.h
        Classes/scenes/ui/panels/gameover/GameOverPanel.cpp
        Classes/scenes/ui/panels/level_completion/LevelCompletionPanel.h
        Classes/scenes/ui/panels/level_completion/LevelCompletionPanel.cpp
        Classes/scenes/ui/menu/MenuScene.cpp
        Classes/scenes/ui/menu/MenuScene.cpp
        Classes/scenes/ui/menu/LevelsSelectionScene.h
        Classes/scenes/ui/menu/LevelsSelectionScene.cpp
        )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
        set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "")
        set_xcode_property(${APP_NAME} CODE_SIGN_IDENTITY "iPhone Developer")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    set(APP_RES_DIR "$<TARGET_FILE_DIR:${APP_NAME}>/Resources")
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()