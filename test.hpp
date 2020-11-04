#pragma once
#include <memory>
#include <list>
#include "singleton.hpp"

namespace Test{
    class CTestCase{
        typedef std::list<CTestCase*> TEST_LIST_TYPE;
        static CSingleton<TEST_LIST_TYPE> s_testList;

    public:
        CTestCase()
        {
            s_testList.get()->push_back(this);
        }

        virtual ~CTestCase(){}
        virtual void test(){}


        virtual void assert_test(bool state,const char* srcFile,int line);
        
        
        static void execute_tests();
    };
}
