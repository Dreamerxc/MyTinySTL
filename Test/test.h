// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/5/16 14:13
// Description:
//

#pragma once
#include <ctime>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>

namespace MyTinySTL {
    namespace test {
        // TestCase 类
        // 封装单个测试案例
        class TestCase {
        public:
            TestCase(const char *case_name) : testcase_name(case_name) {}

            virtual void Run() = 0;

        public:
            const char *testcase_name;   // 测试案例名称
            int Result;          // 测试案例执行结果
            int PassResult;      // 测试通过的案例数
            int FailResult;      // 测试成功的案例数
        };

        // 单元测试类 把所有测试案例加入到 Vector 中，依次执行测试案例
        class UnitTest {
        public:
            // 获得一个案例
            static UnitTest *GetInstance();

            // 将案例依次加入 std::vector
            TestCase *RegisterTestCase(TestCase *testcase);

            void Run();

        public:
            TestCase *CurrentTestCase;  // 当前执行的测试案例
            int PassResult;       // 测试通过的案例数
            int FailResult;       // 测试通过案例数

        protected:
            std::vector<TestCase *> testcases;  // 保存案例集合
        };

        UnitTest *UnitTest::GetInstance() {
            static UnitTest instance;
            return &instance;
        }

        TestCase *UnitTest::RegisterTestCase(TestCase *testcase) {
            testcases.push_back(testcase);
            return testcase;
        }

        void UnitTest::Run() {
            for (auto it : testcases) {
                TestCase *testcase = it;
                CurrentTestCase = testcase;
                testcase->Result = 1;
                testcase->PassResult = 0;
                testcase->FailResult = 0;
                testcase->Run();
            }
        }

#define Print_Vector(v) {                \
    std::cout<<#v<<":";      \
    for (auto x : v) {                   \
       std::cout<< x << " ";             \
    }                                    \
    std::cout<<std::endl;                \
}

#define Print_List(t, v) {                  \
    std::cout<< t << #v << ":";                  \
    for (auto x : v) {                   \
       std::cout<< x << " ";             \
    }                                    \
    std::cout<<std::endl;               \
}

#define Print(t, v) {                  \
    std::cout<< t << #v << ":";                  \
    for (auto x : v) {                   \
       std::cout<< x << " ";             \
    }                                    \
    std::cout<<std::endl;               \
}

#define Print_stack1(t, v) { \
   std::cout<< t << #v << ":";   \
   while (!v.empty()) {              \
        std::cout << v.top() << " "; \
        v.pop();                     \
   }                       \
   std::cout<<std::endl;   \
   }                    \
                             \
    // 不同情况的测试数量级
#if defined(_DEBUG) || defined(DEBUG)
        #define LEN1    10000
#define LEN2    100000
#define LEN3    1000000
#else
#define LEN1    100000
#define LEN2    1000000
#define LEN3    10000000
#endif

#define _LLL * 20
#define _LL  * 10
#define _L   * 5
#define _M
#define _S   / 5
#define _SS  / 10
#define _SSS / 20

#define WIDE    14


// 输出测试数量级
        void test_len(size_t len1, size_t len2, size_t len3, size_t wide)
        {
            std::string str1, str2, str3;
            std::stringstream ss;
            ss << len1 << " " << len2 << " " << len3;
            ss >> str1 >> str2 >> str3;
            str1 += "   |";
            std::cout << std::setw(wide) << str1;
            str2 += "   |";
            std::cout << std::setw(wide) << str2;
            str3 += "   |";
            std::cout << std::setw(wide) << str3 << "\n";
        }

        // 常用测试性能的宏
#define FUN_TEST_FORMAT1(mode, fun, arg, count) do {         \
  srand((int)time(0));                                       \
  clock_t start, end;                                        \
  mode c;                                                    \
  char buf[10];                                              \
  start = clock();                                           \
  for (size_t i = 0; i < count; ++i)                         \
    c.fun(arg);                                              \
  end = clock();                                             \
  int n = static_cast<int>(static_cast<double>(end - start)  \
      / CLOCKS_PER_SEC * 1000);                              \
  std::snprintf(buf, sizeof(buf), "%d", n);                  \
  std::string t = buf;                                       \
  t += "ms    |";                                            \
  std::cout << std::setw(WIDE) << t;                         \
} while(0)


