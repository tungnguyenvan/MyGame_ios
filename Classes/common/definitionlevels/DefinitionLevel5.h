#pragma once

#define BACKGROUND_PATH "sprites/gameplay/level5/background.png"
#define HORIZONTAL_LINE_PATH "sprites/gameplay/paths/horizontal_line_path.png"
#define BALLOON_NAME_PATH "sprites/gameplay/balloon/balloon.png"
#define LINE_FRAME_JSON_PATH "sprites/gameplay/level5/line/line_frame_obstacles.json"
#define LINE_FRAME_NAME_FORMAT "line_frame_%d"
#define LINE_FRAME_NAME_PATH_FORMAT "sprites/gameplay/level5/line/line_frame_%d.png"
#define BALLOON_EXPLOSION_PATH "sprites/gameplay/balloon/balloon_explosion.plist"

#define HORIZONTAL_LINE_START_POSITION_Y 150

#define LINE_FRAME_EASY_MODE_MIN_SIZE 1
#define LINE_FRAME_EASY_MODE_MAX_SIZE 4
#define LINE_FRAME_NORMAL_MODE_MIN_SIZE 9
#define LINE_FRAME_NORMAL_MODE_MAX_SIZE 14
#define LINE_FRAME_HARD_MODE_MIN_SIZE 15
#define LINE_FRAMES_SIZE 22

#define LINE_FRAME_MOVING_SPEED 3.0

#define LINE_FRAME_INCREASE_MOVING_SPEED 0.3
#define LINE_FRAME_CHANGE_SPEED_TIME 10

#define BALLOON_MOVING_SPEED 2.0
#define BALLOON_MOVING_SPEED_NORMAL 2.25
#define BALLOON_MOVING_SPEED_HARD 2.75

#define EASY_MODE 25
#define NORMAL_MODE 65
#define HARD_MODE 90
#define COMPLETED_LEVEL 93

#define FADE_OUT_STEP_OPACITY 1.5

#define LINE_FRAME_LERP_COLOR_TIME_MIN 5
#define LINE_FRAME_LERP_COLOR_TIME_MAX 10