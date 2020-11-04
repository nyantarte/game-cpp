#include <iostream>
#include "test.hpp"
namespace Test{
    CSingleton<CTestCase::TEST_LIST_TYPE> CTestCase::s_testList;
    void CTestCase::assert_test(bool state,const char* srcFile,int line){
        if(! state){
            std::cerr<<"Assert exception:"<<srcFile<<"["<<line<<"]"<<std::endl;
            assert(state);
        }else{
            std::cout<<"Assert test passes:"<<srcFile<<"["<<line<<"]"<<std::endl;
        }
    }

    void CTestCase::execute_tests(){
        for( TEST_LIST_TYPE::value_type& vt:*s_testList.get()){
            vt->test();
        }
    }

}
