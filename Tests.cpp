#include "Audio.h"
#include <stdlib.h>
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"

using namespace MSHIMA001;
using namespace std;

/*Move and copy semantics
• Iterator and its operators (including boundary conditions)
• Thresholding, inverting and masking operator overloads
• Addition and subtraction of images. Ensure that the pixels are clamped
appropriately.
• [optionally] the filtering operator. Take special care to test the boundary
conditions*/
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
      REQUIRE(calcr == r);
      
      
      
      //normalise
      a1.rev(); //return to original audio
      
      vector<int8_t> v8{3*4, 127,23*4,-127,12*4,4*4};

      Audio<int8_t , 1> a8(1, 8, 2, v8);
      
      Audio<int8_t, 1>  norm  = a1.norm(make_pair(4*r, 4*r)); 
      
     REQUIRE(norm == a8);

      //fade in+ copy constructor
     
      vector<int8_t> v10{0, 19, 8, -33, 7, 3, 4, 60, 43, -70, 34, 12};
      Audio<int8_t , 1> a10(1, 8, 2, v10);
      
       Audio<int8_t , 1> faded(a4);
       faded.fadein(4);
      
       
      
     REQUIRE(faded == a10);
      
      //fade out
}


