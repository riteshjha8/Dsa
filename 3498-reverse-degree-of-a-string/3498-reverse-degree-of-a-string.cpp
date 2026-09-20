class Solution {
public:
    int reverseDegree(string s) {
      int sum=0;
      for(int i=0; i<s.length(); i++){
        // before "abc" a=1, b=2...
        int reverseval= 26-(s[i]-'a'); // reverse the string now a=26 b=25 so 26-0=26
        sum +=reverseval*(i+1);

      }
      return sum;
    }
};