/*
You are given an integer n representing the size of a 0-indexed memory array. All memory units are initially free.

You have a memory allocator with the following functionalities:

Allocate a block of size consecutive free memory units and assign it the id mID.
Free all memory units with the given id mID.
Note that:

Multiple blocks can be allocated to the same mID.
You should free all the memory units with mID, even if they were allocated in different blocks.
Implement the Allocator class:

Allocator(int n) Initializes an Allocator object with a memory array of size n.
int allocate(int size, int mID) Find the leftmost block of size consecutive free memory units and allocate it with the id mID. Return the block's first index. If such a block does not exist, return -1.
int free(int mID) Free all memory units with the id mID. Return the number of memory units you have freed.


Example 1:

Input
["Allocator", "allocate", "allocate", "allocate", "free", "allocate", "allocate", "allocate", "free", "allocate", "free"]
[[10], [1, 1], [1, 2], [1, 3], [2], [3, 4], [1, 1], [1, 1], [1], [10, 2], [7]]
Output
[null, 0, 1, 2, 1, 3, 1, 6, 3, -1, 0]

Explanation
Allocator loc = new Allocator(10); // Initialize a memory array of size 10. All memory units are initially free.
loc.allocate(1, 1); // The leftmost block's first index is 0. The memory array becomes [1,_,_,_,_,_,_,_,_,_]. We return 0.
loc.allocate(1, 2); // The leftmost block's first index is 1. The memory array becomes [1,2,_,_,_,_,_,_,_,_]. We return 1.
loc.allocate(1, 3); // The leftmost block's first index is 2. The memory array becomes [1,2,3,_,_,_,_,_,_,_]. We return 2.
loc.free(2); // Free all memory units with mID 2. The memory array becomes [1,_, 3,_,_,_,_,_,_,_]. We return 1 since there is only 1 unit with mID 2.
loc.allocate(3, 4); // The leftmost block's first index is 3. The memory array becomes [1,_,3,4,4,4,_,_,_,_]. We return 3.
loc.allocate(1, 1); // The leftmost block's first index is 1. The memory array becomes [1,1,3,4,4,4,_,_,_,_]. We return 1.
loc.allocate(1, 1); // The leftmost block's first index is 6. The memory array becomes [1,1,3,4,4,4,1,_,_,_]. We return 6.
loc.free(1); // Free all memory units with mID 1. The memory array becomes [_,_,3,4,4,4,_,_,_,_]. We return 3 since there are 3 units with mID 1.
loc.allocate(10, 2); // We can not find any free block with 10 consecutive free memory units, so we return -1.
loc.free(7); // Free all memory units with mID 7. The memory array remains the same since there is no memory unit with mID 7. We return 0.
*/
#include "2502.DesignMemoryAllocator.hpp"

void Allocator::free_block(pair<int, int> block) {
    int index = block.first;
    int size = block.second;
    // 查找block应在的位置
    auto it = free_list.begin();
    for (; it != free_list.end(); ++it) {
        if (it->first > block.first) {
            break;
        }
    }
    // 查看前一个block是否可以merge
    if (it != free_list.begin()) {
        --it;
        if (it->first + it->second == block.first) {
            index = (*it).first;
            size = (*it).second + block.second;
            it = free_list.erase(it);
        }
        else {
            ++it;
        }
    }
    // 查看后一个block是否可以merge
    if (it != free_list.end()) {
        if (block.first + block.second == (*it).first) {
            size += (*it).second;
            it = free_list.erase(it);
        }
    }

    free_list.insert(it, make_pair(index, size));
}


Allocator::Allocator(int n) {
    m_mem = (int*)malloc(n*sizeof(n));
    free_list.emplace_back(make_pair(0, n));
}

int Allocator::allocate(int size, int mID) {
    int index = -1;
    int free_index = -1;
    int free_size = 0;
    // erase first acceptable block from free_list
    for (auto it = free_list.begin(); it != free_list.end(); ++it) {
        if ((*it).second >= size) {
            index = (*it).first;
            free_index = index + size;
            free_size = (*it).second - size;
            free_list.remove(*it);
            if (free_size > 0) {
                free_block(make_pair(free_index, free_size));
            }
            if (used_map.find(mID) != used_map.end()) {
                used_map[mID].emplace_back(make_pair(index, size));
            }
            else {
                vector<pair<int, int>> tmp;
                tmp.emplace_back(make_pair(index, size));
                used_map[mID] = tmp;
            }

            cout << "after allocate" << endl;
            dump_free_list();
            break;
        }
    }
    return index;
}

int Allocator::free(int mID) {
    int ret = 0;
    if (used_map.find(mID) != used_map.end()) {
        for (auto v = used_map[mID].begin(); v != used_map[mID].end(); ++v) {
            ret += (*v).second;
            free_block(*v);
        }
        used_map.erase(mID);
        cout << "after free" << endl;
        dump_free_list();
    }
    return ret;
}

void Allocator::dump_free_list() {
    std::cout << "dump free list:" << std::endl;
    for (auto it = free_list.begin(); it != free_list.end(); it++) {
        std::cout << "index " << (*it).first << " size " << (*it).second << std::endl;
    }
}
