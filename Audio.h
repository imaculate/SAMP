#ifndef AUDIO_H
#define AUDIO_H
#include <string>
#include <cstdint>
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
template<typename T, int channels>
class Audio{
   private:
      int samplingRate;//eg 44100
      int bitcount;//8 or 16
      int channels;
      int length; //length of file.
      
      
      vector<T> data;
 
   public:
      friend ostream& operator<<(ostream& head, const Audio& N );
     
      friend istream& operator>>( istream& file,  Audio& N );
      
        bool operator==(const Audio& N);
   

     // Audio(int w, int h, unsigned char* buffer); // for unit tests.
     Audio()
      Audio( string fileName);
      Audio temp(int chan, int bit, int samp, vector<T> t );

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
      Audio operator^(const Audio& N );
      Audio operator*(pair<float, float> F);
      
      Audio sum(Audio& N);
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
            Normalise(float out):f(out);
            T operator()();
            
         
     
     };
     
     
     
     
     
     
     template<typename T>
     class Normalise<2>{
         private:
            float f;
            pair<T,T> in;
        public:
            Normalise(float out):f(out);
            pair<T,T> operator()();
            
         
     
     };
 



     //template<> class Audio<pair<T,T>>
     #include "Audio.cpp"
     }
#endif