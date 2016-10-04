nclude<iostream>
#include<set>
#include<vector>
using namespace std;
static int m[1000];

void backtrack(const int& N, int total, int& ans, int index, const vector<set<char>>& nums, const vector<int>& s)
{
	if (index == 0)            //if all the routers was installed
	{
		if (total > ans)       //compare
		{
			ans = total;
		}
		return;
	}
	else
	{
		for (int i = 0; i < N; ++i)
		{
			if (m[i] == 0)
			{
				m[i] ++;
				int temptotal = s[i];
				for (auto p = nums[i].begin(); p != nums[i].end(); ++p)
				{
					m[*p] ++;
					if (m[*p] == 1)
					{
						temptotal += s[*p];
					}
				}
				backtrack(N, total + temptotal, ans, index - 1, nums, s);
				m[i] --;
				for (auto p = nums[i].begin(); p != nums[i].end(); ++p)
				{
					m[*p] --;
				}
			}

		}
		if (total > ans)            //if all the room was visited, while the router was surplus.
		{
			ans = total;
		}
		return;
	}
}
int main()
{
	int N, M;
	while (cin >> N >> M)
	{
		vector<int> s(N, 0);
		for (int i = 0; i < N; ++i)
		{
			cin >> s[i];
		}
		vector<set<char>> nums(N,set<char>());
		for (int t = 0; t < N - 1; ++t)
		{
			int  i, j;
			cin >> i >> j;
			nums[i-1].insert(j-1); //store the doors between two rooms
			nums[j-1].insert(i-1);
		}
		int total = 0;
		int ans = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			if (m[i] == 0)
			{
				m[i] ++;
				int temptotal = s[i];           // add the satisfaction of room-self
				for (auto p = nums[i].begin(); p != nums[i].end(); ++p) //use the static char[] to mark the visied rooms
				{
					if (m[*p] == 0)      //if the neighbor room is not visited

					{
						m[*p] ++;                   // mark it's visited
						temptotal += s[*p];       //add the satisfaction of the neighbor
					}
				}
				backtrack(N, total + temptotal, ans, M - 1, nums, s);  //backtrack
				m[i] --;                                               
				for (auto p = nums[i].begin(); p != nums[i].end(); ++p)   //mark the room not visited
				{
					m[*p]--;
				}
			}

		}
		cout << ans << endl;
	}
	return 0;
}

