//
// Created by Dreamer.c on 2021/6/29.
//

#ifndef MYTINYSTL_SET_TEST_H
#define MYTINYSTL_SET_TEST_H

#include "set.h"

// map 的遍历输出
#define set_print(m) do { \
     for (auto x: st) {  \
        std::cout<< x << " ";  \
     }  \
    std::cout << std::endl; \
} while(0)

// map 的函数操作
#define Print_Set(t, s) do { \
    std::cout << t; \
    set_print(s); \
} while(0)

namespace MyTinySTL
{
    namespace test
    {
        void set_test()
        {
            std::cout << "==================================\n";
            std::cout << "========= map test ============\n";
            std::cout << "==================================\n";
            set<int> st;
            set<int> st1(st);
            set<int> st2(MyTinySTL::move(st1));
            st = st2;

            st.insert(1);
            st.insert(5);
            st.insert(3);
            st.insert(4);
            st.insert(2);
            st.insert(3);
            Print_Set("after insert some elems: ", st);

            st.emplace(6);
            st.emplace(7);
            st.emplace(7);
            Print_Set("after emplace some elems: ", st);

            std::cout << "the first elem: " << *st.begin() << std::endl;
            std::cout << "the set size: " << st.size() << std::endl;

            st.erase(1);
            Print_Set("after erase the key [1]: ", st);

            st.erase(st.begin());
            Print_Set("after erase the first elem: ", st);

            std::cout << "max_size(): " << st.max_size() << std::endl;
#if PERFORMANCE_TEST_ON
            std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
            std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
            std::cout << "|       emplace       |";
#if LARGER_TEST_DATA_ON
            CON_TEST_P1(set<int>, emplace, rand(), LEN1 _L, LEN2 _L, LEN3 _L);
#else
            CON_TEST_P1(set<int>, emplace, rand(), LEN1 _M, LEN2 _M, LEN3 _M);
#endif
            std::cout << std::endl;
            std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
            PASSED;
#endif

        }
    }
}









#endif //MYTINYSTL_SET_TEST_H
