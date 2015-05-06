#include "Audio.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstlib>
#include <cstdint>
#include <algorithm>
#include <utility>
#include <vector>
#include <numeric>
#include <math.h>



using namespace std;
namespace MSHIMA001{


/*Audio::Audio(int w, int h, unsigned char* buffer):width(w), height(h){
      
}*/


      
   Audio(){
      channels = 1;
      bitcount = sizeof(T);
   }    

   Audio::Audio( string fileName){
      load(fileName);
    
      
   }

   Audio(int chan, int bit, int samp, vector<T> t):channels(chan), bitcount(bit), samplingRate(samp), data(t){
      length = t.size();
   }

   Audio::~Audio(){ // destructor
      
      channels = bitcount = samplingRate = 0;
   
   
   }
   
   //copy constructor
   Audio::Audio(const Audio& N):channels(N.channels), bitcount(N.bitcount), samplingRate(N.samplingRate), length(N.length), data(N.data){
      cout<<"In copy constructor"<<endl;
      cout<<"allocating memory"<<endl;
   
   
   }
   
   //move constructor
   Audio::Audio(Audio&& N):channels(N.channels), bitcount(N.bitcount), samplingRate(N.samplingRate), length(N.length), data(N.data){
      cout<<"In move "<<endl;
         N.channels = N.bitcount = N.samplingRate = 0;
         data= NULL;
      
  
   }
   
   //assignment operator
   
   Audio& Audio::operator=(const Audio& N ){
      if(this == &N)
         return *this;
    
      channels = N.channels;
      bitcount = N.bitcount;
      samplingRate = N.samplingRate;
      data = N.data;
    
      return *this;
      
   }
   //move assignment operator.
   Audio& Audio::operator=(Audio&& N){
      cout<<"in move op"<<endl;
    if(this == &N)
         return *this;
       
      channels = N.channels;
      bitcount = N.bitcount;
      samplingRate = N.samplingRate;
      data = N.data;
      
      N.data.clear();
    
      return *this;

   }
   
   //method to read input files
   bool  Audio::load(std::string fileName){
      //initialise data members
      channels = 1;
      std::string s = fileName;
      std::string delimiter = "_";
   
      size_t pos = 0;
      std::string token;
      
       pos = s.find(delimiter);
             
      s.erase(0, pos + delimiter.length());//firstpart of name

      
      pos = s.find(delimiter);
      token = s.substr(0, pos);
      istringstream ss(token);
      ss>> samplingRate;
      
      
      s.erase(0, pos + delimiter.length()); 
            pos = s.find(delimiter);
             
      s.erase(0, pos + delimiter.length());//signed
      
        pos = s.find("b");
      token = s.substr(0, pos);
      istringstream ss1(token);
      ss1>>bitcount;
      
      ifstream file(fileName , ios::in |ios::binary);
      if(file){
  
         file.seekg (0, file.end);
         int size = file.tellg();
         file.seekg (0, file.beg);
         
          length = size/sizeof(T);
         data.resize(length);
         
         file.read((char*)&data[0], length);
         if (file)
            std::cout << "all characters read successfully."<<file.gcount()<<endl;
         else
            std::cout << "error: only " << file.gcount() << " could be read"<<endl;
         
         
    
         file.close();
        
         return true;
        
      
      }else{
         cout<<"Unable to open file, ensure correct filename"<<endl;	
         return false;	
      }
   
   }
   void Audio::save(std::string fileName ){
      cout<<"saving"<<endl;
      ofstream head(fileName, ios::out|ios::binary);
      if(head){
         
      
  
         T unit;// 
         for(auto i=this->begin();i!=end();++i){
         
            byte  = *i;
            head.write((char*)&unit,1);
         }
      
      
      
         head.close();
      }
      else{
         cout<<"Unable to open file"<<endl;
      }
   }
   
   Audio::Iterator Audio::begin(void) const{ // etc
      return  Iterator(data.begin());
   
       
   
   }
   Audio::Iterator Audio::end(void) const{
      return Iterator(data.end());
   }
   
