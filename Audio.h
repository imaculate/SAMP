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
      int length; //length of file.
      
      
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
      
      
      Audio rev();
      double rms();
      Audio norm(pair<float, float> f);
      /*void fadein(double n);
      void fadeout(double n);*/
  
     };
     
     template<typename T, int channels>
     class Normalise{
         private:
            float f;
            T in;
        public:
            Normalise(float out);
            T operator()(void);
            
         
     
     };
     
     
     
     
     
     
     /*template<typename T>
     class Normalise<2>{
         private:
            float f;
            pair<T,T> in;
        public:
            Normalise(float out):f(out);
            pair<T,T> operator()();
            
         
     
     };*/
 



     //template<> class Audio<pair<T,T>>

 }
#endif