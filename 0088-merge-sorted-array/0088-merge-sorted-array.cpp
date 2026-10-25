class Solution {
public:
void ms(vector<int>& nums1,vector<int> & nums2, int m, int n){
    vector<int> temp;
    int left=0;
    int right=0;
    
    while(left<m && right<n){
        if(nums1[left]<=nums2[right]){
            temp.push_back(nums1[left]);
            left++;
        }else {
            temp.push_back(nums2[right]);
            right++;

        }
    }
    while(left < m){
        temp.push_back(nums1[left]);
        left++;
    }
    while(right <n){
        temp.push_back(nums2[right]);
        right++;
    }
    for(int i=0; i<m+n; i++){
        nums1[i]=temp[i];
    }

}
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        ms(nums1,nums2,m,n);
    }
};


// two pointer approach tc =O(m+n)

/** class Solution {
public:
    void merge(vector<int>& nums1, int m,
               vector<int>& nums2, int n) {

        int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;

        while(i >= 0 && j >= 0) {
            if(nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }

        while(j >= 0) {
            nums1[k--] = nums2[j--];
        }
    }
}; **/ 