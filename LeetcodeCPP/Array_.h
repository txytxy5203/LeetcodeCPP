#pragma once
#include <vector>
#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

class Array_
{
public:
    void reverseString(vector<char>& s) 
    {
        // https://leetcode.cn/problems/reverse-string/description/
        // 加油   Cpp不熟悉也不要害怕  
        
        for (int left = 0, right = s.size() - 1; left < right; left++,right--)
        {
            swap(s[left], s[right]);
        }
    }
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) 
    {
        // https://leetcode.cn/problems/flip-square-submatrix-vertically/description/
        int up = x;
        int down = x + k - 1;
        while (up < down)
        {
            for (size_t j = y; j < y + k ; j++)
            {
                int temp = grid[up][j];
                grid[up][j] = grid[down][j];
                grid[down][j] = temp;
                
            }
            up++;
            down--;
        }
        return grid;
    }
    string reverseVowels(string s) 
    {
        // https://leetcode.cn/problems/reverse-vowels-of-a-string/description/
        unordered_set<char> set = { 'a','e','i','o','u','A','E','I','O','U'};

        for (int left = 0, right = s.size(); left < right;)
        {
            if (set.find(s[left]) == set.end())
            {
                left++;
            }
            if (set.find(s[right]) == set.end())
            {
                right--;
            }
            if (set.find(s[left]) != set.end() && set.find(s[right]) != set.end())
            {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }
        return s;
    }
    bool isPalindrome(string s) 
    {
        // https://leetcode.cn/problems/valid-palindrome/description/        
        for (int i = 0, j = s.size() - 1; i < j;)           // 灵神的这一手还是有细节的
        {
            if (!isalnum(s[i]))
            {
                i++;
            }
            else if (!isalnum(s[j])) 
            {
                j--;
            }
            else if (tolower(s[i]) == tolower(s[j])) 
            {
                i++;
                j--;
            }
            else 
            {
                return false;
            }
        }
        return true;        
    }
    int minimumLength(string s) 
    {
        // https://leetcode.cn/problems/minimum-length-of-string-after-deleting-similar-ends/description/
        int left = 0;
        int right = s.size() - 1;
        while (left < right && s[left] == s[right])
        {
            char c = s[left];
            while (s[left] == c && left <= right)
                left++;
            while (s[right] == c && left <= right)
                right--;
        }
        return right - left + 1;
    }
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) 
    {
        // https://leetcode.cn/problems/watering-plants-ii/description/
        int ans = 0;
        int left = 0;
        int right = plants.size() - 1;
        int a = capacityA;
        int b = capacityB;

        auto water = [&](int& can, int need, int capacity) // [&] 让 ans 可见；int&/int 接收调用
        {
            if (can < need) {
                can = capacity;
                ans++;
            }
            can -= need;
        };

        
        
        while (left <= right)
        {            
            if (left == right)
            {
                if (a >= b)
                    water(a, plants[left], capacityA);
                else
                    water(b, plants[left], capacityB);
                
                return ans;
            }
            water(a, plants[left++], capacityA);
            water(b, plants[right--], capacityB);
        }
        return ans;
    }
    vector<int> sortedSquares(vector<int>& nums) 
    {
        // https://leetcode.cn/problems/squares-of-a-sorted-array/description/
        vector<int> ans;
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right)
        {

        }
    }
    vector<int> searchRange(vector<int>& nums, int target) 
    {
        // https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/description/
        auto lower = [&](int i)
        {
            int left = 0;
            int right = nums.size() -  1;
            while (left <= right)
            {
                int mid = left + (right - left) / 2;
                if (nums[mid] < i)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            return left;
        };
        int first = lower(target);
        int second = lower(target + 1) - 1;
        if (first == nums.size() || nums[first] != target)
        {
            return {-1, -1};
        }
        return { first, second };
    }
    int search(vector<int>& nums, int target) 
    {
        // https://leetcode.cn/problems/binary-search/description/
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        if (left == nums.size() || nums[left] != target)
            return -1;
        return left;
    }
};