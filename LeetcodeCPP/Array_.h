#pragma once
#include <vector>
#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <cctype>
#include <numeric>      // std::reduce
#include <ranges>       // ranges::max （C++20 起）
#include <climits>
#include <queue>
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
    int maximumCandies(vector<int>& candies, long long k) 
    {
        // https://leetcode.cn/problems/maximum-candies-allocated-to-k-children/description/
        /*auto check = [&](int mid)
            {
                long long sum = 0;
                for (int i : candies)
                {
                    sum += i / mid;
                }
                return sum >= k;
            };

        long long avg = reduce(candies.begin(), candies.end(), 0LL) / k;
        int left = 1, right = min((long long)ranges::max(candies), avg) + 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (check(mid))
                left = mid + 1;
            else
                right = mid - 1;
        }
        return right;*/
    }
    int maximumLength(string s) 
    {
        // https://leetcode.cn/problems/find-longest-special-substring-that-occurs-thrice-ii/description/
        // 灵神还有复杂度更低的写法 以后记得看
        auto check = [&](int mid) -> bool
            {
                int record[26] = {};        // 数组一定要记得初始化 不是Cs！！
                int curr[26] = {};
                // 滑动窗口
                for (int i = 0; i < s.size(); i++)
                {
                    int ch = s[i] - 'a';
                    // in 
                    curr[ch]++;

                    int left = i - mid + 1;
                    if (left < 0)
                        continue;
                    
                    // update
                    if (curr[ch] == mid)
                    {
                        record[ch]++;
                        if (record[ch] >= 3)
                            return true;
                    }
                    // out 
                    curr[s[left] - 'a']--;
                }
                return false;
            };
        int left = 1;
        int right = s.size();
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (check(mid))
                left = mid + 1;
            else
                right = mid - 1;
        }
        return right != 0 ? right : -1;
    }
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) 
    {
        // https://leetcode.cn/problems/maximum-points-inside-the-square/description/
        // 还可以使用最朴素的切比雪夫距离来做
        auto check = [&](long mid) -> tuple<bool, int>       // 使用 tuple
            {
                int record[26] = {};
                int sum = 0;
                for (size_t i = 0; i < points.size(); ++i) 
                {
                    bool inCircle = true;
                    for (int x : points[i])
                        if (std::abs(x) * 2 > mid) 
                        { 
                            inCircle = false; 
                            break; 
                        }
                    if (!inCircle) 
                        continue;
                    record[s[i] - 'a']++;
                    sum++;
                    if (record[s[i] - 'a'] >= 2) 
                        return { false, sum };          // 注意这里就算是false也要返回sum
                }
                return { true, sum };
            };
        long left = -1;
        long right = INT_MAX;
        while (left <= right)
        {
            long mid = left + (right - left) / 2;

            tuple<bool, int> c = check(mid);

            if (get<0>(c))
                left = mid + 1;
            else
                right = mid - 1;
        }
        return get<1>(check(right));
    }
    int splitArray(vector<int>& nums, int k) 
    {
        // https://leetcode.cn/problems/split-array-largest-sum/description/

    }
    int minimizedMaximum(int n, vector<int>& quantities) 
    {
        // https://leetcode.cn/problems/minimized-maximum-of-products-distributed-to-any-store/description/
        // 最小化最大值的模板
        auto check = [&](int mid)
            {
                int record = 0;
                for (auto i : quantities)
                {
                    record += (i + mid - 1) / mid;
                    if (record > n)
                        return false;
                }
                return true;
            };
        int left = 1;
        int right = *max_element(quantities.begin(), quantities.end());
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
    int minCost(int n, vector<vector<int>>& edges, int k) 
    {
        // https://leetcode.cn/problems/minimize-maximum-component-cost/description/
        /*auto countComponent = [&]()
            {
                int n = edges.size() + 1;
                vector<vector<int>> adj(n);
                for (auto& e : edges)
                {
                    adj[e[0]].push_back(e[1]);
                    adj[e[1]].push_back(e[0]);
                }
            };
        auto check = [&](int mid) -> bool
            {
                
            };
        sort(edges.begin(), edges.end(), [](const auto& a, const auto& b)
            {
                return a[2] < b[2];
            });
        int left = 0;
        int right = edges.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (check(mid))
                right = mid - 1;
            else
                left = mid + 1;
        }
        return edges[left][2];*/
    }
    int minimumSize(vector<int>& nums, int maxOperations) 
    {
        // https://leetcode.cn/problems/minimum-limit-of-balls-in-a-bag/description/
        auto check = [&](int mid) -> bool
            {
                int count = 0;
                for (auto num : nums)
                {
                    if (num > mid)
                    {
                        count += (num - 1) / mid;           // 对于 num 要切分多少次才能使得 每一堆都小于等于 mid呢  
                        if (count > maxOperations)
                            return false;
                    }
                }
                return true;
            };
        
        int left = 1;
        int right = *max_element(nums.begin(), nums.end());
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
};