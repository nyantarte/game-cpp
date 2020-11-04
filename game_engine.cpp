//
//  game_engine.cpp
//  game
//
//  Created by shimuya on 2020/10/17.
//
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include "game_engine.hpp"
#include "lisp/lexer.hpp"
#include "lisp/syntax.hpp"
#include "vm.hpp"

namespace System{
    CSingleton<CGameEngine> CGameEngine::s_self;

    void CGameEngine::runScriptFromStream(std::istream& is){
        std::string buf;
        std::string line;
        while(std::getline(is, line)){
            
            buf=buf+"\n"+line;
        }
#ifdef DEBUG
        std::cout<<"Script loading result:"<<buf<<std::endl;
#endif

        //buf="(test)";
        Scripting::CVM vm;
        vm.registFunc("chara",&CGameEngine::charaLispFunc);
        vm.registFunc("item",&CGameEngine::itemLispFunc);
        Lisp::CLexer l;
        l.addTokens(buf);
        Lisp::CSyntax s;
        s.parse(l,vm);
        vm.dump();
        vm.run(this);
    }
    void CGameEngine::runScriptsInFolder(std::string folderPath){
        using namespace std::__fs::filesystem;
        directory_iterator iter(folderPath), end;
        std::error_code err;

        for (; iter != end && !err; iter.increment(err)) {
            const directory_entry entry = *iter;
            if(".lsp"==entry.path().extension()){
                runScriptFromFilePath(entry.path().string());
                
            }
            
        }

        /* エラー処理 */
        if (err) {
            std::cout << err.value() << std::endl;
            std::cout << err.message() << std::endl;
        }
    }

    void CGameEngine::runScriptFromFilePath(std::string filePath){
        std::ifstream fs(filePath);
        runScriptFromStream(fs);
    }
    void CGameEngine::loadAssets(){
        runScriptsInFolder(ITEM_ASSETS_DIR_PATH);
        runScriptsInFolder(CHARA_ASSETS_DIR_PATH);
        std::cout<<"Charactor assets loading results begin"<<std::endl;
        int n=0;
        for(Assets::ItemPtrType i:m_itemTbl){
            std::cout<<"Charactor "<<n<<" "<<i->getName()<<std::endl;
        }
        std::cout<<"Charactor assets loading results end"<<std::endl;

        std::cout<<"Item assets loading results begin"<<std::endl;
        n=0;
        for(Assets::ItemPtrType c:m_itemTbl){
            std::cout<<"Item "<<n<<" "<<c->getName()<<std::endl;
        }
        std::cout<<"Item assets loading results end"<<std::endl;

    }

    std::string CGameEngine::openRootbox(){
        std::normal_distribution<> dist2(0, m_charaTbl.size());
        int idx=dist2(m_randEngine);
        return m_charaTbl[idx]->getName();
        
    }
    void CGameEngine::beginUI(UI::UI_POS pos){
        m_uiPosMode=pos;
        m_nextWidgetPos=Geometory::CPoint(calcUIX(pos),calcUIY(pos));
    }
    void CGameEngine::addUI(UI::WidgetPtrType p,bool doBreak){
       /* int w=p->getRect().getWidth();
        int h=p->getRect().getHeight();
        
        p->getRect().offset(m_nextWidgetPos.getX(),m_nextWidgetPos.getY());
       */
        p->calcRect(m_nextWidgetPos.getX(), m_nextWidgetPos.getY());
        int w=p->getRect().getWidth();
        int h=p->getRect().getHeight();
        m_widgetTbl.push_back(p);
        if(doBreak){
            m_nextWidgetPos.setX(calcUIX(m_uiPosMode));
            m_nextWidgetPos.setY(m_nextWidgetPos.getY()+h);
        }else{
            m_nextWidgetPos.setX(m_nextWidgetPos.getX()+w);

        }
    }