   Audio Audio::operator+(const Audio& N ){;
      cout<<"Adding"<<endl;
   
      cout<<"copy constructiong"<<endl;
      if(N.channels != channels || N.length != length|| N.bitcount!= bitcount ){
         cerr<< "Can't add these arrs, dimensions don't match"<<endl;
         return *this;
      }
      Audio temp<T,1>(*this);//copy constructor
   
      cout<<"iterators creating"<<endl;
      Audio::Iterator beg = temp.begin(), end = temp.end();
      Audio::Iterator inStart = N.begin(), inEnd = N.end();
      cout<<"iterators created"<<endl;
   
      while ( beg != end) { 
      
         int check = (*beg + *inStart);
         if(check> (1<<sizeof(T))){
            check = (1<<sizeof(T)) ;
         }
         
      
         *beg = check; 
      
         ++beg;
         ++inStart;
      } 
   
   
   
      return temp;
      
      
   
   }
   Audio operator|(const Audio& N ){
      if(N.channels != channels || N.length != length|| N.bitcount!= bitcount ){
         cerr<< "Can't append these arrs, dimensions don't match"<<endl;
         return *this;
      }
      
      vector<T> result(2*length);
      copy ( data.begin(), data.end(), result.begin() );
      copy(N.data.begin(), N.data.end(), back_inserter(result));
      Audio<T,1> temp(channels, bitcount, samplingRate, result);
   
    
   
   
   
      return temp;

   
      
   
   
   }
   Audio operator^(pair<int, int> N ){
      int m = N.first;
      int n = N.second;
      
      vector<T> result(length + m - n-1);
      copy(data.begin() , data.begin()+ m, result.begin());
      copy(data.begin()+ n+1, data.end(), back_inserter(result));
      
       Audio<T,1> temp(channels, bitcount, samplingRate, result);
      return temp;
      
        
        
   }
   Audio operator*(pair<float, float> F){
      float factor = F.first;
      
        vector<T> result(length);
      transform(data.begin(), data.end(), result.begin(), [factor](x){return (int)(x*factor)});
      Audio<T, 1> temp(channels, bitcount, samplingRate, result);
      return temp;
      
   
   }

   Audio add(Audio& N, pair<int, int>f){
        int m = N.first;
        int n = N.second;
        vector<T> result(length);
        
        copy(N.begin()+m, N.begin() + n+1, result.begin()+m);
        
        Audio<T,1> temp(channels, bitcount, samplingRate, result);
        temp = *this + temp;
        return temp;
        
   }
   Audio rev()
   {  
       vector<T> result(length);
       copy(data.begin(), data.end(), result.begin());
       reverse(result.begin(), result.end());
       Audio<T,1> temp(channels, bitcount, samplingRate, result);
      return temp;
      
      
   }
   double rms(){
      long product = std::accumulate(data.begin(), data.end(), 0, [](x){return x*x});
      double rms = sqrt(product/length);
      return rms ;
     
      Audio<T,1> temp(channels, bitcount, samplingRate, result);
      return temp;

      
   }
   Audio norm(pair<float, float> f){
      float  out = f.first;
      double rms = this->rms();
      vector<T> result(length);
      
      Normalise<T,1> functor(out); 
      transform(data.begin(), data.end(), result.begin(), functor);
      Audio<T,1> temp(channels, bitcount, samplingRate, result);
      return temp;


      
      
   }
   
   /*void fadein(double n){
    
 
      for_each(data.begin(), data.end(), result.begin(),[samplingRate, n](x){return  } );
         
   }

  
      void fadeout(double n){
            
      
      }*/

   ostream& operator<<(ostream& head, const Audio& N ){
   
   

      if(head){
         
      
  
         T unit;// 
         for(auto i=this->begin();i!=end();++i){
         
            byte  = *i;
            head.write((char*)&unit,1);
         }
      
      
      
         head.close();
      }
      else{
         cout<<"Unable to open file"<<endl;
      }
      
      return head;
   
   
   
   
   
   
   }
   istream& operator>>( istream& file,  Audio& N ){

      if(file){
  
         file.seekg (0, file.end);
         int size = file.tellg();
         file.seekg (0, file.beg);
         
          length = size/sizeof(T);
         N.data.resize(length);
         N.length = length;
         
         file.read((char*)&N.data[0], length);
         if (file)
            std::cout << "all characters read successfully."<<file.gcount()<<endl;
         else
            std::cout << "error: only " << file.gcount() << " could be read"<<endl;
         
         
    
         file.close();
        
        
        
      
      }else{
         cout<<"Unable to open file, ensure correct filename"<<endl;	
         	
      } 
      return file;  
   }

   bool MSHIMA001::Audio::operator==(const Audio& N) {
      if(length!=N.length| samplingRate != N.samplingRate | bitcount != N.bitcount| channels!= N.channels)
         return false;
      
      for(int i = 0; i< length; i++){
         if(data[i]!= N.data[i])
            return false;
      
      }
      return true;
   }
   
}

