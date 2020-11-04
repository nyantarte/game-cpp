//
//  game_exports.cpp
//  game
//
//  Created by shimuya on 2020/10/29.
//

#include "game_exports.hpp"
#include "test.hpp"
#include "game_engine.hpp"
#include "states/menu_state.hpp"
void executeTests(){
    Test::CTestCase::execute_tests();
}
void loadAssets(){
    System::CGameEngine::s_self.get()->loadAssets();

}
void setDrawRectSize(int l,int t,int w,int h){
    System::CGameEngine::s_self.get()->setDrawRectSize(l,t,w,h);
}
void setFontSize(int s){
    System::CGameEngine::s_self.get()->setFontSize(s);
}

void initStates(){
    System::CGameEngine::s_self.get()->pushState(States::StatePtrType(new States::CMenuState()));
}
int getUINum(){
    return System::CGameEngine::s_self.get()->getWidgetTbl().size();
}
int getUIType(int i){
    return (int)System::CGameEngine::s_self.get()->getWidgetTbl()[i]->getType();
}
int getUILeft(int i){
    return System::CGameEngine::s_self.get()->getWidgetTbl()[i]->getRect().getLeft();

}
int getUITop(int i){
    return System::CGameEngine::s_self.get()->getWidgetTbl()[i]->getRect().getTop();

}
int getUIWidth(int i){
    return System::CGameEngine::s_self.get()->getWidgetTbl()[i]->getRect().getWidth();

}
int getUIHeight(int i){
    return System::CGameEngine::s_self.get()->getWidgetTbl()[i]->getRect().getHeight();

}
const char* getUIText(int i){
    return System::CGameEngine::s_self.get()->getWidgetTbl()[i]->getText();

}
const char* getUITextFromListItem(int list,int i){
    UI::WidgetPtrType p= System::CGameEngine::s_self.get()->getWidgetTbl()[list];
    if(UI::UI_TYPE::LIST!= p->getType()){
        return nullptr;
    }
    UI::CListView* plV=(UI::CListView*)p.get();
    UI::CListView::ShowListItemOptionType ot=plV->getShowListItem(i);
    if(ot.first && 0 < strlen(ot.second->get()->getText())){
        return ot.second->get()->getText();
    }
    return nullptr;
}
int getListItemNumShow(int i){
    UI::WidgetPtrType p= System::CGameEngine::s_self.get()->getWidgetTbl()[i];
    if(UI::UI_TYPE::LIST!= p->getType()){
        return 0;
    }
    UI::CListView* plV=(UI::CListView*)p.get();
    return plV->getUIShowItemNum();
    
}


void setMouseInput(int x,int y,bool mouseClick){
    System::CGameEngine::s_self.get()->setMouseInputState(x, y, mouseClick);
}
void changeNextInputData(){
    System::CGameEngine::s_self.get()->changeNextInputData();
}
void procInputEvents(){
    System::CGameEngine::s_self.get()->procInputEvents();

}
