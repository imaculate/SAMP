#include "Audio.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <utility>
#include <vector>
#include <numeric>
#include <math.h>

using namespace std;
namespace MSHIMA001{


   template<typename T, int chans> 
   Audio<T,chans>::Audio(){
      channels = 1;
      bitcount = sizeof(T);
   }    
   template<typename T, int chans>
   Audio<T,chans>::Audio( string fileName){
      load(fileName);
    
      
   }
   template<typename T, int chans>
   Audio<T,chans>::Audio(int chan, int bit, int samp, vector<T> t):channels(chan), bitcount(bit), samplingRate(samp), data(t){
      length = t.size();
      cout<<"In constructor"<<endl;
   }
   template<typename T, int chans>
   Audio<T,chans>::~Audio(){ // destructor
      
      channels = bitcount = samplingRate = 0;
   
   
   }
   
   //copy constructor
   template<typename T, int chans>
   Audio<T,chans>::Audio(const Audio<T, chans>& N):channels(N.channels), bitcount(N.bitcount), samplingRate(N.samplingRate), length(N.length), data(N.data){
      cout<<"In copy constructor"<<endl;
      cout<<"allocating memory"<<endl;
   
   
   }
   
   //move constructor
   template<typename T, int chans>
   Audio<T,chans>::Audio(Audio<T, chans>&& N):channels(N.channels), bitcount(N.bitcount), samplingRate(N.samplingRate), length(N.length), data(N.data){
      cout<<"In move "<<endl;
      N.channels = N.bitcount = N.samplingRate = 0;
     
   
   }
   
