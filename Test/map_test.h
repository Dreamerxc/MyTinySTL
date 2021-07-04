//
// Created by Dreamer.c on 2021/6/26.
//

#ifndef MYTINYSTL_MAP_TEST_H
#define MYTINYSTL_MAP_TEST_H
#include "map.h"

// map 的遍历输出
#define map_print(m) do { \
    for (auto it : m)    std::cout << " <" << it.first << "," << it.second << ">"; \
    std::cout << std::endl; \
} while(0)

// map 的函数操作
#define Print_Map(t, s) do { \
    std::cout << t; \
    map_print(s); \
} while(0)

namespace MyTinySTL
{
    namespace test
    {
        void map_test() {
            std::cout << "==================================\n";
            std::cout << "========= map test ============\n";
            std::cout << "==================================\n";
            map<int, int> mp;
            map<int, int> mp1(mp);
            map<int, int> mp2(MyTinySTL::move(mp1));
            mp = mp2;

            mp.emplace(1, 2);
            mp.emplace(3, 4);
            mp.emplace(1, 3);
            mp.emplace(2, 4);
            Print_Map("after emplace some elems: ", mp);

            mp.insert(std::pair<int, int>(4, 4));
            mp.insert(std::pair<int, int>(5, 6));
            Print_Map("after insert some elems: ", mp);

            mp.erase(1);
            Print_Map("after erase key: ", mp);

            mp.erase(mp.begin());
            Print_Map("after erase begin elems: ", mp);

            mp[3] = 6;
            mp[6]++;
            Print_Map("after use []: ", mp);

            std::cout << "max_size(): " << mp.max_size() << std::endl;
#if PERFORMANCE_TEST_ON
            std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
            std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
            std::cout << "|       emplace       |";
#if LARGER_TEST_DATA_ON
            MAP_EMPLACE_TEST(map, LEN1 _L, LEN2 _L, LEN3 _L);
#else
            MAP_EMPLACE_TEST(map, LEN1 _M, LEN2 _M, LEN3 _M);
#endif
            std::cout << std::endl;
            std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
            PASSED;
#endif
        }
    }

}









#endif //MYTINYSTL_MAP_TEST_H
