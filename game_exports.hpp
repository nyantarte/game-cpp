//
//  game_exports.hpp
//  game
//
//  Created by shimuya on 2020/10/29.
//

#ifndef game_exports_hpp
#define game_exports_hpp
#ifdef __cplusplus
extern"C"{

#endif
void executeTests();
void loadAssets();
void setDrawRectSize(int l,int t,int w,int h);
void setFontSize(int s);
void initStates();
int getUINum();
int getUIType(int i);
int getUILeft(int i);
int getUITop(int i);
int getUIWidth(int i);
int getUIHeight(int i);
const char* getUIText(int i);
const char* getUITextFromListItem(int list,int i);
int getListItemNumShow(int i);
void setMouseInput(int x,int y,bool mouseClick);
void changeNextInputData();
void procInputEvents();

#ifdef __cplusplus
}
#endif
#endif /* game_exports_hpp */
