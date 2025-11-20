/*
Given:
- Array of integers called nums
- Integer target

Task:
- Return indices of the two #s that add up to target

Constraint:
- Only one valid solution exists

Idea: 
- Store each value in a map, where the value is target-its value
    - O(n) time and O(n) space
- Compare every value against each other
    - O(n^2) time and O(c) space

For idea 1: 
1 2 3 where target is 4

map[3] = 0
- Store the partner value and set that equal to the index of the original
- therefore, if we find the partner we know exactly which index to call for the other value

Pseudocode:

two_sum (nums, target)
    define map
    for (int i in nums)
        if nums[i] is not in map
            int intention = target - nums[i]
            map[intention] = i
        else
            pair = (i, map[nums[i]])
            return pair

*/

#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

pair<int,int> two_sum(vector<int>& nums, int target) {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++) {
        if (map.count(nums[i]) == 0) {
            int intention = target - nums[i];
            map[intention] = i;
        } else {
            pair<int,int> p = {map[nums[i]], i};
            return p;
        }
    }
    return {0, 0};
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    pair<int,int> p = two_sum(nums, target);
    cout << p.first << " " << p.second;
    return 0;
}