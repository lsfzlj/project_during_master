#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

class cube;
class location{
public:
	short x;
	short y;
	short z;
public:
	location(short a, short b, short c){
		x = a;
		y = b;
		z = c;
	}
	~location(){}
	friend class cube;
	friend void plus_cube(cube &a, cube b, location l, short p);
};
class cube{
public:
	short len;
	short P;
	vector<vector<vector<short>>>c;
	cube(vector<vector<vector<short>>>in, short max){ c = in; len = in.size(); P = max; }
	cube(){}
	short get_data(location l){
		if (l.x >= len || l.y >= len || l.z >= len) cout << "Visiting cube out of range" << endl;
		else  return c[l.x][l.y][l.z];
	}
	short get_data(short a, short b, short d){
		if (a >= len || b >= len || d >= len) cout << "Get_data  out of range" << endl;
		else
			return c[a][b][d];
	}
	void set_data(short a, short b, short d, short data){
		if (a >= len || b >= len || d >= len) cout << "Set_data out of range" << endl;
		c[a][b][d] = data%P;
	}
	bool is_zero(){
		for (int i = 0; i < len; i++){
			for (short j = 0; j < len; j++){
				for (short k = 0; k < len; k++){
					if (c[i][j][k] != 0)
						return false;
				}
			}
		}
		return true;
	}
	void print(){
		for (int i = 0; i < len; i++){
			for (short j = 0; j < len; j++){
				for (short k = 0; k < len; k++){
					cout << c[i][j][k];
					if (k == len - 1)
						cout << endl;
					else
						cout << " ";
				}
				if (j == len - 1)
					cout << endl;
			}
		}
	}
};

void plus_cube(cube &a, cube b, location l, short p){
	if (l.x + b.len > a.len || l.y + b.len > a.len || l.z + b.len > a.len)
		cout << "Plus two cube out of range" << endl;
	else {
		for (short i = l.x; i < l.x + b.len; i++){
			for (short j = l.y; j < l.y + b.len; j++){
				for (short k = l.z; k < l.z + b.len; k++){
					a.set_data(i, j, k, a.get_data(i, j, k) + b.get_data(i - l.x, j - l.y, k - l.z));
				}
			}
		}
	}

}
cube get_cube(short M, short P){
	short k1 = 0, k2 = 0, k3 = 0;
	vector<vector<vector<short>>>cubeA;
	vector<short>t1; vector<vector<short>>t2;
	for (int i = 0; i < pow(M, 3); i++){
		short t;
		cin >> t;
		if (t1.size() == M){
			if (t2.size() == M){
				cubeA.push_back(t2);
				t2.clear();
			}
			t2.push_back(t1);
			t1.clear();
		}
		t1.push_back(t);
	}
	t2.push_back(t1); cubeA.push_back(t2);
	cube result(cubeA, P);
	return result;
}
vector<location> process(cube A, vector<cube>B, short index, vector<location>l){
	for (int i = 0; i < A.len; i++){
		for (int j = 0; j < A.len; j++){
			for (int k = 0; k < A.len; k++){
				if (i + B[index].len <= A.len&&j + B[index].len <= A.len&&k + B[index].len <= A.len){

					location temp(i, j, k);
					l.push_back(temp);
					cube abc = A;
					if (index < B.size()){
						plus_cube(A, B[index], temp, A.P);
					}
					else
						cout << "index erro" << endl;
					if (index == B.size() - 1){
						if (A.is_zero()){
							return l;
						}
						else{
							A = abc;
							l.pop_back();
							continue;
						}
					}
					else{
						vector<location> re = process(A, B, index + 1, l);
						A = abc; l.pop_back();
						if (re.empty())continue;
						else {
							return re;
						}
					}
				}
			}
		}
	}
	vector<location>q;
	return q;
}
int main(){
	short M, N, P;
	while (cin >> M >> N >> P){
		cube A = get_cube(M, P);
		vector<cube>B;
		for (short i = 0; i < N; i++){
			int t;
			cin >> t;
			cube temp = get_cube(t, P);
			B.push_back(temp);
		}
		vector<location>t;
		vector<location>re = process(A, B, 0, t);
		for (int i = 0; i < re.size(); i++){
			cout << re[i].x << " " << re[i].y << " " << re[i].z << endl;
		}
	}
	return 0;
}

