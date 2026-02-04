// 1
// class Solution {
//    public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         unordered_map<int, int> numMap;
//         for (int i = 0; i < nums.size(); ++i) {
//             int res = target - nums[i];
//             if (numMap.find(res) != numMap.end()) {
//                 return {numMap[res], i};
//             }
//             numMap[nums[i]] = i;
//         }
//         return {};
//     }
// };
// 2 class Solution {
//    public:
//     bool isAnagram(string s, string t) {
//         if (s.size() != t.size()) {
//             return false;
//         }
//         unordered_map<char, int> charhash;
//         for (char c : s) {
//             charhash[c]++;
//         }
//         for (char c : t) {
//             charhash[c]--;
//             if (charhash[c] < 0) {
//                 return false;
//             }
//         }
//         return true;
//     }
// };
// 3
//     /**
//      * Definition for singly-linked list.
//      * struct ListNode {
//      *     int val;
//      *     ListNode *next;
//      *     ListNode(int x) : val(x), next(NULL) {}
//      * };
//      */
//     class Solution {
//    public:
//     ListNode* detectCycle(ListNode* head) {
//         ListNode* fast = head;
//         ListNode* slow = head;
//         while (fast != NULL && fast->next != NULL) {
//             slow = slow->next;
//             fast = fast->next->next;
//             if (fast == slow) {
//                 ListNode* temp1 = fast;
//                 ListNode* temp2 = head;
//                 while (temp1 != temp2) {
//                     temp1 = temp1->next;
//                     temp2 = temp2->next;
//                 }
//                 return temp1;
//             }
//         }
//         return NULL;
//     }
// };
// 4
//     /**
//      * Definition for singly-linked list.
//      * struct ListNode {
//      *     int val;
//      *     ListNode *next;
//      *     ListNode(int x) : val(x), next(NULL) {}
//      * };
//      */
//     class Solution {
//    public:
//     ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
//         ListNode* curA = headA;
//         ListNode* curB = headB;
//         int lenA = 0;
//         int lenB = 0;
//         while (curA != NULL) {
//             lenA++;
//             curA = curA->next;
//         }
//         while (curB != NULL) {
//             lenB++;
//             curB = curB->next;
//         }
//         curA = headA;
//         curB = headB;
//         if (lenB > lenA) {
//             swap(lenA, lenB);
//             swap(curA, curB);
//         }
//         int num = lenA - lenB;
//         while (num--) {
//             curA = curA->next;
//         }
//         while (curA != NULL) {
//             if (curA == curB) {
//                 return curA;
//             }
//             curA = curA->next;
//             curB = curB->next;
//         }
//         return NULL;
//     }
// };
// 5
//     /**
//      * Definition for singly-linked list.
//      * struct ListNode {
//      *     int val;
//      *     ListNode *next;
//      *     ListNode() : val(0), next(nullptr) {}
//      *     ListNode(int x) : val(x), next(nullptr) {}
//      *     ListNode(int x, ListNode *next) : val(x), next(next) {}
//      * };
//      */
//     class Solution {
//    public:
//     int size(ListNode* head) {
//         ListNode* cur = head;
//         int count = 0;
//         while (cur != nullptr) {
//             cur = cur->next;
//             count++;
//         }
//         return count;
//     }
//     ListNode* removeNthFromEnd(ListNode* head, int n) {
//         ListNode* dummynode = new ListNode();
//         dummynode->next = head;
//         int a = size(head);
//         int num = a - n;
//         ListNode* cur = dummynode;
//         while (num--) {
//             cur = cur->next;
//         }
//         ListNode* delNode = cur->next;
//         cur->next = delNode->next;
//         delete delNode;
//         ListNode* res = dummynode->next;
//         delete dummynode;
//         return res;
//     }
// };
// 6
//     /**
//      * Definition for singly-linked list.
//      * struct ListNode {
//      *     int val;
//      *     ListNode *next;
//      *     ListNode() : val(0), next(nullptr) {}
//      *     ListNode(int x) : val(x), next(nullptr) {}
//      *     ListNode(int x, ListNode *next) : val(x), next(next) {}
//      * };
//      */
//     class Solution {
//    public:
//     ListNode* swapPairs(ListNode* head) {
//         ListNode* dummynode = new ListNode();
//         dummynode->next = head;
//         ListNode* cur = dummynode;
//         while (cur->next != nullptr && cur->next->next != nullptr) {
//             ListNode* temp1 = cur->next;
//             ListNode* temp2 = cur->next->next->next;
//             cur->next = cur->next->next;
//             cur->next->next = temp1;
//             cur->next->next->next = temp2;
//             cur = cur->next->next;
//         }
//         ListNode* result = dummynode->next;
//         delete dummynode;
//         return result;
//     }
// };
// 7 class MyLinkedList {
//    private:
//     struct LinkedNode {
//         int val;
//         LinkedNode* next;
//         LinkedNode(int val) : val(val), next(nullptr) {}
//     };
//     int _size;
//     LinkedNode* _dummyHead;

