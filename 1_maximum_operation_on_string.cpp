====================================================
    Questions
//    https://leetcode.com/problems/repeated-string-match/


======================================================



https://leetcode.com/contest/weekly-contest-313/problems/maximum-deletions-on-a-string/

typedef long long ll;
class Solution {
public:
    
    vector<vector<int>>hash;
    vector<int>t;
    ll P=37;
    ll MOD=1e9+7;
     void setHash (string& s) {
        int n = s.length();
        
        for (int j = 0; j < n; j ++) {
            ll pwr = P;
            ll prefix = 0;
            vector<int>& start_j_hash = hash[j]; 
            
            for (int k = j; k < n; k ++) {
                ll val = (pwr * s[k]) % MOD;
                prefix = (prefix + val) % MOD;
                
                start_j_hash.push_back (prefix);
                pwr = (pwr * P) % MOD;
            }
        }
    }
    
    bool IsEqual (int l1, int r1, int l2, int r2) {
        int len = (r2 - l2 + 1);
        
        return (hash[l1][len-1] == hash[l2][len-1]);
    }
    
    int maxDel (int ind, int len) {
        if (ind == len) return 0;
        if (t[ind] != -1) return t[ind];
        
        int& ans = t[ind];
        ans = 1;    // delete the entire string.
        
        for (int j = 1; j < len; j ++) {
            int l1 = ind, r1 = l1 + j - 1;
            int l2 = r1 + 1, r2 = l2 + j - 1;
            
            if (r1 >= len || r2 >= len) break;
            
            if (IsEqual(l1, r1, l2, r2)) ans = max (ans, 1+maxDel (l2, len));
        }
        return ans;
    }
    int deleteString(string s) {
       int n=s.length();
        t.clear();
        hash.clear();
        t.resize(n,-1);
        hash.resize(n);
        setHash(s);
        return maxDel(0,n);
    }
};
