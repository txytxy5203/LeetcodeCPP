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
#include <unordered_map>
#include <map>
#include <set>
#include <stack>
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
        // 这题后续还得再看看
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
    int maxPossibleScore(vector<int>& start, int d) 
    {
        // https://leetcode.cn/problems/maximize-score-of-numbers-in-ranges/description/
        // 这题还是没有看懂
        sort(start.begin(), start.end());      
        auto check = [&](int score)
            {
                // 给定mid 使得任意两个数之差不小于mid
                long long x = LLONG_MIN;
                for (int s : start) {
                    x = max(x + score, (long long)s); // x 必须 >= 区间左端点 s
                    if (x > s + d) {
                        return false;
                    }
                }
                return true;
            };
        int left = 0;
        int right = INT_MAX;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (check(mid))
                left = mid + 1;
            else
                right = mid - 1;
        }
        return right;
    }
    int kthSmallest(vector<vector<int>>& matrix, int k) 
    {
        // https://leetcode.cn/problems/kth-smallest-element-in-a-sorted-matrix/description/
        int n = matrix.size();
        auto check = [&](int mid) -> bool
            {
                int count = 0;
                int i = 0;
                int j = n - 1;
                while (i < n && j >= 0 && count < k)            // 这里一定要利用好矩阵是有一定顺序的 这个信息
                {
                    if (matrix[i][j] > mid)
                    {
                        j--;
                    }
                    else
                    {
                        count += j + 1;
                        i++;
                    }
                }
                return count >= k;

            };
        int left = matrix[0][0];
        int right = matrix[n - 1][n - 1];
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
    int findKthNumber(int m, int n, int k) 
    {
        // https://leetcode.cn/problems/kth-smallest-number-in-multiplication-table/description/
        
        #pragma region 没有优化的
        //auto check = [&](int mid) -> bool
                //    {
                //        int count = 0;
                //        int i = 0;
                //        int j = n - 1;
                //        while (i < m && j >= 0 && count < k)            // 这里一定要利用好矩阵是有一定顺序的 这个信息
                //        {
                //            if ((i + 1) * (j + 1) > mid)
                //            {
                //                j--;
                //            }
                //            else
                //            {
                //                count += j + 1;
                //                i++;
                //            }
                //        }
                //        return count >= k;

                //    };
        #pragma endregion
#pragma region 优化
        auto check = [&](int mid) -> bool 
            {
                // 因为第 i 行都是i 的倍数       
                // 一定要利用好题目的所有信息 
                // 都是关键
                int count = 0;
                for (int i = 1; i <= m; i++)    
                {
                    count += min(mid / i, n);   
                }
                return count >= k;
            };
#pragma endregion

        
        int left = 1;
        int right = n * m;
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
    int smallestDistancePair(vector<int>& nums, int k) 
    {
        // https://leetcode.cn/problems/find-k-th-smallest-pair-distance/description/
        // 居然一次就过了 happy
        auto check = [&](int mid)
            {
                // 距离的绝对值小于等于mid的  有k个就行了
                int count = 0;
                int left = 0;
                // 双指针  不定长的滑动窗口
                for (int i = 1; i < nums.size(); i++)
                {
                    // in
                    
                    // out
                    while (abs(nums[i] - nums[left]) > mid && left < i)
                    {
                        left++;
                    }

                    // update
                    if (abs(nums[i] - nums[left]) <= mid)       
                        count += i - left;                      // 这里的update一定要注意
                    if (count >= k)
                        return true;
                }
                return false;
            };

        sort(nums.begin(), nums.end());
        int left = 0;
        int right = nums[nums.size() - 1] - nums[0];
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
    int nthMagicalNumber(int n, int a, int b) 
    {
        // https://leetcode.cn/problems/nth-magical-number/description/
        // 这题也要再看看
        long long lcm = std::lcm(a, b);
        auto check = [&](long long mid) -> bool
            {
                long long countA = mid / a;
                long long countB = mid / b;
                long long countRepeat = mid / lcm;
                return (countA + countB - countRepeat) >= n;
            };
        long long left = 0;
        long long right = max(a, b) * 1LL * n;
        
        while (left <= right)
        {
            long long mid = left + (right - left) / 2;
            if (check(mid))
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left % 1'000'000'007;
    }
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        // https://leetcode.cn/problems/two-sum/description/
        // 枚举右  维护左      双变量问题
        unordered_map<int, int> dict;
        for (int i = 0; i < nums.size(); i++)
        {
            if (dict.find(target - nums[i]) != dict.end()) 
            {
                return { dict[target - nums[i]], i };
            }
            dict[nums[i]] = i;
        }     
    }
    int findMaxK(vector<int>& nums) 
    {
        // https://leetcode.cn/problems/largest-positive-integer-that-exists-with-its-negative/description/
        unordered_set<int> set;
        int ans = -1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (set.find(-nums[i]) != set.end())
            {
                ans = max(ans, abs(nums[i]));
            }
            set.insert(nums[i]);
        }
        return ans;
    }
    int numIdenticalPairs(vector<int>& nums) 
    {
        // https://leetcode.cn/problems/number-of-good-pairs/description/
        unordered_map<int, int> dict;
        int ans = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (dict.find(nums[i]) != dict.end())
            {
                ans += dict[nums[i]];
                dict[nums[i]]++;
                continue;
            }
            dict[nums[i]] = 1;
        }
        return ans;
    }
    long long interchangeableRectangles(vector<vector<int>>& rectangles) 
    {
        // https://leetcode.cn/problems/number-of-pairs-of-interchangeable-rectangles/description/
        map<pair<int, int>, long> dict;        
        // 这个map是红黑树 如果使用unordered_map 会显示tuple不是可哈希的类型
        long long ans = 0;
        for (int i = 0; i < rectangles.size(); i++)
        {
            int width = rectangles[i][0];
            int height = rectangles[i][1];
            int g = gcd(width, height);
            pair<int, int> rate = { width / g, height / g };
            if (dict.find(rate) != dict.end())
            {
                ans += dict[rate];
                dict[rate]++;
                continue;
            }
            dict[rate] = 1;
        }
        return ans;
    }
    int numPairsDivisibleBy60(vector<int>& time) 
    {
        // https://leetcode.cn/problems/pairs-of-songs-with-total-durations-divisible-by-60/description/
        // 模板
        unordered_map<int, int> cnt;   // 余数出现次数
        long long ans = 0;
        for (int t : time) {
            int r = t % 60;
            int need = (r == 0) ? 0 : 60 - r;
            ans += cnt[need];          // 先查旧计数
            cnt[r]++;                  // 再存新余数
        }
        return ans;
    }
    long long countCompleteDayPairs(vector<int>& hours) 
    {
        // https://leetcode.cn/problems/count-pairs-that-form-a-complete-day-ii/description/
        map<int, long> dict;
        long long ans = 0;
        for (int i = 0; i < hours.size(); i++)
        {
            int r = hours[i] % 24;
            int need = (r == 0) ? 0 : 24 - r;
            ans += dict[need];
            dict[r]++;
        }
        return ans;
    }
    int countBeautifulPairs(vector<int>& nums) 
    {
        // https://leetcode.cn/problems/number-of-beautiful-pairs/description/
        map<int, int> dict;
        int ans = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            int curr = nums[i] % 10;
            for (int j = 1; j < 10; j++)
            {
                if (gcd(j, curr) == 1)
                    ans += dict[j];
            }
            while (nums[i] >= 10)       // TODO 取第一个数字就这么取
            {
                nums[i] /= 10;
            }
            dict[nums[i]]++;
        }
        return ans;
    }
    int minimumSum(vector<int>& nums) 
    {
        // https://leetcode.cn/problems/minimum-sum-of-mountain-triplets-ii/description/
        // 经典的来啦 在一个不断减少的集合中一直能够得到最小值
        // 后缀最小值
        int ans = INT_MAX;
        int minValue = nums[0];
        int n = nums.size();

        // 先计算后缀最小值
        vector<int> suf(n);
        suf[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            suf[i] = min(nums[i], suf[i + 1]);
        }

        for (int i = 1; i < n - 1; i++)
        {
            if (minValue < nums[i] && suf[i + 1] < nums[i])
                ans = min(ans, minValue + nums[i] + suf[i + 1]);
            minValue = min(minValue, nums[i]);
        }
        return ans != INT_MAX ? ans : -1;
    }
    int specialTriplets(vector<int>& nums)
    {
        // https://leetcode.cn/problems/count-special-triplets/description/
        int ans = 0;
        int n = nums.size();
        vector<int> suf(n);
        map<int, int> dict;
        for (int i = n - 1; i >= 0; i--)
        {
            suf[i] += dict[2 * nums[i]];            // CPP中不存在的key会默认添加一个 value为类型的默认值
            dict[nums[i]]++;
        }
        dict.clear();

        for (int i = 0; i < n; i++)
        {
            ans += (dict[2 * nums[i]] * suf[i]) % 1'000'000'007;

            dict[nums[i]]++;
        }
        return ans ;
    }
    int countPalindromicSubsequence(string s) 
    {
        // https://leetcode.cn/problems/unique-length-3-palindromic-subsequences/description/
        int front[26] = {};
        int behind[26] = {};
        int n = s.size();
        int ans = 0;
        set<pair<char, char>> set;
        front[s[0] - 'a']++;
        for (int i = n - 1; i >= 2; i--)
        {
            behind[s[i] - 'a']++;
        }
        for (int i = 1; i < n - 1; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                int num = min(front[j], behind[j]);
                if (num != 0 && set.find({ s[i], char('a' + j) }) == set.end())
                {
                    ans += 1;
                    set.insert({ s[i], char('a' + j) });
                }
            }
            
            front[s[i] - 'a']++;
            behind[s[i + 1] - 'a']--;
        }
        return ans;
    }
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) 
    {
        // https://leetcode.cn/problems/sort-matrix-by-diagonals/description/
        // 遍历矩阵的对角线
        int m = grid.size();
        int n = grid[0].size();

        for (int k = 1; k < m + n; k++)     // k = i - j + n
        {
			vector<int> diagonal;
			for (int i = 0; i < m; i++)
			{
				int j = i - k + n;
				if (j >= 0 && j < n)        // 相比于灵神的写法 我觉得这个写法更清晰一些
				{
					diagonal.push_back(grid[i][j]);
				}
			}
            if (k < n)
                sort(diagonal.begin(), diagonal.end());
            else
                sort(diagonal.begin(), diagonal.end(), greater<int>());
			int index = 0;
			for (int i = 0; i < m; i++)
			{
				int j = i - k + n;
				if (j >= 0 && j < n)
				{
					grid[i][j] = diagonal[index++];
				}
			}
        }
        return grid;
    }
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) 
    {
        // https://leetcode.cn/problems/difference-of-number-of-distinct-values-on-diagonals/description/
		int m = grid.size();
		int n = grid[0].size();
        for (int k = 1; k < m + n; k++)
        {
            // 对角线遍历
            int record[51] = {};        // grid中最大的数字就是50 所以开51即可
			int front[51] = {};
            // 前缀和
            for (int i = 0; i < m; i++)
            {
                int j = i - k + n;
                if (j >= 0 && j < n)
                {
                    record[grid[i][j]]++;
                }
            }

            for (int i = 0; i < m; i++)
            {
                int j = i - k + n;
                if (j >= 0 && j < n)
                {
					record[grid[i][j]]--;
					int frontCount = 0;
					int behindCount = 0;
					for (int num = 0; num < 51; num++)
					{
						if (front[num] > 0)
							frontCount++;
						if (record[num] > 0)
							behindCount++;
					}
                    int temp = grid[i][j];
					grid[i][j] = abs(frontCount - behindCount);
					front[temp]++;
                }
            }
        }
        return grid;
    }
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) 
    {
        // https://leetcode.cn/problems/sort-the-matrix-diagonally/description/
        int m = mat.size();
        int n = mat[0].size();
        for (int k = 1; k < m + n; k++)
        {
            // 对角线遍历
            vector<int> nums;
            for (int i = 0; i < m; i++)
            {
                int j = i - k + n;
                if (j >= 0 && j < n)
                {
					nums.push_back(mat[i][j]);
                }
            }
			sort(nums.begin(), nums.end());
			int index = 0;              // 直接使用 index 来记录排序后的位置 不就行了吗  怎么这么捞？
            for (int i = 0; i < m; i++)
            {
                int j = i - k + n;
                if (j >= 0 && j < n)
                {
                    mat[i][j] = nums[index++];
                }
            }
        }
        return mat;
    }
    vector<string> buildArray(vector<int>& target, int n) 
    {
        // https://leetcode.cn/problems/build-an-array-with-stack-operations/description/
		vector<string> ans;
        // 脑子机灵一点
        int index = 1;
        for (int i : target)
        {
            while (index < i)
            {
                ans.push_back("Push");
                ans.push_back("Pop");
                index++;
            }
			ans.push_back("Push");
            index++;
        }
        return ans;
    }
    int calPoints(vector<string>& operations) 
    {
        // https://leetcode.cn/problems/baseball-game/description/
		vector<int> record;
        for (auto s : operations)
        {
            if (s == "D")
            {
                record.push_back(record.back() * 2);
            }
            else if (s == "C")
            {
                record.erase(record.end());
            }
            else if (s == "+")
            {
                record.push_back(*(record.end() - 1) + *(record.end() - 2));
            }
            else
            {
                record.push_back(stoi(s));  // string to int
            }
        }
        return accumulate( record.begin(), record.end(), 0);
    }
    string clearStars(string s) 
    {
        // https://leetcode.cn/problems/lexicographically-minimum-string-after-removing-stars/description/
        // 这么简单的想法为什么就想不到呢？  多想想 没那么难
        stack<int> stacks[26];
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '*')
            {
				for (auto& st : stacks)
				{
                    if (!st.empty())
                    {
                        s[st.top()] = '*';
                        st.pop();
						break;
                    }
				}
            }
            else
            {
				stacks[s[i] - 'a'].push(i);
            }
        }
        s.erase(remove(s.begin(), s.end(), '*'), s.end());
        return s;
    }
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        // https://leetcode.cn/problems/exclusive-time-of-functions/description/
		vector<int> ans(n, 0);
		stack<pair<int, int>> stk;      // 函数id  开始时间
		for (auto& log : logs)          // 直接是引用
		{
			int pos1 = log.find_first_of(':');
			int pos2 = log.find_last_of(':');
			int id = stoi(log.substr(0, pos1));
			string type = log.substr(pos1 + 1, pos2 - pos1 - 1);
			int time = stoi(log.substr(pos2 + 1));
			if (type == "start")
			{
				if (!stk.empty())
				{
					ans[stk.top().first] += time - stk.top().second;
				}
				stk.push({ id, time });
			}
			else
			{
				auto [funcId, startTime] = stk.top();
				stk.pop();
				ans[funcId] += time - startTime + 1;
				if (!stk.empty())
				{
					stk.top().second = time + 1;
				}
			}
		}
		return ans;		
    }
    int minLength(string s) 
    {
        // https://leetcode.cn/problems/minimum-string-length-after-removing-substrings/description/
		stack<char> stk;
        for (auto ch : s)
        {
            char top = stk.empty() ? ' ' : stk.top();
            if (ch == 'B' && top == 'A')
            {
                stk.pop();
                continue;
            }
            else if (ch == 'D' && top == 'C')
            {
                stk.pop();
                continue;
            }
            stk.push(ch);
        }
        return stk.size();
    }
    string removeDuplicates(string s) 
    {
        // https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/description/
        // 优雅 太优雅了   cpp所有的数据结构都有一些相似 要利用好这些特性
        string ans;
        for (auto ch : s)
        {
            if (!ans.empty() && ans.back() == ch)
                ans.pop_back();
            else
                ans.push_back(ch);
        }
        return ans;
    }
    string makeGood(string s) 
    {
        // https://leetcode.cn/problems/make-the-string-great/description/
        string ans;
        for (auto ch : s)
        {
            if (!ans.empty() && (ans.back() == ch + 32 || ans.back() == ch - 32))
                ans.pop_back();
            else
                ans.push_back(ch);
        }
        return ans;
    }
    bool isValid(string s) 
    {
        // https://leetcode.cn/problems/valid-parentheses/description/
        unordered_map<char, char> map;
        map.insert({ ')','(' });
        map.insert({ '}','{' });
        map.insert({ ']','[' });
        stack<char> stk;
        for (auto ch : s)
        {
            if (!stk.empty() && stk.top() == map[ch])
            {
                stk.pop();
                continue;
            }                
            stk.push(ch);
        }
        return stk.empty();
    }
    int minAddToMakeValid(string s) 
    {
        // https://leetcode.cn/problems/minimum-add-to-make-parentheses-valid/description/
        stack<char> stk;
        for (auto ch : s)
        {
            if (!stk.empty() && stk.top() == '(' && ch == ')')
                stk.pop();
            else
                stk.push(ch);
        }
        return stk.size();
    }
    string removeOuterParentheses(string s) 
    {
        // https://leetcode.cn/problems/remove-outermost-parentheses/description/
        string ans;
        stack<char> stk;
        for (auto ch : s)
        {
            if (stk.empty())
            {
                stk.push(ch);
            }
            else
            {         
                if (ch == ')')
                {
                    if(stk.size() != 1)
                        ans.push_back(ch);
                    stk.pop();
                }
                else
                {
                    ans.push_back(ch);
                    stk.push(ch);
                }
            }
        }
        return ans;
    }
    string removeOuterParentheses2(string s)
    {
        // ai优化版本
        string ans;
        ans.reserve(s.size());          // 预分配，减少重分配
        int depth = 0;                  // 当前括号深度
        for (char ch : s) {
            if (ch == '(') {
                if (depth++ > 0) ans.push_back(ch); // 非外层
            }
            else { // ch == ')'
                if (--depth > 0) ans.push_back(ch); // 非外层
            }
        }
        return ans;
    }
    int maxDepth(string s) 
    {
        // https://leetcode.cn/problems/maximum-nesting-depth-of-the-parentheses/description/
        int ans = 0;
        stack<char> stk;
        for (auto ch : s)
        {
            if (ch == '(')
                stk.push(ch);
            else if (ch == ')')
            {
                ans = max(ans, (int)stk.size());
                stk.pop();
            }
        }
        return ans;
    }
    int maxDepth2(string s)
    {
        // https://leetcode.cn/problems/maximum-nesting-depth-of-the-parentheses/description/
        // 思想上的 栈 也可以  而且更好
        int ans = 0;
        int curr = 0;
        for (auto ch : s)
        {
            if (ch == '(')
                curr++;
            else if (ch == ')')
            {
                ans = max(ans, curr);
                curr--;
            }
        }
        return ans;
    }
    int clumsy(int n) 
    {
        // https://leetcode.cn/problems/clumsy-factorial/description/
        // 对于所有表达式类问题都可以使用下面的框架
        // 双栈法
        // https://leetcode.cn/problems/clumsy-factorial/solutions/693194/gong-shui-san-xie-tong-yong-biao-da-shi-nngfp/
        // 还可以使用打表法 简单无脑
        
        stack<int> nums;
        stack<char> ops;
        map<char, int> dict = {
            {'*', 2},
            {'/', 2},
            {'+', 1},
            {'-', 1}
        };
        char cs[4] = {'*','/','+','-'};

        auto calc = [&]()
            {
                int b = nums.top();
                nums.pop();
                int a = nums.top();
                nums.pop();
                char op = ops.top();
                ops.pop();

                int ans = 0;
                if (op == '*')
                    ans = a * b;
                else if (op == '-')
                    ans = a - b;
                else if (op == '/')
                    ans = a / b;
                else if (op == '+')
                    ans = a + b;
                nums.push(ans);
            };

        for (int i = n, j = 0; i >= 1; i--, j++)
        {
            char op = cs[j % 4];
            nums.push(i);
            while (!ops.empty() && dict[ops.top()] >= dict[op])
            {
                calc();
            }
            if (i != 1)
                ops.push(op);
        }

        while (!ops.empty())
        {
            calc();
        }
        return nums.top();    
    }
    int calculate(string s) 
    {
        // https://leetcode.cn/problems/basic-calculator/description/
        stack<int> nums;
        stack<char> ops;
        unordered_map<char, int> prio{ {'*',2},{'/',2},{'+',1},{'-',1} }; // 0级：括号
        auto calc = [&]() {
            int b = nums.top(); nums.pop();
            int a = nums.top(); nums.pop();
            char op = ops.top(); ops.pop();
            switch (op) {
            case '+': nums.push(a + b); break;
            case '-': nums.push(a - b); break;
            case '*': nums.push(a * b); break;
            case '/': nums.push(a / b); break;
            }
            };

        int i = 0, n = s.size();
        while (i < n) {
            char c = s[i];
            if (c == ' ') { ++i; continue; }
            if (c == '(') { ops.push(c); ++i; continue; }
            if (c == ')') {
                while (ops.top() != '(') calc();
                ops.pop(); // 弹出 '('
                ++i;
                continue;
            }
            if (isdigit(c)) {
                int num = 0;
                while (i < n && isdigit(s[i])) 
                    num = num * 10 + (s[i++] - '0');
                nums.push(num);
                continue;
            }
            // 运算符
            while (!ops.empty() 
                && ops.top() != '(' 
                && prio[ops.top()] >= prio[c]) 
                calc();
            ops.push(c);
            ++i;
        }
        while (!ops.empty()) calc();
        return nums.top();
    }
    vector<int> dailyTemperatures(vector<int>& temperatures) 
    {
        // https://leetcode.cn/problems/daily-temperatures/description/
        // 单调栈   忘记了别怕 想想就想起来了
        // 栈内的数据是有序的！！！
        // 我这个是从左到右的顺序 也可以从右到左
        stack<int> stk;
        int n = temperatures.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++)
        {
            while (!stk.empty() && temperatures[stk.top()] < temperatures[i])
            {
                int index = stk.top();
                stk.pop();
                ans[index] = i - index;         // 直接在这里完成
            }
            stk.push(i);
        }

        while (!stk.empty())
        {
            int index = stk.top();
            stk.pop();
            ans[index] = 0;
        }
        return ans;
    }
    vector<int> finalPrices(vector<int>& prices) 
    {
        // https://leetcode.cn/problems/final-prices-with-a-special-discount-in-a-shop/description/
        int n = prices.size();
        stack<int> stk;
        vector<int> ans(n);
        for (int i = 0; i < n; i++)
        {
            while (!stk.empty() && prices[stk.top()] >= prices[i])
            {
                int index = stk.top();
                stk.pop();
                ans[index] = prices[index] - prices[i];
            }
            stk.push(i);
        }
        while (!stk.empty())
        {
            int index = stk.top();
            stk.pop();
            ans[index] = prices[index];
        }
        return ans;
    }
    vector<int> nextGreaterElements(vector<int>& nums) 
    {
        // https://leetcode.cn/problems/next-greater-element-ii/description/
        int n = nums.size();
        vector<int> ans(n, -1);
        nums.insert(nums.end(), nums.begin(), nums.end());
        stack<int> stk;
        // 从前到后
        for (int i = 0; i < n * 2; i++)
        {
            while (!stk.empty() && nums[stk.top()] < nums[i])
            {
                int index = stk.top();
                stk.pop();
                ans[index % n] = nums[i % n];
            }
            if(i < n)
                stk.push(i);
        }
        
        return ans;
    }
    int maxChunksToSorted(vector<int>& arr) {
        // https://leetcode.cn/problems/max-chunks-to-make-sorted-ii/description/
        // 核心的逻辑就是要保证chunk的最大值是有序的
        stack<int> stk;   // 存当前 chunk 的最大值
        for (int x : arr) {
            int curMax = x;                    // 新元素可能成新最大值
            while (!stk.empty() && stk.top() > x) {
                curMax = std::max(curMax, stk.top()); // 合并 chunk，保留最大值
                stk.pop();
            }
            stk.push(curMax);                  // 压回合并后的最大值
        }
        return stk.size();                     // 每个栈元素 = 一个 chunk
    }
    int maxWidthRamp(vector<int>& nums) {
        // https://leetcode.cn/problems/maximum-width-ramp/description/
         
        vector<int> stk;
        stk.push_back(0);
        int n = nums.size();
        for (size_t i = 1; i < n; i++)
        {
            if (nums[i] < nums[stk.back()])
                stk.push_back(i);
        }
        int ans = 0;
        for (int i = n - 1; i >= 0; i--)        // 这里的处理太妙了
        {
            while (!stk.empty() && nums[i] >= nums[stk.back()])     // 一定是区间越大越好
            {
                int index = stk.back();
                stk.pop_back();
                ans = max(ans, i - index);
            }
        }
        return ans;
    }
    int trap(vector<int>& height) {
        // https://leetcode.cn/problems/trapping-rain-water/description/
        stack<int> stk;
        map<int, int> right;
        map<int, int> left;
        int n = height.size();
        int ans = 0;
        // right
        for (int i = 0; i < n; i++)
        {
            while (!stk.empty() && height[stk.top()] < height[i]) {
                int top = stk.top();
                right[top] = i;
                stk.pop();
            }
            stk.push(i);
        }
        while (!stk.empty()) {
            right[stk.top()] = -1;
            stk.pop();
        }
        // left
        for (int i = n - 1; i >= 0; i--)
        {
            while (!stk.empty() && height[stk.top()] < height[i]) {
                int top = stk.top();
                left[top] = i;
                stk.pop();
            }
            stk.push(i);
        }
        while (!stk.empty()) {
            left[stk.top()] = -1;
            stk.pop();
        }

        for (int i = 0; i < n;)
        {
            if (left[i] != -1 && right[i] != -1) {
                int left_index = left[i];
                int right_index = right[i];
                int level = min(height[left_index], height[right_index]);
                
                for (int j = left_index + 1; j < right_index; j++)
                {
                    ans += level - height[j];
                }
                i = right_index + 1;
            }
            else
            {
                i++;
            }
        }
        return ans;
    }
    vector<int> twoSum2(vector<int>& numbers, int target) {
        // https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/
        int left = 0;
        int right = numbers.size() - 1;
        while (left < right)
        {
            int add = numbers[left] + numbers[right];
            if (add > target)
            {
                right--;
            }
            else if (add < target)
            {
                left++;
            }
            else
            {
                return {left + 1, right + 1};
            }
        }
        return { 0,0 };
    }
    vector<vector<int>> threeSum(vector<int>& nums) {
        // https://leetcode.cn/problems/3sum/description/
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int n = nums.size();

        for (int i = 0; i < n - 2; i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int target = -nums[i];
            int left = i + 1;
            int right = n - 1;
            while (left < right)
            {
                int add = nums[left] + nums[right];
                if (add == target)
                {
                    ans.push_back({ nums[i], nums[left], nums[right] });
                    int left_jump = left;
                    int right_jump = right;
                    while (left_jump < n && nums[left] == nums[left_jump])
                    {
                        left_jump++;
                    }
                    while (right_jump >= 0 && nums[right] == nums[right_jump])
                    {
                        right_jump--;
                    }
                    left = left_jump;
                    right = right_jump;
                }
                else if (add > target)
                    right--;
                else
                    left++;
            }
        }
        return ans;
    }
};