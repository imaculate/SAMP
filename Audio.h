#ifndef AUDIO_H
#define AUDIO_H
#include <memory>
#include <string>
#include <iostream>

using namespace std;


namespace MSHIMA001{
template<typename T>
class Audio{
   private:
      int rate;
      vector<T> data;
 
   public:
      friend ostream& operator<<(ostream& head, const Audio& N );
     
      friend istream& operator>>( istream& file,  Audio& N );
      
        bool operator==(const Audio& N);
   

      Audio(int w, int h, unsigned char* buffer); // default constructor - define in .cpp
      Audio( string fileName);
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
   Audio operator!();
      bool  load(std::string fileName);
      void save(std::string fileName );
      
      class Iterator{
      private:
         T* ptr;
         
      // grant private access to Audio class functions
         friend class Audio;
      // construct only via Audio class (begin/end)
      
         Iterator(T *p);
      
      public:
       //copy construct is public
         Iterator(const Iterator& N);
    
         // define overloaded ops: *, ++, --, =
         //destructor
         ~Iterator();
         //move constructor
         Iterator(Iterator&& N); 
      
         //assignment operator
      
         Iterator& operator=(const Iterator& N );
         //move assignment operator.
      
         Iterator& operator=(Iterator&& N);
         
         
         
         //++ operator
         const Iterator& operator ++();
         const Iterator& operator --();
          unsigned char& operator *();
         bool operator !=( const Iterator& N);
         Iterator&  operator+=(int n);
         
        //Iterator&  operator=(int&& N );
         
          
      
          
      // other methods for Iterator
      };
      

   
      Audio::Iterator begin(void) const; // etc
      Audio::Iterator end(void) const;
   
      Audio operator+(const Audio& N );
      Audio operator|(const Audio& N );
      Audio operator^(const Audio& N );
      Audio operator*(pair<float, float> F);
   
   
         
   
   
   
    
   
   
   
         
     
     };
     
     //template<> class Audio<pair<T,T>>
     }
#endif