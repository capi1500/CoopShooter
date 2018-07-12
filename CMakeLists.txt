cmake_minimum_required(VERSION 3.10)
project(CoopShooter)

set(EXECUTABLE_NAME CoopShooter)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)

include_directories("${PROJECT_SOURCE_DIR}" src)

add_executable(${PROJECT_NAME}
	main.cpp
	src/Enum/enum.hpp
	src/Sound/sound.cpp src/Sound/sound.hpp
	src/SoundManager/soundManager.cpp src/SoundManager/soundManager.hpp
	src/TextureManager/textureManager.cpp src/TextureManager/textureManager.hpp
	src/EventManager/eventManager.cpp src/EventManager/eventManager.hpp
	src/Object/object.cpp src/Object/object.hpp
	src/PhysicObject/physicObject.cpp src/PhysicObject/physicObject.hpp
	src/Loader/loader.cpp src/Loader/loader.hpp
	src/World/world.cpp src/World/world.hpp
	src/Game/game.cpp src/Game/game.hpp
	src/Entity/entity.cpp src/Entity/entity.hpp
	src/Player/player.cpp src/Player/player.hpp
	src/Event/event.cpp src/Event/event.hpp
	src/Bullet/bullet.cpp src/Bullet/bullet.hpp
	src/Weapon/weapon.cpp src/Weapon/weapon.hpp
	src/Item/item.cpp src/Item/item.hpp
	src/Equipment/equipment.cpp src/Equipment/equipment.hpp
	src/ContactListener/contactListener.cpp src/ContactListener/contactListener.hpp src/WorldObject/worldObject.cpp src/WorldObject/worldObject.hpp src/ItemManager/itemManager.cpp src/ItemManager/itemManager.hpp)

set(CMAKE_MODULE_PATH "./cmake_modules" ${CMAKE_MODULE_PATH})
# Detect and add SFML
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# add Box2D

target_link_libraries(${EXECUTABLE_NAME} ${PROJECT_SOURCE_DIR}/lib/libBox2D.a)

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)
