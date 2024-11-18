cmake_minimum_required(VERSION 3.5)
project (SilvergunProject)
include(FetchContent)

FetchContent_Declare(
  allegro5
  GIT_REPOSITORY https://github.com/liballeg/allegro5.git
  GIT_TAG        5.2.7.0
)
FetchContent_Declare(
	silvergun
	GIT_REPOSITORY https://github.com/AtomicSponge/silvergun.git
	GIT_TAG				 main
)
FetchContent_GetProperties(allegro5)
FetchContent_GetProperties(silvergun)
if(NOT allegro5_POPULATED)
  FetchContent_Populate(allegro5)
	if (MSVC)
		set(SHARED ON)
	else()
		set(SHARED OFF)
	endif()
	set(WANT_TESTS OFF)
	set(WANT_EXAMPLES OFF)
	set(WANT_DEMO OFF)
  add_subdirectory(${allegro5_SOURCE_DIR} ${allegro5_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

if(NOT silvergun_POPULATED)
	FetchContent_Populate(silvergun)
endif()

add_executable(slvdemo src/main.cpp)

target_include_directories(slvdemo PUBLIC ${allegro5_SOURCE_DIR}/include)
target_include_directories(slvdemo PUBLIC ${allegro5_BINARY_DIR}/include)
target_include_directories(slvdemo PUBLIC ${silvergun_SOURCE_DIR}/include)
target_link_libraries(slvdemo LINK_PUBLIC allegro allegro_main allegro_audio allegro_acodec allegro_font allegro_image allegro_primitives)

# These include files are typically copied into the correct places via allegro's install
# target, but we do it manually.

file(COPY ${allegro5_SOURCE_DIR}/addons/acodec/allegro5/allegro_acodec.h
	DESTINATION ${allegro5_SOURCE_DIR}/include/allegro5
)
file(COPY ${allegro5_SOURCE_DIR}/addons/audio/allegro5/allegro_audio.h
	DESTINATION ${allegro5_SOURCE_DIR}/include/allegro5
)
file(COPY ${allegro5_SOURCE_DIR}/addons/font/allegro5/allegro_font.h
	DESTINATION ${allegro5_SOURCE_DIR}/include/allegro5
)
file(COPY ${allegro5_SOURCE_DIR}/addons/image/allegro5/allegro_image.h
	DESTINATION ${allegro5_SOURCE_DIR}/include/allegro5
)
file(COPY ${allegro5_SOURCE_DIR}/addons/primitives/allegro5/allegro_primitives.h
	DESTINATION ${allegro5_SOURCE_DIR}/include/allegro5
)
