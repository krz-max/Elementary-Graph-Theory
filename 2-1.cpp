#include <bits/stdc++.h>

using namespace std;

template <class T>
void print_iterator(T iterable){
    for(auto it:iterable){
        cout << it << " ";
    }
    cout << endl;
}

size_t remove_substring(vector<string>& strings){
    if(!strings.size()) return 0;
    sort(strings.begin(), strings.end(), [](const auto& s1, const auto& s2){
        return s1.length() >= s2.length();
    });
    // print_iterator<vector<string>>(strings);
    for(int i = strings.size()-1; i > 0; i--){
        for(int j = i-1; j >= 0; j--){
            if(strings[j].find(strings[i]) != string::npos){
                strings.erase(strings.begin()+i);
                // cout << "removed string: " << strings[i] << endl;
                break;
            }
        }
    }
    return 0;
}

size_t match_string(string& s1, string& s2){
    // append s2 to s1 with longest match
    int max_match = min(s1.size(), s2.size());
    for(int i = max_match; i > 0; i--){
        if(s1.substr(s1.size() - i) == s2.substr(0, i)){
            s1.append(s2.substr(i));
            return 0;
        }
    }
    s1.append(s2);
    return 0;
}

int main(){
    unordered_set<string> input_strings;
    int n = 0; // how many lines of strings
    cin >> n;
    string temp;
    while(n--){
        cin >> temp;
        input_strings.insert(temp);
    }
    vector<string> unique_strings(input_strings.begin(), input_strings.end());
    // print_iterator<vector<string>>(unique_strings);
    
    remove_substring(unique_strings);
    
    string result = "";
    sort(unique_strings.begin(), unique_strings.end());
    n = unique_strings.size();
    do{
        temp = unique_strings[0];
        
        for(int i = 1; i < n; i++){
            match_string(temp, unique_strings[i]);
        }

        if(result.empty() || result.length() > temp.length() || (result.length() == temp.length() && temp < result) ){
            result = temp;
        }
    }while(next_permutation(unique_strings.begin(), unique_strings.end()));
    cout << result;
    return 0;
}