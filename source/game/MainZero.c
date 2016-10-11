
#include <sys/types.h>

#include "framebuffer.h"
#include "mt.h"
#include "timer.h"

#include "SceneStory.h"
#include "SceneGame.h"

#define SCENE_STORY 0
#define SCENE_GAME 1

int currentScene = SCENE_STORY;

void
GameLoop() {
	SceneStory_init();
	for ( ;; ) {
		switch ( currentScene ) {
			case SCENE_STORY:
				SceneStory_loop();
				if ( SceneStory_finished() ) {
					SceneGame_init();
					currentScene = SCENE_GAME;
				}
				break;
			case SCENE_GAME:
				SceneGame_loop();
				if ( SceneGame_finished() ) {
					SceneStory_init();
					currentScene = SCENE_STORY;
				}
				break;
		}
	}
}

void
TestLoop() {
	SceneGame_init();
	for ( ;; ) {
		SceneGame_loop();
		if ( SceneGame_finished() ) {
			SceneGame_init();
		}
	}
}

void
MainZero() {
	framebuffer_init();
	init_genrand_with_hw();
	timer_sleep(TIMER_SEC*3);
	//GameLoop();
	TestLoop();
}
