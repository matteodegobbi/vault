

#include <iostream>
#include <vector>
using namespace std;



#define P(v) do { for (const auto& e : (v)) std::cout << e << ","; std::cout << std::endl; } while(0)

template <class T>
void partition(vector<T>& v, int l, int u, int& k) {
  int i = l+1;
  int j = u;
  T pv = v[l]; // NOTE: l non i
  while (i < j+1) {
    while (i < j+1 and v[i] <= pv) ++i;
    while (i < j+1 and pv <= v[j]) --j;
    if (i < j + 1) {
      swap(v[i], v[j]);
      ++i; --j;
    }
  };
  swap(v[l], v[j]);
  k = j;
  P(v);
}

template <class T>
void quicksort(vector<T>& v, int l, int u) {
  if (u -l + 1 > 1) {
    int k;
    partition(v, l, u, k);
    quicksort(v, l, k-1);
    quicksort(v, k+1, u);
  }
}
template <class T>
void quicksort(vector<T>& v) {
  quicksort(v, 0, v.size()-1);
}

int main(){
  vector<int> v{7,2,3,5,2,3,6,8};


  P(v);
  //quicksort<int>(v);
  int k;
  partition(v, 0, v.size()-1, k);

  P(v);
  cout << "k" << k << endl;

  return 0;
}
