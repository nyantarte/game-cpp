//
//  game_engine.hpp
//  game
//
//  Created by shimuya on 2020/10/17.
//

#ifndef game_engine_hpp
#define game_engine_hpp
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <random>

#include "singleton.hpp"
#include "lisp/lexer.hpp"
#include "scripting/vm.hpp"
#include "assets/character.hpp"
#include "assets/item.hpp"
#include "ui/widget.hpp"
#include "ui/list_view.hpp"
#include "ui/ui_pos.hpp"
#include "geometory/point.hpp"
#include "states/istate.hpp"
namespace System{
    class CGameEngine{
    public:
        typedef  std::vector<Assets::CharaPtrType> CharaTblType;
    private:
        CharaTblType m_charaTbl;
        CharaTblType m_userCharaTbl;
        typedef std::vector<Assets::ItemPtrType> ItemTblType;
        ItemTblType m_itemTbl;
        ItemTblType m_userItemTbl;
        unsigned m_timePerFrame;
        int m_fontSize;
        std::mt19937 m_randEngine;
    public:
        typedef std::vector<UI::WidgetPtrType> WidgetTblType;
    private:
        WidgetTblType m_widgetTbl;
        Geometory::CPoint m_nextWidgetPos;
        Geometory::CRect m_drawRect;
        UI::UI_POS m_uiPosMode;
        std::stack<States::StatePtrType> m_stateStack;
        
        bool m_mouseDown[INPUT_ARRAY_NUM];
        Geometory::CPoint m_mousePos[INPUT_ARRAY_NUM];
        int m_nextInputIdx;
        int m_checkInputIdx;
    public:
        static CSingleton<CGameEngine> s_self;
    public:
        void runScriptsInFolder(std::string folderPath);
        void runScriptFromStream(std::istream& is);
        void runScriptFromFilePath(std::string filePath);
        void loadAssets();
        std::string openRootbox();
        void setFPS(int fpsNum){
            m_timePerFrame=1000/fpsNum;
        }
        unsigned getTimePerFrame(){
            return m_timePerFrame;
        }
        void setFontSize(int s){
            m_fontSize=s;
        }
        int getFontSize(){
            return m_fontSize;
        }
        WidgetTblType& getWidgetTbl(){
            return m_widgetTbl;
        }
        void beginUI(UI::UI_POS pos);
        void addUI(UI::WidgetPtrType p,bool doBreak);
        void endUI();
        
        void pushState(States::StatePtrType p){
            m_stateStack.push(p);
        }
        void popState(){
            m_stateStack.pop();
        }
        States::StatePtrType getCurrentState(){
            return m_stateStack.top();
        }
        void setDrawRectSize(int l,int t,int w,int h){
            m_drawRect=Geometory::CRect(l,t,w,h);
        }
        void setMouseInputState(int x,int y,bool mouseClick);
        void changeNextInputData();
        void procInputEvents();
        CharaTblType& getUserCharaTbl(){
            return m_userCharaTbl;
        }
        
        static void returnPrevState(void*);
    private:
        int calcUIX(UI::UI_POS pos);
        int calcUIY(UI::UI_POS pos);
        static int charaLispFunc(Scripting::CVM& vm,int argNum,void* pUD);
        static int itemLispFunc(Scripting::CVM& vm,int argNum,void* pUD);
        
    };
};
#endif /* game_engine_hpp */
