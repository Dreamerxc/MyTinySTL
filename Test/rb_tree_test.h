//
// Created by 谯保林 on 2021/6/20.
//

#ifndef MYTINYSTL_RB_TREE_TEST_H
#define MYTINYSTL_RB_TREE_TEST_H

#endif //MYTINYSTL_RB_TREE_TEST_H
#include "rb_tree.h"
#include <functional>

void rbtree_print(MyTinySTL::rb_tree<int, std::less<int>> s)
{
   for (auto x = s.begin(); x!= s.end();x++) {
       std::cout << *x << " ";
   }
    std::cout << std::endl;
}

// stack 的遍历输出
#define Print_Rbtree(t,s) do {                       \
    std::cout << t << " " ;          \
    rbtree_print(s);                              \
} while(0)

namespace MyTinySTL
{
    namespace test {
        void rb_tree_test() {
            std::cout << "==================================\n";
            std::cout << "========= rb_tree test ============\n";
            std::cout << "==================================\n";

            rb_tree<int, std::less<int>> tree1;
            rb_tree<int, std::less<int>> tree2(tree1);
            rb_tree<int, std::less<int>> tree3(MyTinySTL::move(tree1));

            tree2 = tree1;
            tree3 = MyTinySTL::move(tree2);

            tree3.emplace_multi(2);
            tree3.emplace_multi(3);
            tree3.emplace_multi(1);
            tree3.emplace_multi(1);
            Print_Rbtree("after emplace some elems: ", tree3);
            std::cout << "tree3 size(): " << tree3.size() << std::endl;

            tree3.emplace_multi_at_pos(tree3.begin(), 4);
            tree3.emplace_multi_at_pos(tree3.begin(), 3);
            Print_Rbtree("after emplace some elems at begin(): ", tree3);

            tree3.insert_multi(6);
            Print_Rbtree("after insert value: ", tree3);

            tree3.erase(tree3.begin());
            tree3.erase(tree3.begin());

            Print_Rbtree("after erase two elems: ", tree3);

            auto it = tree3.find(2);
            if (it != tree3.end()) {
                std::cout << "find value: " << *it << std::endl;
            }

            tree3.clear();
            Print_Rbtree("after clear: ", tree3);
            std::cout << "tree3 size: " << tree3.size() << std::endl;

            std::cout << "==================================\n";
            tree3.emplace_unique(2);
            tree3.emplace_unique(3);
            tree3.emplace_unique(1);
            tree3.emplace_unique(1);
            Print_Rbtree("after emplace unique some elems: ", tree3);
            std::cout << "tree3 size(): " << tree3.size() << std::endl;

            tree3.emplace_unique_at_pos(tree3.begin(), 4);
            tree3.emplace_unique_at_pos(tree3.begin(), 3);
            Print_Rbtree("after emplace unique some elems at begin(): ", tree3);

            tree3.insert_unique(3);
            Print_Rbtree("after insert unique value: ", tree3);

            tree3.insert_unique(5);
            Print_Rbtree("after insert unique value: ", tree3);

            tree3.erase(tree3.begin());
            tree3.erase(tree3.begin());
            Print_Rbtree("after erase two elems: ", tree3);
        }
    }
}