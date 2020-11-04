//
//  config.h
//  game
//
//  Created by shimuya on 2020/10/17.
//

#ifndef config_h
#define config_h
#define CMD_BUF_SIZE (0xFFFF)

#define ASSETS_DIR_PATH "/Users/shimuya/Desktop/game/assets"
#define CHARA_ASSETS_DIR_PATH (std::string(ASSETS_DIR_PATH)+"/chara")
#define ITEM_ASSETS_DIR_PATH (std::string(ASSETS_DIR_PATH)+"/item")
#define CHARA_ITEM_NUM (4)
#define MAIN_WND_TITLE "Game"
#define MAIN_WND_W 640
#define MAIN_WND_H 480
#define DEF_FONT_SIZE 16

#define DEF_UI_CLEAR_R (0/255.0f)
#define DEF_UI_CLEAR_G (0/255.0f)
#define DEF_UI_CLEAR_B (0/255.0f)
#define DEF_UI_CLEAR_A (0/255.0f)

#define DEF_CTRL_TEXT_R (0.0f)
#define DEF_CTRL_TEXT_G (0.0f)
#define DEF_CTRL_TEXT_B (0.0f)
#define DEF_CTRL_TEXT_A (1.0f)

#define DEF_LABEL_TEXT_R (1.0f)
#define DEF_LABEL_TEXT_G (1.0f)
#define DEF_LABEL_TEXT_B (1.0f)
#define DEF_LABEL_TEXT_A (1.0f)

#define DEF_FPS 15
#define DEF_FRAME_INTERVAL_TIME (1000/DEF_FPS)

#define INPUT_ARRAY_NUM 2
#endif /* config_h */
