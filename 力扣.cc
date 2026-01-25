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
