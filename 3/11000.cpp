// #include <iostream>
// #define MAX_TIME 1000000001
// using namespace std;

// int main()
// {
//     int arr[MAX_TIME] = {0};
//     int N, si, ti;
//     cin >> N;
//     for (int i = 0; i < N; i++)
//     {
//         cin >> si;
//         cin >> ti;
//         arr[si]++;
//         arr[ti]--;
//     }

//     int max = 0;
//     int cur = 0;
//     for (int i = 0; i <= MAX_TIME; i++)
//     {
//         cur += arr[i];
//         if (cur > max)
//             max = cur;
//     }
//     cout << max;
//     return 0;
// }

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class ClassTime
{
public:
    ClassTime(int x) : si(0), ei(0){};
    ClassTime(int _si, int _ei) : si(_si), ei(_ei){};
    bool operator<(ClassTime &other) { return (ei < other.ei) ? true : false; }

    int si;
    int ei;
};

bool CT_si_compare(ClassTime a, ClassTime b)
{
    return a.si < b.si;
}

int main()
{
    ios::sync_with_stdio(0);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    priority_queue<int, vector<int>, greater<int>> q;

    vector<ClassTime> v;
    int N, si, ei;
    int max = 0;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> si;
        cin >> ei;
        v.push_back(ClassTime(si, ei));
    }
    sort(v.begin(), v.end(), CT_si_compare);

    for (auto it = v.begin(); it != v.end(); it++)
    {
        while (!q.empty() && q.top() <= (*it).si)
            q.pop();
        q.push((*it).ei);
        if (q.size() > max)
            max = q.size();
    }
    
    // for (auto it = v.begin(); it != v.end(); it++)
    // {
    //     if (!q.empty() && q.top() <= (*it).si)
    //         q.pop();
    //     q.push((*it).ei);
    // }
    // max = q.size();

    cout << max;

    return 0;
}