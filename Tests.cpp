#include "Audio.h"
#include <stdlib.h>
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"

using namespace MSHIMA001;
using namespace std;


TEST_CASE( "testing mono audio files ", "8 bit" ) {
   
      
      vector<int8_t> v1{3, 78, 23, -67, 12, 4};
      Audio<int8_t , 1> a1(1, 8, 2, v1);
      
        
      vector<int8_t> v2{5, 60, 43, -70, 34, 12};
      Audio<int8_t , 1> a2(1, 8, 2, v2);
      
      
            
      //additon
      //expected sum 
        vector<int8_t> v3{8, 127, 66, -127, 46, 16};

      Audio<int8_t , 1> a3(1, 8, 2, v3);

      Audio<int8_t, 1>  sum  = a1 + a2;
      REQUIRE(sum == a3);

      
      //concatenate
     
        vector<int8_t> v4{3, 78, 23, -67, 12, 4, 5, 60, 43, -70, 34, 12};

      Audio<int8_t , 1> a4(1, 8, 2, v4);

      Audio<int8_t, 1>  cat  = a1|a2; 
      
      REQUIRE(cat == a4);

      
      
      //cut
      vector<int8_t> v5{3, 78, 23, 5, 60, 43, -70, 34, 12};

      Audio<int8_t , 1> a5(1, 8, 2, v5);
      
      Audio<int8_t, 1>  cut  = cat^make_pair(3,5); 
      
      REQUIRE(cut == a5);
      //range add
      vector<int8_t> v6{3, 78,66,-127,46,4};

      Audio<int8_t , 1> a6(1, 8, 2, v6);
      
      Audio<int8_t, 1>  radd  = a1.add(a2,make_pair(2,4)); 
      
      REQUIRE(radd == a6);
      
      //volume factor
      
      vector<int8_t> v7{2, 62,18,-53,9,3};

      Audio<int8_t , 1> a7(1, 8, 2, v7);
      
      Audio<int8_t, 1>  vol  = a1*make_pair(0.8, 0.8); 
      
      REQUIRE(vol == a7);
            
      //reverse
      
      vector<int8_t> v9{4, 12,-67,23,78,3};

      Audio<int8_t , 1> a9(1, 8, 2, v9);
      
      a1.rev(); 
      
      REQUIRE(a1 == a9);
      
      //rms
      
      double r = a1.rms();
      
      long prod = 0;
      for(auto i = 0; i< 6; i++){
         prod += v1[i]*v1[i];
      }
      double calcr = sqrt(prod/6);
      REQUIRE((long)calcr ==(long) r);
      
      
      
      //normalise
      a1.rev(); //return to original audio
      
      vector<int8_t> v8{3*4, 127,23*4,-127,12*4,4*4};

      Audio<int8_t , 1> a8(1, 8, 2, v8);
      
      Audio<int8_t, 1>  norm  = a1.norm(make_pair(4*r, 4*r)); 
      
     REQUIRE(norm == a8);

      //fade in+ copy constructor
     
      vector<int8_t> v10{0, 20, 8, -33, 7, 3, 4, 60, 43, -70, 34, 12};
      //{3, 78, 23, -67, 12, 4, 5, 60, 43, -70, 34, 12};
      Audio<int8_t , 1> a10(1, 8, 2, vector<int8_t>{0, 19, 8, -33, 7, 3, 4, 60, 43, -70, 34, 12});

      
       Audio<int8_t , 1> faded(a4);
       faded.fadein(4);
      
       
      
     //REQUIRE(faded == a10);
      
      //fade out
}
TEST_CASE("testing stereo files", "16 bit"){
    
       vector<pair<int16_t,int16_t>> v1{make_pair(3, -90),make_pair(78, 150), make_pair(23, -1), make_pair(-67, 12), make_pair(12, 96), make_pair(4, -200)};
      Audio<int16_t , 2> a1(2, 16, 2, v1);
      
       
      
      
            
      //additon
      //expected sum 
        vector<pair<int16_t,int16_t>> v3{make_pair(6, -180),make_pair(156, 300), make_pair(46, -2), make_pair(-134, 24), make_pair(24, 192), make_pair(8, -400)};

      Audio<int16_t , 2> a3(2, 16, 2, v3);

      Audio<int16_t, 2>  sum  = a1 + a1;
      REQUIRE(sum == a3);

      
      //concatenate
     
        vector<pair<int16_t,int16_t>> v4{make_pair(3, -90),make_pair(78, 150), make_pair(23, -1), make_pair(-67, 12), make_pair(12, 96), make_pair(4, -200), make_pair(3, -90),make_pair(78, 150), make_pair(23, -1), make_pair(-67, 12), make_pair(12, 96), make_pair(4, -200)};


      Audio<int16_t , 2> a4(2, 16, 2, v4);

      Audio<int16_t, 2>  cat  = a1|a1; 
      
      REQUIRE(cat == a4);

      
      
      //cut
      vector<pair<int16_t,int16_t>> v5{make_pair(3, -90),make_pair(78, 150), make_pair(23, -1),make_pair(3, -90), make_pair(78, 150), make_pair(23, -1), make_pair(-67, 12), make_pair(12, 96), make_pair(4, -200)};
      

      Audio<int16_t , 2> a5(2, 16, 2, v5);
      
      Audio<int16_t, 2>  cut  = cat^make_pair(3,5); 
      
      REQUIRE(cut == a5);
      //range add
      vector<pair<int16_t,int16_t>> v6{make_pair(3, -90),make_pair(78, 150),  make_pair(46, -2), make_pair(-134, 24), make_pair(24, 192), make_pair(4, -200)};


      Audio<int16_t , 2> a6(2, 16, 2, v6);
      
      Audio<int16_t, 2>  radd  = a1.add(a1,make_pair(2,4)); 
      
      REQUIRE(radd == a6);
      
      //volume factor
      
      vector<pair<int16_t,int16_t>> v7{make_pair(2, -45),make_pair(62, 75), make_pair(18, 0), make_pair(-53, 6), make_pair(9, 48),  make_pair(3, -100)};

      Audio<int16_t , 2> a7(2, 16, 2, v7);
      
      Audio<int16_t, 2>  vol  = a1*make_pair(0.8, 0.5); 
      
      REQUIRE(vol == a7);
            
      //reverse
      
      vector<pair<int16_t,int16_t>> v9{  make_pair(4, -200), make_pair(12, 96) ,make_pair(-67, 12),  make_pair(23, -1), make_pair(78, 150),  make_pair(3, -90)};


      Audio<int16_t , 2> a9(2, 16, 2, v9);
      
      a1.rev(); 
      
      REQUIRE(a1 == a9);
      
           a1.rev(); //return to original audio
      
      //rms
      
      pair<double, double> r = a1.rms();
      
      long long int prod1 = 0;
      long long int prod2 = 0;
      
      for(auto i = 0; i< 6; i++){
         prod1 += v1[i].first*v1[i].first;
         
         prod2 += v1[i].second*v1[i].second;

      }
      double r1 = sqrt(prod1/6);
         double r2 = sqrt(prod2/6);
         pair<double, double> calcr = make_pair(r1,r2);
         
      REQUIRE((long)calcr.first == (long)r.first); //decimal calculations are not accuate
       REQUIRE((long)calcr.second == (long)r.second);
      
      
      
      //normalise
 
      
      vector<pair<int16_t,int16_t>> v8{make_pair(3*4, -360),make_pair(312, 600), make_pair(92, -4), make_pair(-268, 48), make_pair(48, 384), make_pair(16, -800)};

      Audio<int16_t , 2> a8(2, 16, 2, v8);
      
      Audio<int16_t, 2>  norm  = a1.norm(make_pair(4*r.first, 4*r.second)); 
      
     REQUIRE(norm == a8);

             
      
     //REQUIRE(faded == a10);
      
      //fade out 
      }