//    public:
//     MyLinkedList() {
//         _dummyHead = new LinkedNode(0);
//         _size = 0;
//     }
//     int get(int index) {
//         if (index > (_size - 1) || index < 0) {
//             return -1;
//         }
//         LinkedNode* cur = _dummyHead->next;
//         while (index--) {
//             cur = cur->next;
//         }
//         return cur->val;
//     }
//     void addAtHead(int val) {
//         LinkedNode* newNode = new LinkedNode(val);
//         newNode->next = _dummyHead->next;
//         _dummyHead->next = newNode;
//         _size++;
//     }
//     void addAtTail(int val) {
//         LinkedNode* newNode = new LinkedNode(val);
//         LinkedNode* cur = _dummyHead;
//         while (cur->next != nullptr) {
//             cur = cur->next;
//         }
//         cur->next = newNode;
//         _size++;
//     }
//     void addAtIndex(int index, int val) {
//         if (index > _size)
//             return;
//         if (index < 0)
//             index = 0;
//         LinkedNode* newNode = new LinkedNode(val);
//         LinkedNode* cur = _dummyHead;
//         while (index--) {
//             cur = cur->next;
//         }
//         newNode->next = cur->next;
//         cur->next = newNode;
//         _size++;
//     }
//     void deleteAtIndex(int index) {
//         if (index >= _size || index < 0) {
//             return;
//         }
//         LinkedNode* cur = _dummyHead;
//         while (index--) {
//             cur = cur->next;
//         }
//         LinkedNode* tmp = cur->next;
//         cur->next = cur->next->next;
//         delete tmp;
//         tmp = nullptr;
//         _size--;
//     }
//     void printLinkedList() {
//         LinkedNode* cur = _dummyHead;
//         while (cur->next != nullptr) {
//             cout << cur->next->val << " ";
//             cur = cur->next;
//         }
//         cout << endl;
//     }
// };

// /**
//  * Your MyLinkedList object will be instantiated and called as such:
//  * MyLinkedList* obj = new MyLinkedList();
//  * int param_1 = obj->get(index);
//  * obj->addAtHead(val);
//  * obj->addAtTail(val);
//  * obj->addAtIndex(index,val);
//  * obj->deleteAtIndex(index);
//  */
// 8
//     /**
//      * Definition for singly-linked list.
//      * struct ListNode {
//      *     int val;
//      *     ListNode *next;
//      *     ListNode() : val(0), next(nullptr) {}
//      *     ListNode(int x) : val(x), next(nullptr) {}
//      *     ListNode(int x, ListNode *next) : val(x), next(next) {}
//      * };
//      */
//     class Solution {
//    public:
//     ListNode* removeElements(ListNode* head, int val) {
//         while (head != NULL && head->val == val) {
//             ListNode* tmp = head;
//             head = head->next;
//             delete tmp;
//         }
//         ListNode* cur = head;
//         ListNode* prev = nullptr;
//         while (cur != NULL) {
//             if (cur->val == val) {
//                 ListNode* temp = cur->next;
//                 prev->next = cur->next;
//                 delete cur;
//                 cur = temp;
//             } else {
//                 prev = cur;
//                 cur = cur->next;
//             }
//         }
//         return head;
//     }
// };
// 9 
// class Solution {
//    public:
//     int minSubArrayLen(int target, vector<int>& nums) {
//         int result = INT32_MAX;
//         int sum = 0;
//         int i = 0;
//         int length = 0;
//         for (int j = 0; j < nums.size(); j++) {
//             sum += nums[j];
//             while (sum >= target) {
//                 length = j - i + 1;
//                 result = result < length ? result : length;
//                 sum -= nums[i++];
//             }
//         }
//         return result == INT32_MAX ? 0 : result;
//     }
// };
// 10 class Solution {
//    public:
//     vector<int> sortedSquares(vector<int>& nums) {
//         int left = 0;
//         int right = nums.size() - 1;
//         int pos = nums.size() - 1;
//         int n = nums.size();
//         vector<int> res(n);
//         while (left <= right) {
//             int leftans = nums[left] * nums[left];
//             int rightans = nums[right] * nums[right];
//             if (leftans > rightans) {
//                 res[pos--] = leftans;
//                 left++;
//             } else {
//                 res[pos--] = rightans;
//                 right--;
//             }
//         }
//         return res;
//     }
// };
// 11 class Solution {
//    public:
//     bool backspaceCompare(string s, string t) {
//         string s1;
//         string t1;
//         for (char c : s) {
//             if (c != '#') {
//                 s1.push_back(c);
//             } else if (!s1.empty()) {
//                 s1.pop_back();
//             }
//         }
//         for (char c : t) {
//             if (c != '#') {
//                 t1.push_back(c);
//             } else if (!t1.empty()) {
//                 t1.pop_back();
//             }
//         }
//         return s1 == t1;
//     }
// };
// 12 class Solution {
//    public:
//     bool isPerfectSquare(int num) {
//         int ans = -1;
//         long left = 0;
//         long right = num;
//         while (left <= right) {
//             long middle = left + (right - left) / 2;
//             if (middle * middle < num) {
//                 left = middle + 1;
//             } else if (middle * middle > num) {
//                 right = middle - 1;
//             } else {
//                 return true;
//             }
//         }
//         return false;
//     }
// };
// 13 class Solution {
//    public:
//     int mySqrt(int x) {
//         if (x == 0 || x == 1) {
//             return x;
//         }
//         long left = 0;
//         long right = x;
//         int ans = 0;
//         while (left <= right) {
//             long middle = left + (right - left) / 2;
//             if (middle * middle <= x) {
//                 left = middle + 1;
//                 ans = middle;
//             } else {
//                 right = middle - 1;
//             }
//         }
//         return ans;
//     }
// };
// 14 class Solution {
//    public:
//     vector<int> searchRange(vector<int>& nums, int target) {
//         int leftborder = getleftborder(nums, target);
//         int rightborder = getrightborder(nums, target);
//         if (rightborder == -2 || leftborder == -2) {
//             return {-1, -1};
//         } else if ((rightborder - leftborder) > 1) {
//             return {leftborder + 1, rightborder - 1};
//         } else {
//             return {-1, -1};
//         }
//     }

