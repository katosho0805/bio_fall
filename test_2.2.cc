#include<iostream>
#include<string>
#include<vector>
using namespace std;

double CalcGCcontent(string seq){
    int gc_content=0;
    int total_length=seq.size();

    if(total_length=0){
        return 0.0;
    }

    for(int i=0;i<total_length;i++){
        char c=seq[i];
        if(c=='G'||c=='C'){
            gc_content++;
        }
    }

    return (double)gc_content/total_length;

}

int main(void){

  vector<string> sequences = {
        "ATGCGAT",  // GC 3/7 (約 42.9%)
        "GCGCGCGC", // GC 8/8 (100%)
        "ATATATAC", // GC 1/8 (12.5%)
        "CCCGGGTT", // GC 6/8 (75%)
        "TTAACCGA"  // GC 3/8 (37.5%)
    };

  vector<string> high_gc_sequences;

  for(int i=0;i<sequences.size();i++){
    string current_seq=sequences[i];

    double  gc_content=CalcGCcontent(current_seq);
  
  if(gc_content>=0.5){
    high_gc_sequences.push_back(current_seq)
  }
 }

 for(int i=0;i<high_gc_sequences.size();i++){
    cout<<high_gc_sequences[i] <<endl;
 }