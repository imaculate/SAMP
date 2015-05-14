#ifndef AUDIO_H
#define AUDIO_H
#include <string>
#include <cstdint>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <numeric>


using namespace std;


namespace MSHIMA001{

template <typename T, int chans>
class Audio;

template <typename T, int chans>
ostream& operator<<(ostream& head, const Audio<T,chans>& N );

template <typename T, int chans>
istream& operator>>( istream& file,  Audio<T,chans>& N );

template<typename T, int chans>
class Audio{
   private:
      int samplingRate;//eg 44100
      int bitcount;//8 or 16
      int channels;
      long length; //length of file.
      
      
      vector<T> data;
 
   public:
      
      friend ostream& operator<< <T, chans>(ostream& head, const Audio<T,chans>& N );
     
      
      friend istream& operator>><T, chans>( istream& file,  Audio<T,chans>& N );
     
   

     // Audio(int w, int h, unsigned char* buffer); // for unit tests.
     Audio();
      Audio( string fileName);
      Audio(int chan, int bit, int samp, vector<T> t );

      ~Audio(); // destructor - define in .cpp file
   
   //copy constructor
      Audio(const Audio& N);
   
   //move constructor
      Audio(Audio&& N); 
   
   //assignment operator
   
      Audio& operator=(const Audio& N );
   //move assignment operator.
   
      Audio& operator=(Audio&& N);
   
   //method to read input files
  
  
      bool  load(std::string fileName);
      void save(std::string fileName );

      Audio operator+(const Audio& N );
      Audio operator|(const Audio& N );
      Audio operator^(pair<int, int> N );
      Audio operator*(pair<float, float> F);
      bool operator==(const Audio& N);
      Audio add(Audio& N, pair<int, int>f);
      
      
      void rev();
      double rms();
      Audio norm(pair<float, float> f);
      void fadein(double n);
      void fadeout(double n);
  
     };
     
     template<typename T, int channels>
     class Normalise{
         private:
            float f;
            double rms;
            
        public:
            Normalise(float out, double r):f(out), rms(r){};
            T operator()(T in);
            
         
     
     };
     
template <typename T >
class Audio<T,2>;

template <typename T >
ostream& operator<<(ostream& head, const Audio<T,2>& N );

template <typename T >
istream& operator>>( istream& file,  Audio<T,2>& N );

template<typename T >
class Audio<T,2>{
   private:
      int samplingRate;//eg 44100
      int bitcount;//8 or 16
      int channels;
      int length; //length of file.
      
      
      vector<pair<T,T>> data;
 
   public:
      
      friend ostream& operator<< <T,2>(ostream& head, const Audio<T,2>& N );
     
      
      friend istream& operator>><T,2>( istream& file,  Audio<T,2>& N );
     
   

     // Audio(int w, int h, unsigned char* buffer); // for unit tests.
     Audio();
      Audio( string fileName);
      Audio(int chan, int bit, int samp, vector<pair<T,T>> t );

      ~Audio(); // destructor - define in .cpp file
   
   //copy constructor
      Audio(const Audio& N);
   
   //move constructor
      Audio(Audio&& N); 
   
   //assignment operator
   
      Audio& operator=(const Audio& N );
   //move assignment operator.
   
      Audio& operator=(Audio&& N);
   
   //method to read input files
  
  
      bool  load(std::string fileName);
      void save(std::string fileName );

      Audio operator+(const Audio& N );
      Audio operator|(const Audio& N );
      Audio operator^(pair<int, int> N );
      Audio operator*(pair<float, float> F);
      bool operator==(const Audio& N);
      Audio add(Audio& N, pair<int, int>f);
      
      
      void rev();
      pair<double,double> rms();
      Audio norm(pair<float, float> f);
      void fadein(double n);
      void fadeout(double n);
  
     };
     
     template<typename T>
     class Normalise<T,2>{
         private:
            pair<float,float> f;
            pair<double, double> rms;
          
        public:
            Normalise(pair<float, float> out, pair<double, double> r ):f(out),rms(r){};
            pair<T,T> operator()(pair<T,T> in);
            
         
     
     };
     



 

 }
#include "Audio.cpp"
#endif