//    private:
//     int getleftborder(vector<int>& nums, int target) {
//         int left = 0;
//         int right = nums.size() - 1;
//         int leftborder = -2;
//         while (left <= right) {
//             int middle = left + (right - left) / 2;
//             if (nums[middle] >= target) {
//                 right = middle - 1;
//                 leftborder = right;
//             } else {
//                 left = middle + 1;
//             }
//         }
//         return leftborder;
//     }
//     int getrightborder(vector<int>& nums, int target) {
//         int left = 0;
//         int right = nums.size() - 1;
//         int rightborder = -2;
//         while (left <= right) {
//             int middle = left + (right - left) / 2;
//             if (nums[middle] <= target) {
//                 left = middle + 1;
//                 rightborder = left;
//             } else {
//                 right = middle - 1;
//             }
//         }
//         return rightborder;
//     }
// };
// 15 class Solution {
//    public:
//     int searchInsert(vector<int>& nums, int target) {
//         int left = 0;
//         int right = nums.size() - 1;
//         while (left <= right) {
//             int middle = left + (right - left) / 2;
//             if (nums[middle] > target) {
//                 right = middle - 1;
//             } else if (nums[middle] < target) {
//                 left = middle + 1;
//             } else {
//                 return middle;
//             }
//         }
//         return left;
//     }
// };
// 16 class Solution {
//    public:
//     int search(vector<int>& nums, int target) {
//         int left = 0;
//         int right = nums.size() - 1;
//         while (left <= right) {
//             int middle = left + (right - left) / 2;
//             if (nums[middle] > target) {
//                 right = middle - 1;
//             } else if (nums[middle] < target) {
//                 left = middle + 1;
//             } else {
//                 return middle;
//             }
//         }
//         return -1;
//     }
// };
// 17 
// class Solution {
//    public:
//     bool canConstruct(string ransomNote, string magazine) {
//         if (ransomNote.size() > magazine.size()) {
//             return false;
//         }
//         string r = ransomNote;
//         string m = magazine;
//         unordered_map<char, int> hash;
//         for (char c : m) {
//             hash[c]++;
//         }
//         for (char c : r) {
//             hash[c]--;
//             if (hash[c] < 0) {
//                 return false;
//             }
//         }
//         return true;
//     }
// };
// 18 class Solution {
//    public:
//     vector<vector<string>> groupAnagrams(vector<string>& strs) {
//         vector<vector<string>> result;
//         unordered_map<string, vector<string>> hash;
//         for (string s : strs) {
//             string key = s;
//             sort(key.begin(), key.end());
//             hash[key].push_back(s);
//         }
//         for (auto pair : hash) {
//             result.push_back(pair.second);
//         }
//         return result;
//     }
// };
// 19 class Solution {
//    public:
//     vector<int> findAnagrams(string s, string p) {
//         int n = s.size();
//         int m = p.size();  // 关键：转换为有符号整数

