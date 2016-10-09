
#include "framebuffer.h"
#include "DrawText.h"
#include "SpriteManager.h"

const char *story_text[] = {
" The third intergalactic conflict",
"    lays waste to the galaxy.",
" The Hegemonic Empire crushes all",
"       traces of freedom.",
"Rebels assemble at the Kronerd sector",
"   to launch their final assault.",
" Brave pilots, on one-manned ships,",
" push forward through enemy lines.",
"  Their only mission is to reach",
"  Central Control and crush it.",
};

#define TEXT_WIDTH (SCREEN_WIDTH / 2)
#define TEXT_HEIGHT 200
#define TEXT_MOVE_DELAY (TIMER_SEC / 30)
#define TEXT_FINAL_POSITION (-TEXT_HEIGHT - 10)

uint8_t textArt[TEXT_WIDTH*TEXT_HEIGHT];
SpriteT *textSpr;
uint64_t textNextMove;
int finished;

void
SceneStory_init() {
	for ( int i = 0; i < TEXT_WIDTH*TEXT_HEIGHT; i++ ) {
		textArt[i] = 0;
	}
	int len = sizeof(story_text)/sizeof(const char *);
	for ( int i = 0; i < len; i++ ) {
		DrawString(textArt, 0, 10*i, 1, story_text[i]);
	}
	SpriteManager_init();
	textSpr = SpriteManager_newSprite();
	textSpr->art = textArt;
	textSpr->width = TEXT_WIDTH;
	textSpr->height = TEXT_HEIGHT;
	textSpr->anchorX = 0;
	textSpr->anchorY = 0;
	textSpr->x = (SCREEN_WIDTH - TEXT_WIDTH)/2;
	textSpr->y = SCREEN_HEIGHT+10;
	textNextMove = timer_current() + TEXT_MOVE_DELAY;
	finished = 0;
}

void
SceneStory_loop() {
	if ( textSpr->y <= TEXT_FINAL_POSITION ) {
		finished = 1;
		return;
	}
	int dt = timer_current() - textNextMove;
	if ( dt > 0 ) {
		int dy = (dt / TEXT_MOVE_DELAY) + 1;
		textSpr->y -= dy;
		textNextMove += TEXT_MOVE_DELAY * dy;
	}
	uint8_t *fb = framebuffer_getptr();
	framebuffer_clear();
	SpriteManager_draw(fb);
	DrawNumber(fb, 0, 5, 1, timer_fps_current);
	framebuffer_commit();
	timer_count_frame();
}

int
SceneStory_finished() {
	return finished;
}