#define FUN_TEST_FORMAT2(mode, fun, arg1, arg2, count) do {  \
  srand((int)time(0));                                       \
  clock_t start, end;                                        \
  mode c;                                                    \
  char buf[10];                                              \
  start = clock();                                           \
  for (size_t i = 0; i < count; ++i)                         \
    c.fun(c.arg1(), arg2);                                   \
  end = clock();                                             \
  int n = static_cast<int>(static_cast<double>(end - start)  \
      / CLOCKS_PER_SEC * 1000);                              \
  std::snprintf(buf, sizeof(buf), "%d", n);                  \
  std::string t = buf;                                       \
  t += "ms    |";                                            \
  std::cout << std::setw(WIDE) << t;                         \
} while(0)


#define TEST_LEN(len1, len2, len3, wide) \
  test_len(len1, len2, len3, wide)
// 重构重复代码
#define CON_TEST_P1(con, fun, arg, len1, len2, len3)         \
  TEST_LEN(len1, len2, len3, WIDE);                          \
  std::cout << "|         std         |";                    \
  FUN_TEST_FORMAT1(std::con, fun, arg, len1);                \
  FUN_TEST_FORMAT1(std::con, fun, arg, len2);                \
  FUN_TEST_FORMAT1(std::con, fun, arg, len3);                \
  std::cout << "\n|     MyTinySTL       |";                  \
  FUN_TEST_FORMAT1(MyTinySTL::con, fun, arg, len1);              \
  FUN_TEST_FORMAT1(MyTinySTL::con, fun, arg, len2);              \
  FUN_TEST_FORMAT1(MyTinySTL::con, fun, arg, len3);

#define CON_TEST_P2(con, fun, arg1, arg2, len1, len2, len3)  \
  TEST_LEN(len1, len2, len3, WIDE);                          \
  std::cout << "|         std         |";                    \
  FUN_TEST_FORMAT2(std::con, fun, arg1, arg2, len1);         \
  FUN_TEST_FORMAT2(std::con, fun, arg1, arg2, len2);         \
  FUN_TEST_FORMAT2(std::con, fun, arg1, arg2, len3);         \
  std::cout << "\n|     MyTinySTL       |";                   \
  FUN_TEST_FORMAT2(MyTinySTL::con, fun, arg1, arg2, len1);       \
  FUN_TEST_FORMAT2(MyTinySTL::con, fun, arg1, arg2, len2);       \
  FUN_TEST_FORMAT2(MyTinySTL::con, fun, arg1, arg2, len3);

#define MAP_EMPLACE_TEST(con, len1, len2, len3)              \
  TEST_LEN(len1, len2, len3, WIDE);                          \
  std::cout << "|         std         |";                    \
  MAP_EMPLACE_DO_TEST(std, con, len1);                       \
  MAP_EMPLACE_DO_TEST(std, con, len2);                       \
  MAP_EMPLACE_DO_TEST(std, con, len3);                       \
  std::cout << "\n|     MyTinySTL       |";                   \
  MAP_EMPLACE_DO_TEST(MyTinySTL, con, len1);                     \
  MAP_EMPLACE_DO_TEST(MyTinySTL, con, len2);                     \
  MAP_EMPLACE_DO_TEST(MyTinySTL, con, len3);

#define MAP_EMPLACE_DO_TEST(mode, con, count) do {           \
  srand((int)time(0));                                       \
  clock_t start, end;                                        \
  mode::con<int, int> c;                                     \
  char buf[10];                                              \
  start = clock();                                           \
  for (size_t i = 0; i < count; ++i)                         \
    c.emplace(std::make_pair(rand(), rand()));              \
  end = clock();                                             \
  int n = static_cast<int>(static_cast<double>(end - start)  \
      / CLOCKS_PER_SEC * 1000);                              \
  std::snprintf(buf, sizeof(buf), "%d", n);                  \
  std::string t = buf;                                       \
  t += "ms    |";                                            \
  std::cout << std::setw(WIDE) << t;                         \
} while(0)

        // 是否开启性能测试
#ifndef PERFORMANCE_TEST_ON
#define PERFORMANCE_TEST_ON 1
#endif // !PERFORMANCE_TEST_ON

// 是否开启大数据量测试
#ifndef LARGER_TEST_DATA_ON
#define LARGER_TEST_DATA_ON 1
#endif // !LARGER_TEST_DATA_ON

// 输出通过提示
#define PASSED    std::cout << "[ PASSED ]\n"
    }
}