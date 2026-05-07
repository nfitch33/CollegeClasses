#include <iostream>
#include <vector>
#include <queue>
using namespace std;


typedef pair<int, pair<int, int> > prs;

int partition(vector<int>& list, int first, int last) {

  int index, smallIndex;

  int pivot = max(min(list[first], list[last]), min(max(list[first], list[last]), list[(first + last) / 2])); // returns median value

  if(pivot == list[last]){ // if pivot is last, switch with first position
    swap(list[first], list[last]);
  }
  else if(pivot == list[(first + last) / 2]){ // if pivot is middle, switch with first
    swap(list[first], list[(first + last) / 2]);
  }

  smallIndex = first;
  for(index = first + 1; index <= last; index++){
    if(list[index] < pivot){ // check if current element is less than pivot
      smallIndex++;
      swap(list[smallIndex], list[index]);
    }
  }
  
  swap(list[first], list[smallIndex]);
  return smallIndex;
}

void quicksort(vector<int>& list, int first, int last){
  if(first < last){
    int pivot = partition(list, first, last);
    quicksort(list, first, pivot - 1);
    quicksort(list, pivot + 1, last);
  }
}

void multiway_merge(vector<vector<int> >& input_lists, vector<int>& output_list) {
  priority_queue<prs, vector<prs>, greater<prs> > p_queue;
  output_list.clear();
  
  for(size_t i = 0; i < input_lists.size(); i++){
    prs tmp = make_pair(input_lists[i][0], make_pair(i, 0));
    p_queue.push(tmp);
  }
  
  while(!(p_queue.empty())){
    prs curr = p_queue.top();
    p_queue.pop();

    int i = curr.second.first; 
    int j = curr.second.second; 

    output_list.push_back(curr.first);

    if(j + 1 < input_lists[i].size()){
      p_queue.push(make_pair(input_lists[i][j + 1], make_pair(i, j + 1)));
    }
  }
} 

int main(int argc, char** argv) {
  int n, m;
  cin >> n >> m;

  vector<vector<int> > input_lists(n, vector<int>(m));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> input_lists[i][j];
    }
  }

  // Quicksort k sublists
  for (int i = 0; i < input_lists.size(); ++i){
    quicksort(input_lists[i], 0, m-1);
  }
  // Merge n input sublists into one sorted list
  vector<int> output_list(n * m);
  multiway_merge(input_lists, output_list);

  for (int i = 0; i < output_list.size(); ++i){
    cout << output_list[i] << " ";
  }

  cout << endl;

  return 1;
}