    void CGameEngine::endUI(){}
    int CGameEngine::calcUIX(UI::UI_POS pos){
        switch (pos) {
            case UI::UI_POS::NORTH:
                return m_drawRect.getLeft();
                break;
            case UI::UI_POS::SOUTH:{
                return m_drawRect.getLeft();
            }break;;
            case UI::UI_POS::WEST:{
                return m_drawRect.getLeft();
            }break;
            case UI::UI_POS::EAST:{
                return m_drawRect.getLeft()+m_drawRect.getWidth()/3*2;
            }break;
            case UI::UI_POS::CENTER:{
                return m_drawRect.getLeft()+m_drawRect.getWidth()/3;
            }break;
        }

    }
    int CGameEngine::calcUIY(UI::UI_POS pos){
        switch (pos) {
            case UI::UI_POS::NORTH:
                return m_drawRect.getTop();
                break;
            case UI::UI_POS::SOUTH:{
                return m_drawRect.getTop()+m_drawRect.getHeight()/3*2;
            }break;;
            case UI::UI_POS::WEST:{
                return m_drawRect.getTop()+m_drawRect.getHeight()/3;
            }break;
            case UI::UI_POS::EAST:{
                return m_drawRect.getTop()+m_drawRect.getHeight()/3;
            }break;
            case UI::UI_POS::CENTER:{
                return m_drawRect.getTop()+m_drawRect.getHeight()/3*2;
            }break;
        }

    }
    void CGameEngine::setMouseInputState(int x,int y,bool mouseClick){
        m_mousePos[m_nextInputIdx]=Geometory::CPoint(x,y);
        m_mouseDown[m_nextInputIdx]=mouseClick;
    }
    void CGameEngine::changeNextInputData(){
        m_checkInputIdx=m_nextInputIdx;
        ++m_nextInputIdx;
        m_nextInputIdx%=INPUT_ARRAY_NUM;

    }
    void CGameEngine::procInputEvents(){
        Geometory::CPoint& po=m_mousePos[m_checkInputIdx];
        bool isClick=m_mouseDown[m_checkInputIdx] && !m_mouseDown[m_nextInputIdx];
        if(isClick){
            for(UI::WidgetPtrType p:getWidgetTbl()){
                if(p->isInside(po.getX(), po.getY())){
                    p->onClick(this);
                   // std::cout<<"click"<<std::endl;
                    break;
                }
            }
        }
    }
    void CGameEngine::returnPrevState(void* p){
        assert(nullptr!=p);
        CGameEngine* pE=(CGameEngine*)p;
        pE->popState();
    }
    int CGameEngine::charaLispFunc(Scripting::CVM& vm,int argNum,void* pUD){
        Assets::CharaPtrType pChara(new Assets::CCharacter());
        
        for(int i=0;i < argNum;++i){
            Scripting::ValuePtrType v=vm.pop();
            
                Scripting::CPairValueType* pPair=(Scripting::CPairValueType*)v.get();
                if(pPair->getValue().first=="name"){
                    pChara->setName(pPair->getValue().second);
                }else if(pPair->getValue().first=="type"){
                    pChara->setType(Assets::charaTypeFromString(pPair->getValue().second));
                }else if(pPair->getValue().first=="life"){
                    pChara->setLifeRank(Assets::rankFromString(pPair->getValue().second));
                }else if(pPair->getValue().first=="atk"){
                    pChara->setAtkRank(Assets::rankFromString(pPair->getValue().second));
                }else if(pPair->getValue().first=="airAtk"){
                    pChara->setAirAtkRank(Assets::rankFromString(pPair->getValue().second));
                }else if(pPair->getValue().first=="airDef"){
                    pChara->setAirDefRank(Assets::rankFromString(pPair->getValue().second));
                }else if(0==pPair->getValue().first.compare(0,4,"item")){
                    std::string idxPart=pPair->getValue().first.substr(4);
                    int idx=atoi(idxPart.c_str());
                    Assets::ItemPtrType item;
                    for(Assets::ItemPtrType pt:(s_self.get()->m_itemTbl)){
                        if(pPair->getValue().second==pt->getName()){
                            item=pt;
                        }
                    }
                    
                    pChara->setItem(idx, item);
                }
            }
        
        CGameEngine* pE=(CGameEngine*)pUD;
        pE->m_charaTbl.push_back(pChara);
        return 0;
    }

    int CGameEngine::itemLispFunc(Scripting::CVM& vm,int argNum,void* pUD){
        Assets::ItemPtrType pItem(new Assets::CItem());
        for(int i=0;i < argNum;++i){
            Scripting::ValuePtrType v=vm.pop();
                Scripting::CPairValueType* pPair=(Scripting::CPairValueType*)v.get();
                if(pPair->getValue().first=="name"){
                    pItem->setName(pPair->getValue().second);
                }else if(pPair->getValue().first=="atk"){
                    pItem->setAtkRank(Assets::rankFromString(pPair->getValue().second));
                }else if(pPair->getValue().first=="coolTime"){
                    pItem->setCoolTimeRank(Assets::rankFromString(pPair->getValue().second));
                }
            }
        
        CGameEngine* pE=(CGameEngine*)pUD;
        pE->m_itemTbl.push_back(pItem);

        return 0;
    }

}
