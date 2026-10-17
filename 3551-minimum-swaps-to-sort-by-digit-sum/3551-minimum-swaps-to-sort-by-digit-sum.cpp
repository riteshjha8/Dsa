class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n=nums.size();
        vector<pair<int,int>> v;
        for(int i=0; i<n;i++){
            int x= nums[i], sum=0;

            while(x>0){
                sum+=x%10;
                x /=10;
            }
            v.push_back({sum,nums[i]});
        }
        sort(v.begin(),v.end());

        unordered_map<int,int> pos;
        for(int i=0; i<n; i++){
            pos[v[i].second] =i;
        }
        vector<bool> visited(n,false);
        int swaps =0;

        for(int i=0; i<n; i++){
            if(visited[i] || pos[nums[i]]==i)
        continue;
        int j=i;
        int cycle=0;
        while(!visited[j]){
            visited[j]=true;
            j= pos[nums[j]];
            cycle++;
        }
        swaps +=cycle-1;
        }
        return swaps;
    }
};