//         if (m > n)
//             return {};  // 额外检查

//         array<int, 26> cnt_p{};
//         for (char c : p) {
//             cnt_p[c - 'a']++;
//         }

//         vector<int> ans;
//         array<int, 26> cnt_s{};

//         for (int i = 0; i < n; i++) {
//             cnt_s[s[i] - 'a']++;

//             // 当窗口长度达到p的长度时
//             if (i >= m - 1) {
//                 if (cnt_s == cnt_p) {
//                     ans.push_back(i - m + 1);
//                 }
//                 // 移除窗口最左边的字符
//                 cnt_s[s[i - m + 1] - 'a']--;
//             }
//         }
//         return ans;
//     }
// };
// 20 class Solution {
//    public:
//     vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
//         unordered_map<int, int> hash;
//         vector<int> result;
//         for (int c : nums1) {
//             hash[c]++;
//         }
//         for (int c : nums2) {
//             if (hash[c] > 0) {
//                 result.push_back(c);
//             }
//         }
//         sort(result.begin(), result.end());
//         auto last = unique(result.begin(), result.end());
//         result.erase(last, result.end());
//         return result;
//     }
// };
// 21 class Solution {
//    public:
//     vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
//         unordered_map<int, int> num_count;
//         for (int num : nums1) {
//             num_count[num]++;
//         }
//         vector<int> result;
//         for (int num : nums2) {
//             if (num_count.find(num) != num_count.end() && num_count[num] > 0) {
//                 result.push_back(num);
//                 num_count[num]--;
//             }
//         }
//         return result;
//     }
// };
// 22 class Solution {
//    public:
//     int getsum(int n) {
//         int sum = 0;
//         while (n) {
//             sum += (n % 10) * (n % 10);
//             n /= 10;
//         }
//         return sum;
//     }
//     bool isHappy(int n) {
//         unordered_map<int, int> hash;
//         while (1) {
//             int sum = getsum(n);
//             if (sum == 1) {
//                 return true;
//             }
//             if (hash.find(sum) != hash.end()) {
//                 return false;
//             } else {
//                 hash[sum]++;
//             }
//             n = sum;
//         }
//     }
// };
// 23 class Solution {
//    public:
//     int fourSumCount(vector<int>& nums1,
//                      vector<int>& nums2,
//                      vector<int>& nums3,
//                      vector<int>& nums4) {
//         unordered_map<int, int> hash;
//         int n = nums1.size();
//         int count = 0;
//         for (int i = 0; i < n; i++) {
//             for (int j = 0; j < n; j++) {
//                 int sum = nums1[i] + nums2[j];
//                 hash[sum]++;
//             }
//         }
//         for (int k = 0; k < n; k++) {
//             for (int l = 0; l < n; l++) {
//                 int sum = nums3[k] + nums4[l];
//                 int target = -sum;
//                 if (hash.find(target) != hash.end()) {
//                     count += hash[target];
//                 }
//             }
//         }
//         return count;
//     }
// };
// 24 class Solution {
//    public:
//     vector<vector<int>> threeSum(vector<int>& nums) {
//         unordered_map<int, int> hash;
//         vector<vector<int>> result;
//         int n = nums.size();
//         if (n < 3) {
//             return result;
//         }
//         sort(nums.begin(), nums.end());
//         for (int i = 0; i < n; i++) {
//             hash[nums[i]] = i;
//         }
//         for (int i = 0; i < n; ++i) {
//             if (i > 0 && nums[i] == nums[i - 1]) {
//                 continue;
//             }
//             for (int j = i + 1; j < n; ++j) {
//                 if (j > i + 1 && nums[j] == nums[j - 1]) {
//                     continue;
//                 }
//                 int target = -(nums[i] + nums[j]);
//                 if (hash.count(target) && hash[target] > j) {
//                     result.push_back({nums[i], nums[j], target});
//                 }
//             }
//         }
//         return result;
//     }
// };
// 25 class Solution {
//    public:
//     void reverseString(vector<char>& s) {
//         int n = s.size();
//         string r;
//         for (int i = n - 1; i >= 0; i--) {
//             r += s[i];
//         }
//         for (int i = 0; i < n; i++) {
//             s[i] = r[i];
//         }
//     }
// };
// 26 class Solution {
//    public:
//     string reverseStr(string s, int k) {
//         for (int i = 0; i < s.size(); i += (2 * k)) {
//             if (i + k <= s.size()) {
//                 reverse(s.begin() + i, s.begin() + i + k);
//             } else {
//                 reverse(s.begin() + i, s.end());
//             }
//         }
//         return s;
//     }
// };
// 27 class Solution {
//    public:
//     int strStr(string haystack, string needle) {
//         int idx = haystack.find(needle, 0);
//         if (idx == string::npos) {
//             idx = -1;
//         }
//         return idx;
//     }
// };
// 28 class Solution {
//    public:
//     bool repeatedSubstringPattern(string s) {
//         int n = s.size();
//         for (int len = 1; len <= n / 2; ++len) {
//             if (n % len != 0) {
//                 continue;
//             }
//             bool match = true;
//             for (int i = len; i < n; ++i) {
//                 if (s[i] != s[i - len]) {
//                     match = false;
//                 }
//             }
//             if (match) {
//                 return true;
//             }
//         }
//         return false;
//         ;
//     }
// };
// 29 class Solution {
//    public:
//     string reverseWords(string s) {
//         stringstream ss(s);
//         string word;
//         vector<string> words;
//         while (ss >> word) {
//             words.push_back(word);
//         }
//         reverse(words.begin(), words.end());
//         int n = words.size();
//         string result;
//         for (int i = 0; i < n; i++) {
//             if (i > 0) {
//                 result += " ";
//             }
//             result += words[i];
//         }
//         return result;
//     }
// };
// 30 class Solution {
//    public:
//     vector<vector<int>> fourSum(vector<int>& nums, int target) {
//         vector<vector<int>> result;
//         int n = nums.size();
//         if (n < 4) {
//             return result;
//         }
//         sort(nums.begin(), nums.end());
//         for (int i = 0; i < n - 3; ++i) {
//             if (i > 0 && nums[i] == nums[i - 1]) {
//                 continue;
//             }
//             for (int j = i + 1; j < n - 2; ++j) {
//                 if (j > i + 1 && nums[j] == nums[j - 1]) {
//                     continue;
//                 }
//                 int left = j + 1;
//                 int right = n - 1;
//                 while (left < right) {
//                     long long sum =
//                         (long long)nums[i] + nums[j] + nums[left] + nums[right];
//                     if (sum == target) {
//                         result.push_back(
//                             {nums[i], nums[j], nums[left], nums[right]});
//                         while (left < right && nums[left] == nums[left + 1]) {
//                             left++;
//                         }
//                         while (left < right && nums[right] == nums[right - 1]) {
//                             right--;
//                         }
//                         right--;
//                         left++;
//                     } else if (sum < target) {
//                         left++;
//                     } else {
//                         right--;
//                     }
//                 }
//             }
//         }
//         return result;
//     }
// };
// 31 class Solution {
//    public:
//     bool isValid(string s) {
//         stack<char> st;
//         for (char c : s) {
//             if (c == '(' || c == '[' || c == '{') {
//                 st.push(c);
//             } else {
//                 if (st.empty()) {
//                     return false;
//                 } else if ((c == ')' && st.top() == '(') ||
//                            (c == ']' && st.top() == '[') ||
//                            (c == '}' && st.top() == '{')) {
//                     st.pop();
//                 } else {
//                     return false;
//                 }
//             }
//         }
//         return st.empty();
//     }
// };
// 32 class Solution {
//    public:
//     string removeDuplicates(string s) {
//         stack<char> st;
//         for (int i = 0; i < s.size(); i++) {
//             if (!st.empty() && s[i] == st.top()) {
//                 st.pop();
//             } else {
//                 st.push(s[i]);
//             }
//         }
//         string str;
//         while (!st.empty()) {
//             str += st.top();
//             st.pop();
//         }
//         reverse(str.begin(), str.end());
//         return str;
//     }
// };
// 33 class Solution {
//    public:
//     int evalRPN(vector<string>& tokens) {
//         stack<long long> st;
//         for (int i = 0; i < tokens.size(); i++) {
//             if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" ||
//                 tokens[i] == "/") {
//                 long long num1 = st.top();
//                 st.pop();
//                 long long num2 = st.top();
//                 st.pop();
//                 if (tokens[i] == "+")
//                     st.push(num2 + num1);
//                 if (tokens[i] == "-")
//                     st.push(num2 - num1);
//                 if (tokens[i] == "*")
//                     st.push(num2 * num1);
//                 if (tokens[i] == "/")
//                     st.push(num2 / num1);
//             } else {
//                 st.push(stoll(tokens[i]));
//             }
//         }
//         long long result = st.top();
//         return result;
//     }
// };
