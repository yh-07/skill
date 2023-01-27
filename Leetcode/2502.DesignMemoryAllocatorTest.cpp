/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->free(mID);
 */
#include "2502.DesignMemoryAllocator.hpp"

 /**
  * Your Allocator object will be instantiated and called as such:
  * Allocator* obj = new Allocator(n);
  * int param_1 = obj->allocate(size,mID);
  * int param_2 = obj->free(mID);
  */

vector<string> opt_str = { "Allocator", "allocate", "allocate", "allocate", "allocate", "free", "free", "free", "allocate", "allocate", "allocate", "allocate", "free", "free", "free", "free", "free", "free", "free", "allocate", "free", "free", "allocate", "free", "allocate", "allocate", "free", "free", "free", "allocate", "allocate", "allocate", "allocate", "free", "allocate", "free", "free", "allocate", "allocate", "allocate", "allocate", "allocate", "allocate", "allocate", "free", "free", "free", "free" };
vector<vector<int>> param_list = {{50}, {12, 6}, {28, 16}, {17, 23}, {50, 23}, {6}, {10}, {10}, {16, 8}, {17, 41}, {44, 27}, {12, 45}, {33}, {8}, {16}, {23}, {23}, {23}, {29}, {38, 32}, {29}, {6}, {40, 11}, {16}, {22, 33}, {27, 5}, {3}, {10}, {29}, {16, 14}, {46, 47}, {48, 9}, {36, 17}, {33}, {14, 24}, {16}, {8}, {2, 50}, {31, 36}, {17, 45}, {46, 31}, {2, 6}, {16, 2}, {39, 30}, {33}, {45}, {30}, {27}};
//vector<vector<int>> param_list = { {10} ,{1, 1},{1, 2},{1, 3},{2},{3, 4},{1, 1},{1, 1},{1},{10, 2},{7} };
void TestDesignMemoryAllocator() {
    //Input
    //    ["Allocator", "allocate", "allocate", "allocate", "free", "allocate", "allocate", "allocate", "free", "allocate", "free"]
    //[[10], [1, 1], [1, 2], [1, 3], [2], [3, 4], [1, 1], [1, 1], [1], [10, 2], [7]]
    //Output
    //    [null, 0, 1, 2, 1, 3, 1, 6, 3, -1, 0]
    auto it_opt = opt_str.begin();
    auto it_param = param_list.begin();

    Allocator* obj = new Allocator((*it_param)[0]);

    it_opt++;
    it_param++;

    int ret = -1;

    int id, size;
    while (it_opt != opt_str.end()) {
        if (*it_opt == "allocate") {
            id = (*it_param)[0];
            size = (*it_param)[1];
            ret = obj->allocate(id, size);
            cout << ret << endl;
        }
        else if (*it_opt == "free") {
            id = (*it_param)[0];
            ret = obj->free(id);
            cout << ret << endl;
        }
        it_opt++;
        it_param++;
    }
}