   //assignment operator
   template<typename T, int chans>
   Audio<T,chans>& Audio<T,chans>::operator=(const Audio<T, chans>& N ){
      if(this == &N)
         return *this;
    
      channels = N.channels;
      bitcount = N.bitcount;
      samplingRate = N.samplingRate;
      data = N.data;
    
      return *this;
      
   }
   //move assignment operator.
   template<typename T, int chans>
   Audio<T,chans>& Audio<T,chans>::operator=(Audio<T, chans>&& N){
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
   template<typename T, int chans>
   bool  Audio<T,chans>::load(std::string fileName){
      cout<<"loading"<<endl;
      //initialise data members
      channels = 1;
      std::string s = fileName;
      std::string delimiter = "_";
   
      size_t pos = 0;
      std::string token;
      
      pos = s.find(delimiter);
             
      s.erase(0, pos + delimiter.length());//firstpart of name
   
      
      pos = s.find(delimiter);
      cout<<"getting sample Rate"<<endl;
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
      cout<<"Creating file stream"<<endl;
      
      ifstream file(fileName , ios::in |ios::binary);
      if(file){
      
         file.seekg (0, file.end);
         int size = file.tellg();
         file.seekg (0, file.beg);
         
         length = size/sizeof(T);
         data.resize(length);
         for(auto i =0; i < length; i++){
            file.read((char*)&data[i], sizeof(T));
         }
         if (file)
            std::cout << "all characters read successfully."<<file.gcount()<<endl;
         else
            std::cout << "error: only " << file.gcount() << " could be read"<<endl;
         
         
      
         file.close();
        
         return true;
        
      
      }
      else{
         cout<<"Unable to open file, ensure correct filename"<<endl;	
         return false;	
      }
   
   }
   template<typename T, int chans>
   void Audio<T,chans>::save(std::string fileName ){
      cout<<"saving"<<endl;
      ofstream head(fileName, ios::out|ios::binary);
      if(head){
         
      
      
         T unit;// 
         for(auto i=data.begin();i!=data.end();++i){
         
            unit  = *i;
            head.write((char*)&unit,1);
         }
      
      
      
         head.close();
      }
      else{
         cout<<"Unable to open file"<<endl;
      }
   }
   
   
   template<typename T, int chans>
   Audio<T,chans> Audio<T,chans>::operator+(const Audio<T, chans>& N ){;
      cout<<"Adding"<<endl;
   
      cout<<"copy construction"<<endl;
      if(N.channels != channels || N.length != length|| N.bitcount!= bitcount ){
         cerr<< "Can't add these arrs, dimensions don't match"<<endl;
         return *this;
      }
      Audio<T,chans> temp(*this);//copy constructor
   
      cout<<"iterators creating"<<endl;
      auto beg = temp.data.begin(), end = temp.data.end();
      auto inStart = N.data.begin(), inEnd = N.data.end();
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
   template<typename T, int chans>
   Audio<T,chans> Audio<T,chans>::operator|(const Audio<T, chans>& N ){
      if(N.channels != channels || N.length != length|| N.bitcount!= bitcount ){
         cerr<< "Can't append these arrs, dimensions don't match"<<endl;
         return *this;
      }
      
      vector<T> result(2*length);
      copy ( data.begin(), data.end(), result.begin() );
      copy(N.data.begin(), N.data.end(), back_inserter(result));
      Audio<T,chans> temp(channels, bitcount, samplingRate, result);
   
    
   
   
   
      return temp;
   
   
      
   
   
   }
   template<typename T, int chans>
   Audio<T,chans> Audio<T,chans>::operator^(pair<int, int> N ){
      int m = N.first;
      int n = N.second;
      
      vector<T> result(length + m - n-1);
      copy(data.begin() , data.begin()+ m, result.begin());
      copy(data.begin()+ n+1, data.end(), back_inserter(result));
      
      Audio<T,chans> temp(channels, bitcount, samplingRate, result);
      return temp;
      
        
        
   }
   template<typename T, int chans>
   Audio<T,chans> Audio<T,chans>::operator*(pair<float, float> F){
      float factor = F.first;
      
      vector<T> result(length);
      transform(data.begin(), data.end(), result.begin(), [factor](T x){return (T)(x*factor);});
      Audio<T, chans> temp(channels, bitcount, samplingRate, result);
      return temp;
      
   
   }
   template<typename T, int chans>
   Audio<T,chans> Audio<T,chans>::add(Audio<T, chans>& N, pair<int, int>f){
      int m = f.first;
      int n = f.second;
      vector<T> result(length);
        
      copy(N.data.begin()+m, N.data.begin() + n+1, result.begin()+m);
        
      Audio<T,chans> temp(channels, bitcount, samplingRate, result);
      temp = *this + temp;
      return temp;
        
   }
   template<typename T, int chans>
   void Audio<T,chans>::rev()
   {  
      cout<<"in reverse"<<endl;
      
      reverse(data.begin(), data.end());
      
      cout<<"reversed!"<<endl;
    
      
   }
   template<typename T, int chans>
   double Audio<T,chans>::rms(){
     unsigned long long int product;
      for(auto i = 0; i<length; i++){
         product += (long)(data[i]) *  (long)(data[i]);
      }
      double rms = sqrt(product/length);
      return rms ;
     
      
      
   }
   
   template<typename T, int chans>
   Audio<T,chans> Audio<T,chans>::norm(pair<float, float> f){
      float  out = f.first;
      double rms = this->rms();
      vector<T> result(length);
      
      Normalise<T,chans> functor(out); 
      transform(data.begin(), data.end(), result.begin(), functor);
      Audio<T,chans> temp(channels, bitcount, samplingRate, result);
      return temp;
   
   
      
      
   }
   
   /*void fadein(double n){
    
 
      for_each(data.begin(), data.end(), result.begin(),[samplingRate, n](x){return  } );
         
   }

  
      void fadeout(double n){
            
      
      }*/
   template <typename T, int chans>
   ostream& operator<<(ostream& head, const Audio<T, chans>& N ){
   
      if(head){
         
      
      
         T unit;// 
         for(auto i=N.data.begin(); i!=N.data.end(); ++i){
         
            unit  = *i;
            head.write((char*)&unit,1);
         }
      
      
      }
      else{
         cout<<"Unable to open file"<<endl;
      }
      
      return head;
   
   
   
   
   
   
   }
   template <typename T, int chans>
   istream& operator>>( istream& file,  Audio<T,chans>& N ){
   
      if(file){
      
         file.seekg (0, file.end);
         int size = file.tellg();
         file.seekg (0, file.beg);
         
         int length = size/sizeof(T);
         N.data.resize(length);
         N.length = length;
         N.channels = 1;
         N.bitcount = sizeof(T);
         
        
         T unit;// 
         for(auto i=N.data.begin(); i!=N.data.end(); ++i){
         
            
            file.read((char*)i,1);
         }
      
         if (file)
            std::cout << "all characters read successfully."<<endl;
         else
            std::cout << "error: only some ints could be read"<<endl;
         
         
      
         
        
        
        
      
      }
      else{
         cout<<"Unable to open file, ensure correct filename"<<endl;	
         	
      } 
      return file;  
   }
      
   template<typename T, int chans>
   bool Audio<T,chans>::operator==(const Audio<T, chans>& N) {
      if(length!=N.length| samplingRate != N.samplingRate | bitcount != N.bitcount| channels!= N.channels)
         return false;
      
      for(int i = 0; i< length; i++){
         if(data[i]!= N.data[i])
            return false;
      
      }
      return true;
   }
 
   
   template<typename T, int chans>
     T Normalise<T, chans>::operator()(T in){
      long check = in * f ;
      if(check > (1<<sizeof(T))){
         check = (1<<sizeof(T));
      }
      return T(check);
   }
     
     


   template<typename T > 
   Audio<T,2>::Audio(){
      channels = 2;
      bitcount = sizeof(T);
   }    
   template<typename T >
   Audio<T,2>::Audio( string fileName){
      load(fileName);
    
      
   }
   template<typename T >
   Audio<T,2>::Audio(int chan, int bit, int samp, vector<pair<T,T>> t):channels(chan), bitcount(bit), samplingRate(samp), data(t){
   cout<<"In constructor"<<endl;
      length = t.size();
   }
   template<typename T >
   Audio<T,2>::~Audio(){ // destructor
      
      channels = bitcount = samplingRate = 0;
      
   
   }
   
   //copy constructor
   template<typename T >
   Audio<T,2>::Audio(const Audio<T,2>& N):channels(N.channels), bitcount(N.bitcount), samplingRate(N.samplingRate), length(N.length), data(N.data){
      cout<<"In copy constructor"<<endl;
      cout<<"allocating memory"<<endl;
   
   
   }
   
   //move constructor
   template<typename T >
   Audio<T,2>::Audio(Audio<T,2>&& N):channels(N.channels), bitcount(N.bitcount), samplingRate(N.samplingRate), length(N.length), data(N.data){
      cout<<"In move "<<endl;
      N.channels = N.bitcount = N.samplingRate = 0;
     
      
   
   }
   
   //assignment operator
   template<typename T >
   Audio<T,2>& Audio<T,2>::operator=(const Audio<T,2>& N ){
      if(this == &N)
         return *this;
    
      channels = N.channels;
      bitcount = N.bitcount;
      samplingRate = N.samplingRate;
      data = N.data;
    
      return *this;
      
   }
   //move assignment operator.
   template<typename T >
   Audio<T,2>& Audio<T,2>::operator=(Audio<T,2>&& N){
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
   template<typename T >
   bool  Audio<T,2>::load(std::string fileName){
      //initialise data members
      cout<<"loading"<<endl;
      channels = 1;
      std::string s = fileName;
      std::string delimiter = "_";
   
      size_t pos = 0;
      std::string token;
      
      pos = s.find(delimiter);
             
      s.erase(0, pos + delimiter.length());//firstpart of name
   
      
      pos = s.find(delimiter);
      token = s.substr(0, pos);
      cout<<"Obtained sample rate"<<endl;
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
         cout<<"File is not null"<<endl;
      
         file.seekg (0, file.end);
         int size = file.tellg();
         file.seekg (0, file.beg);
         cout<<size<< endl;
         
         length = size/(2*sizeof(T));
         
         cout<<"Length is "<<length<<endl;
         data.resize(length);
         cout<<"Vector resized"<<endl;
            pair<T,T> pod;
         //file.read((char*)&data[0], length);
         for(int i = 0; i< length; i++){
            T l,r;
            //file>>l>>r;
            //cout<<"Left " <<(long)l<<"Right "<<(long)r<<endl;
            
            
            file.read((char*)&(data[i].first),sizeof(T));
                file.read((char*)&(data[i].second),sizeof(T));
         }
                  
      
         file.close();
         cout<<"Done reading file"<<endl;
        
         return true;
        
      
      }
      else{
         cout<<"Unable to open file, ensure correct filename"<<endl;	
         return false;	
      }
   
   }
   template<typename T >
   void Audio<T,2>::save(std::string fileName ){
      cout<<"saving"<<endl;
      ofstream head(fileName, ios::out|ios::binary);
      if(head){
         
      
      
         pair<T, T> unit;// 
         for(auto i=data.begin();i!=data.end();++i){
         
            unit  = *i;
            head.write((char*)&(unit.first),1);
            head.write((char*)&(unit.second),1);
         }
      
      
      
         head.close();
      }
      else{
         cout<<"Unable to open file"<<endl;
      }
   }
   
   
   template<typename T >
   Audio<T,2> Audio<T,2>::operator+(const Audio<T,2>& N ){;
      cout<<"Adding"<<endl;
   
      cout<<"copy construction"<<endl;
      if(N.channels != channels || N.length != length|| N.bitcount!= bitcount ){
         cerr<< "Can't add these arrs, dimensions don't match"<<endl;
         return *this;
      }
      Audio<T,2> temp(*this);//copy constructor
   
      cout<<"iterators creating"<<endl;
      auto beg = temp.data.begin(), end = temp.data.end();
      auto inStart = N.data.begin(), inEnd = N.data.end();
      cout<<"iterators created"<<endl;
   
      while ( beg != end) { 
      
         int check = ((*beg).first + (*inStart).first);
         if(check> (1<<sizeof(T))){
            check = (1<<sizeof(T)) ;
         }
         
      
         (*beg).first = check; 
         
          check = ((*beg).second + (*inStart).second);
         if(check> (1<<sizeof(T))){
            check = (1<<sizeof(T)) ;
         }
         
      
         (*beg).second = check; 
      
      
         ++beg;
         ++inStart;
      } 
   
   
   
      return temp;
      
      
   
   }
   template<typename T >
   Audio<T,2> Audio<T,2>::operator|(const Audio<T,2>& N ){
      if(N.channels != channels || N.length != length|| N.bitcount!= bitcount ){
         cerr<< "Can't append these arrs, dimensions don't match"<<endl;
         return *this;
      }
      
      vector<pair<T,T>> result(2*length);
      copy ( data.begin(), data.end(), result.begin() );
      copy(N.data.begin(), N.data.end(), back_inserter(result));
      Audio<T,2> temp(channels, bitcount, samplingRate, result);
   
   
      return temp;
   
   
   }
   template<typename T >
   Audio<T,2> Audio<T,2>::operator^(pair<int, int> N ){
      int m = N.first;
      int n = N.second;
      
      vector<pair<T,T>> result(length + m - n-1);
      copy(data.begin() , data.begin()+ m, result.begin());
      copy(data.begin()+ n+1, data.end(), back_inserter(result));
      
      Audio<T,2> temp(channels, bitcount, samplingRate, result);
      return temp;
      
        
        
   }
   template<typename T >
   Audio<T,2> Audio<T,2>::operator*(pair<float, float> F){
      float factor = F.first;
      
      vector<pair<T,T>> result(length);
      transform(data.begin(), data.end(), result.begin(), [factor](pair<T,T> x){return make_pair((T)((x.first)*factor), (T)((x.second)*factor));});
      Audio<T,2> temp(channels, bitcount, samplingRate, result);
      return temp;
      
   
   }
   template<typename T >
   Audio<T,2> Audio<T,2>::add(Audio<T,2>& N, pair<int, int>f){
      int m = f.first;
      int n = f.second;
      vector<pair<T,T>> result(length);
        
      copy(N.data.begin()+m, N.data.begin() + n+1, result.begin()+m);
        
      Audio<T,2> temp(channels, bitcount, samplingRate, result);
      temp = *this + temp;
      return temp;
        
   }
   template<typename T >
   void Audio<T,2>::rev()
   
   {  
      cout<<"In reverse"<<endl;
           cout<<"Using reverse algorithm"<<endl;
      reverse(data.begin(), data.end());
      cout<<"Reversed!"<<endl;
            
      
   }
   template<typename T >
   pair<double,double> Audio<T,2>::rms(){
     
      unsigned long long int product1=0; 
       unsigned long long int product2 = 0;
      cout<<"Length is " << length<<endl;
      for(auto i = 0; i<length; i++){
         product1 += (long)(data[i].first) *  (data[i].first);
         product2 += (long)(data[i].second) *  (data[i].second);
         cout<<"at position "<<i <<" product is "<<product1<<endl;
         cout<<(long)(data[i].first)<<endl;
      }
       
      double rms1 = sqrt(product1/(double)length);
      double rms2 = sqrt(product2/(double)length);
      pair<double, double> ans = make_pair(rms1, rms2);
      return ans ;
     
      
      
   }
   
   template<typename T >
   Audio<T,2> Audio<T,2>::norm(pair<float, float> f){
      
      pair<double,double> rms = this->rms();
      vector<pair<T,T>> result(length);
      
      Normalise<T,2> functor(f, rms); 
      transform(data.begin(), data.end(), result.begin(), functor);
      Audio<T,2> temp(channels, bitcount, samplingRate, result);
      return temp;
   
   
      
      
   }
   
   /*void fadein(double n){
    
 
      for_each(data.begin(), data.end(), result.begin(),[samplingRate, n](x){return  } );
         
   }

  
      void fadeout(double n){
            
      
      }*/
   template <typename T >
   ostream& operator<<(ostream& head, const Audio<T,2>& N ){
   
      if(head){
         
      
      
         pair<T,T> unit;// 
         for(auto i=N.data.begin(); i!=N.data.end(); ++i){
         
            unit  = *i;
            head.write((char*)&(unit.first),1);
            head.write((char*)&(unit.second),1);
         
         }
      
      
      }
      else{
         cout<<"Unable to open file"<<endl;
      }
      
      return head;
   
   
   
   
   
   
   }
   template <typename T >
   istream& operator>>( istream& file,  Audio<T,2>& N ){
   
      if(file){
      
         file.seekg (0, file.end);
         int size = file.tellg();
         file.seekg (0, file.beg);
         
         int length = size/sizeof(T);
         N.data.resize(length);
         N.length = length;
         N.channels = 1;
         N.bitcount = sizeof(T);
         
        
         T unit;// 
         for(auto i=N.data.begin(); i!=N.data.end(); ++i){
         
               
            file.read((char*)&(i->first),1);  
               
            file.read((char*)&(i->second),1);      }
      
         if (file)
            std::cout << "all characters read successfully."<<endl;
         else
            std::cout << "error: only some ints could be read"<<endl;
         
         
      
         
        
        
        
      
      }
      else{
         cout<<"Unable to open file, ensure correct filename"<<endl;	
         	
      } 
      return file;  
   }
      
   template<typename T >
   bool Audio<T,2>::operator==(const Audio<T,2>& N) {
      if(length!=N.length| samplingRate != N.samplingRate | bitcount != N.bitcount| channels!= N.channels)
         return false;
      
      for(int i = 0; i< length; i++){
         if((data[i].first!= N.data[i].first)||(data[i].second!= N.data[i].second))
            return false;
      
      }
      return true;
   }
 
   
   template<typename T >
     pair<T,T> Normalise<T,2>::operator()(pair<T,T> in){
      long check = (long)(in.first * f.first/rms.first );
      if(check > (1<<sizeof(T))){
         check = (1<<sizeof(T));
      }
      long check1 = (long)(in.second * f.second /rms.second);
      if(check1 > (1<<sizeof(T))){
         check1 = (1<<sizeof(T));
      }
         
      return make_pair(T(check), T(check1));
   }
   



   
}

