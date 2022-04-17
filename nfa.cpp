#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <set>
using namespace std;
using std::cout;
void tokenize(string const &str, const char delim, vector<string> &out)
{
    stringstream ss(str);
    string s;
    while (getline(ss, s, delim))
        out.push_back(s);
}

int main()
{
    ifstream in;
    string input_line;
    vector<char> input_alphabet;
    vector<int> nfa_states, nfa_final_states;
    vector<vector<int>> dfa_states, dfa_final_states;
    vector<int> dfa_initial_state;
    map<pair<int, char>, vector<int>> nfa_transition;
    map<pair<vector<int>, char>, vector<int>> dfa_transition;
    map<vector<int>, int> rename;
    vector<int> renamed_dfa_states, renamed_dfa_final_states;
    map<pair<int, char>, int> renamed_dfa_transition;
    int line = 0, initial_state = 0;
    in.open("nfa_input.txt");
    while (in >> input_line)
    {
        line++;
        if (line == 1)
        {
            vector<string> temp;
            tokenize(input_line, ',', temp);
            for (auto &s : temp)
                input_alphabet.push_back(s[0]);
        }
        if (line == 2)
        {
            vector<string> temp;
            tokenize(input_line, ',', temp);
            for (auto &s : temp)
            {
                int x = stoi(s);
                nfa_states.push_back(x);
            }
        }
        if (line == 3)
        {
            initial_state = stoi(input_line);
            vector<int> temp{initial_state};
            dfa_initial_state = temp;
            dfa_states.push_back(dfa_initial_state);
        }
        if (line == 4)
        {
            vector<string> temp;
            int flag = 0;
            tokenize(input_line, ',', temp);
            for (auto &s : temp)
            {
                int x = stoi(s);
                if (flag == 0 && x == dfa_states[0][0])
                {
                    dfa_final_states.push_back(dfa_states[0]);
                    flag = -1;
                }
                nfa_final_states.push_back(x);
            }
        }
        if (line > 4 && input_line != "")
        {
            vector<string> temp;
            tokenize(input_line, ',', temp);
            pair<int, char> lhs{stoi(temp[0]), temp[1][0]};
            vector<int> store;
            for (size_t i = 2; i < temp.size(); i++)
                store.push_back(stoi(temp[i]));
            nfa_transition[lhs] = store;
        }
    }

    for (size_t i = 0; i < dfa_states.size(); i++)
    {
        vector<int> dfa_current_state = dfa_states[i];
        rename[dfa_current_state] = i;
        renamed_dfa_states.push_back(i);
        for (auto x : input_alphabet)
        {
            set<int> temp;
            for (auto &var : dfa_current_state)
            {
                pair<int, char> lhs{var, x};
                if (nfa_transition.find(lhs) != nfa_transition.end())
                {
                    vector<int> cor = nfa_transition[lhs];
                    for (auto &v : cor)
                        temp.insert(v);
                }
            }

            vector<int> tempv(temp.begin(), temp.end());
            if (tempv.size() == 0)
                tempv = vector<int>{-1};
            if (find(dfa_states.begin(), dfa_states.end(), tempv) == dfa_states.end())
                dfa_states.push_back(tempv);
            for (auto x : tempv)
            {
                if ((find(nfa_final_states.begin(), nfa_final_states.end(), x) != nfa_final_states.end()) && (find(dfa_final_states.begin(), dfa_final_states.end(), tempv) == dfa_final_states.end()))
                {
                    dfa_final_states.push_back(tempv);
                    break;
                }
            }
            pair<vector<int>, char> lhsv{dfa_current_state, x};
            dfa_transition[lhsv] = tempv;
        }
    }

    for (auto x : dfa_final_states)
        renamed_dfa_final_states.push_back(rename[x]);

    for (auto x : dfa_transition)
    {
        pair<int, char> lhs{rename[x.first.first], x.first.second};
        renamed_dfa_transition[lhs] = rename[x.second];
    }

    cout << "\n\nInput NFA\n\n";
    cout << "\nInput Alphabets\n";
    for (auto &s : input_alphabet)
        cout << s << " ";
    cout << "\nStates\n";
    for (auto &s : nfa_states)
        cout << s << " ";
    cout << "\nFinal States\n";
    for (auto &s : nfa_final_states)
        cout << s << " ";
    cout << "\nTransition Function\n";
    for (auto &s : nfa_transition)
    {
        cout << s.first.first << "," << s.first.second << " -> { ";
        for (auto &t : s.second)
            cout << t << " ";
        cout << "}\n";
    }
    cout << "\n\nCorresponding DFA\n\n";
    cout << "\nInput Alphabet\n";
    for (auto &s : input_alphabet)
        cout << s << " ";

    cout << "\n\nStates\n";
    for (auto &s : dfa_states)
    {
        cout << "{ ";
        for (auto &t : s)
            cout << t << " ";
        cout << "}";
        cout << "\n";
    }
    cout << "\n Final States\n";
    for (auto &s : dfa_final_states)
    {
        cout << "{ ";
        for (auto &t : s)
            cout << t << " ";
        cout << "}";
        cout << "\n";
    }

    cout << "\nTransition Function\n";
    for (auto &s : dfa_transition)
    {
        cout << "({ ";
        for (auto x : s.first.first)
            cout << x << " ";
        cout << "}," << s.first.second << " -> {";
        for (auto x : s.second)
            cout << x << " ";
        cout << "})";
        cout << "\n";
    }
    cout << "\n\nCorresponding renamed DFA\n\n";
    cout << "\nInput Alphabets\n";
    for (auto &s : input_alphabet)
        cout << s << " ";
    cout << "\nStates\n";
    for (auto &s : renamed_dfa_states)
        cout << s << " ";
    cout << "\nFinal States\n";
    for (auto &s : renamed_dfa_final_states)
        cout << s << " ";
    cout << "\nTransition Function\n";
    for (auto &s : renamed_dfa_transition)
        cout << s.first.first << "," << s.first.second << " -> " << s.second << "\n";
    cout << "\n";

    return 0;
}