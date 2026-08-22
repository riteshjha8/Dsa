class Solution {
public:
    bool isPalindrome(string &s,int i=0, int j=-1) {
     if(j==-1) j = s.size()-1;

     if(i>=j) return true;

     if(!isalnum(s[i]))
     return isPalindrome(s,i+1,j);

     if (!isalnum(s[j])){
        return isPalindrome(s,i,j-1);
     }
  

    if (tolower(s[i]) != tolower(s[j]))
    return false;

    return isPalindrome(s,i+1,j-1);
    }
};