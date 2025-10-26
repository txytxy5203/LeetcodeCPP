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
    char nextGreatestLetter(vector<char>& letters, char target) 
    {
        // https://leetcode.cn/problems/find-smallest-letter-greater-than-target/description/
        int left = 0;
        int right = letters.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (letters[mid] < target + 1)
                left = mid + 1;
            else
                right = mid - 1;
        }
        if (left == letters.size() )
            return letters[0];
        return letters[left];
    }
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) 
    {
        // https://leetcode.cn/problems/successful-pairs-of-spells-and-potions/description/
        // 这个题灵神的题解太重要了   乘法溢出的问题
        vector<int> ans;
        sort(potions.begin(), potions.end());           // 先升序
        int size = potions.size();
        auto lower = [&](int multiple)
        {
            int left = 0;
            int right = size - 1;
            while (left <= right)
            {
                int mid = left + (right - left) / 2;
                if (potions[mid] < success / multiple)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            return left;
        };

        for (int i : spells)
        {
            auto num = lower(i);
            ans.push_back(size - num);
        }
        return ans;
    }
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) 
    {
        // https://leetcode.cn/problems/find-the-distance-value-between-two-arrays/description/
        sort(arr2.begin(), arr2.end());
        auto lower = [&](int target)
        {
            int left = 0;
            int right = arr2.size() - 1;
            while (left <= right)
            {
                int mid = left + (right - left) / 2;
                if (arr2[mid] < target)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            return left;
        };

        int ans = 0;
        for (int i = 0; i < arr1.size(); i++)
        {
            int first = lower(arr1[i] - d);
            int second = lower(arr1[i] + d + 1);
            if (first == second)
                ans++;
        }
        return ans;
    }
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) 
    {
        // https://leetcode.cn/problems/longest-subsequence-with-limited-sum/description/
        
        auto lower = [&](int target)
        {
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
            return left;
        };

        sort(nums.begin(), nums.end());     
        for (int i = 1; i < nums.size(); i++)       // 前缀和
        {
            nums[i] += nums[i - 1];
        }

        vector<int> ans;
        for (int i = 0; i < queries.size(); i++)
        {
            int num = lower(queries[i] + 1);            // 灵活地 +1 -11
            ans.push_back(num);
        }
        return ans;
    }
    int smallestDivisor(vector<int>& nums, int threshold) 
    {
        // https://leetcode.cn/problems/find-the-smallest-divisor-given-a-threshold/description/
        auto check = [&](int mid)
            {
                int sum = 0;
                for (int i = 0; i < nums.size(); i++)
                {
                    sum += (nums[i] + mid - 1 ) / mid;
                    if (sum > threshold)
                        return false;
                }
                return true;
            };

        int left = 1;
        int right = *max_element(nums.begin(), nums.end());
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (check(mid))                             // 这边依旧是 一个 +1  一个 -1
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;
    }
    long long minimumTime(vector<int>& time, int totalTrips) 
    {
        // https://leetcode.cn/problems/minimum-time-to-complete-trips/description/
        // 灵神 二分找最小的答案  模板
        auto check = [&](long long mid)
            {
                long long sum = 0;
                for(int i : time)
                {
                    sum += mid / (long long)i;
                    if (sum >= totalTrips)
                        return true;
                }
                return false;
            };

        long long left = 0;
        long long right = (long long)*min_element(time.begin(), time.end()) * (long long)totalTrips;
        while (left <= right)
        {
            long long mid = left + (right - left) / 2;
            if (check(mid))                             // 这边依旧是 一个 +1  一个 -1
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;
    }
    int shipWithinDays(vector<int>& weights, int days) 
    {
        // https://leetcode.cn/problems/capacity-to-ship-packages-within-d-days/description/
        auto check = [&](int mid)
            {
                int time = 1, last = 0;
                for (int i = 0; i < weights.size(); i++)
                {
                    if (weights[i] - last > mid)
                    {
                        last = weights[i - 1];
                        time++;
                        if (time > days)
                            return false;
                    }
                }
                return true;
            };
        int left = *max_element(weights.begin(), weights.end());

        for (int i = 1; i < weights.size(); i++)
        {
            weights[i] += weights[i - 1];
        }
        int right = weights[weights.size() - 1];

        while (left <= right) 
        {
            int mid = left + (right - left) / 2;
            if (check(mid))
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;
    }
    int hIndex(vector<int>& citations) 
    {
        // https://leetcode.cn/problems/h-index-ii/description/ 
        // 二分找答案 求最大  最后返回的是right

        //  FFFFFFTTTTTTT
        //  TTTTTTFFFFFFF
        // 看上面这个就懂了 返回right or left
        auto check = [&](int mid)
            {
                return citations[citations.size() - mid] >= mid;
            };
        int left = 1;
        int right = citations.size();
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (check(mid))
                left = mid + 1;
            else
                right = mid - 1;
        }
        return right;           // 记住最后返回的是 right
    }
};