string longDivision(string num, ll divisor){
    string ans;
 
    ll idx = 0;
    ll temp = num[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (num[++idx] - '0');
 
    while (num.size() > idx) {
        ans += (temp / divisor) + '0';
 
        temp = (temp % divisor) * 10 + num[++idx] - '0';
    }
 
    if (ans.length() == 0)
        return "0";
 
    return ans;
}