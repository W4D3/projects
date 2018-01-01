#include<iostream>
#include<string>
#include<list>

using namespace std;

int schedule[84];

void print( list<int> l){
   for(list<int>::iterator it=l.begin(); it!=l.end() ; ++it)
      cout << " " << *it;
   cout<<endl;
}

void subset(int arr[], int size, int left, int index, list<int> &l){
   if(left==0){
      print(schedule);
      return;
   }
   for(int i=index; i<size;i++){
      l.push_back(arr[i]);
      subset(arr,size,left-1,i+1,l);
      l.pop_back();
   }

}     

int main(){
   int array[7]={1,2,3,4,5,6,7};
   for(int i = 0; i < 84; i++) {schedule[i] = 0};
   list<int> lt;   
   subset(array,7,7,0,lt);

   return 0;
}
