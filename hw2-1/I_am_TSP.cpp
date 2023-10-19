#include <bits/stdc++.h>

using namespace std;

class MinimumSuperString
{
public:
    MinimumSuperString(){};
    void build_string_sets()
    {
        unordered_set<string> input_strings;
        int n;
        cin >> n;
        string temp;
        while (n--)
        {
            cin >> temp;
            input_strings.insert(temp);
        }
        unique_strings = vector<string>(input_strings.begin(), input_strings.end());
        remove_substring();
    };
    int solve()
    {
        build_string_sets();
        string result = "", temp;
        sort(unique_strings.begin(), unique_strings.end());
        int n = unique_strings.size();
        do
        {
            temp = unique_strings[0];

            for (int i = 1; i < n; i++)
            {
                match_string(temp, unique_strings[i]);
            }

            if (result.empty() || result.length() > temp.length() || (result.length() == temp.length() && temp < result))
            {
                result = temp;
            }
        } while (next_permutation(unique_strings.begin(), unique_strings.end()));
        cout << result << endl;
        return 0;
    }

private:
    vector<string> unique_strings;
    /*
    This function concatenate s1 and s2, removing all overlapped characters in s1's suffix and s2's prefix.
    @param s1: The base string
    @param s1: The minor string, to be append to s1
    @return  : The shortest "superstring" of s1 + s2.
    Example: s1 = saafda, s2 = afdakfdk. Then the result will become "saafdakfdk"
    */
    size_t match_string(string &s1, string &s2)
    {
        for (int i = min(s1.size(), s2.size()); i > 0; i--)
        {
            if (s1.substr(s1.size() - i) == s2.substr(0, i))
            {
                s1 += s2.substr(i);
                return 0;
            }
        }
        s1 += s2;
        return 0;
    }
    /*
    This function removes strings that are any other strings' substring in the same array.
    Example: arr = ["abc", "c"], the resulting array is: arr = ["abc"], because "c" is a substring of "abc"
    */
    void remove_substring()
    {
        if (!unique_strings.size())
            return;
        for (int i = unique_strings.size() - 1; i >= 0; i--)
        {
            for (int j = 0; j < int(unique_strings.size()); j++)
            {
                if (i == j)
                    continue;
                // check if s[i] is s[j]'s substring
                if (unique_strings[i].size() > unique_strings[j].size())
                    continue;
                if (unique_strings[j].find(unique_strings[i]) != string::npos)
                {
                    // s[i] is s[j]'s substring, remove s[i]
                    unique_strings.erase(unique_strings.begin() + i);
                    break;
                }
            }
        }
    }
};

int main()
{
    MinimumSuperString Solution;
    return Solution.solve();
}