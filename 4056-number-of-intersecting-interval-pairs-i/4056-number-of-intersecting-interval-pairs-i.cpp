class Solution {
public:
    int countIntersectingIntervals(vector<vector<int>>& intervals) {
         int cnt=0;
        int elementcnt=intervals.size();
        vector<vector<int>> orderedsegment=intervals;
                sort(orderedsegment.begin(),orderedsegment.end(),[](const vector<int>& alphanode,const vector<int>&betanode){
                    return alphanode[0]<betanode[0];
                });
        
        vector<int> isolatedstart(elementcnt);
        for(int i =0; i<elementcnt; i++){
            isolatedstart[i]=orderedsegment[i][0];
        }
        for(int j=0; j<elementcnt;j++){
            int endtime=orderedsegment[j][1];

            auto rightmost_bound_iter=upper_bound(isolatedstart.begin(),isolatedstart.end(),endtime);

            int rightmost_bound_indx = distance(isolatedstart.begin(),rightmost_bound_iter);
            int valid_subsequent_pairs = max(0,rightmost_bound_indx-(j+1));
            cnt += valid_subsequent_pairs;
        }
        return cnt;
    }
};