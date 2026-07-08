class Solution {
public:
    bool isPalindrome(int x) {

         if (x<0){
        return false;
       }
        double revN = 0;
       int original =x;

       while (x !=0){
        int ld = x%10;

        revN = (revN*10)+ld;
        x=x/10;
       }
       
      return revN == original;
    
    }
};