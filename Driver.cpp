#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include "Audio.h"




using namespace std;
using namespace MSHIMA001;
//method used to extract initial string.


int main(int argc, char**  argv) {
  
   
   if(argc<10){
      //error handling.
      cout<<"Enter correct format of commands"<<endl;
      cout<<"samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName] [<ops>] Soundfile [SoundFile2]"<<endl;
      cout<<"where ops is"<<endl;
      cout<<"-add s1 s2"<<endl;
      cout<<"-cut r1 r2"<<endl;
      cout<<"-radd r1 r2 s1 s2"<<endl;
      cout<<"-cat s1 s2"<<endl;
      cout<<"-v r1 r2"<<endl;
      cout<<"-rev s1"<<endl;
          
      cout<<"-rms s1"<<endl;
      cout<<"-norm r1 r2"<<endl;
      cout<<"-fade in n"<<endl;
      cout<<"-fade out n"<<endl;
      return 1;
   }
   else{
      
      if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-add")==0)||(string(argv[7]).compare("-add")==0)){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?10:8)]);
         string strb = string(argv[(outfile?11:9)]);
           string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";
           cout<<"Creating first audio"<<endl;

         if( string(argv[6]).compare("1")==0  ){
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t, 1> a(stra);
                    Audio<int8_t, 1> b(strb);
                    Audio<int8_t, 1> sum;
                      sum = a + b;

         
         sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
            cout<<"Done"<<endl;
         return 0;
            }else{
               Audio<int16_t, 1> a(stra);
                Audio<int16_t, 1> b(strb);
                Audio<int16_t, 1> sum;
                  sum = a + b;
                     
         sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
            cout<<"Done"<<endl;
         return 0;
                

            }
         }else{
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t,2> a(stra);
                    Audio<int8_t,2> b(strb);
                    Audio<int8_t,2> sum;
                      sum = a + b;
                         
         sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
            cout<<"Done"<<endl;
         return 0;
            }else{
               Audio<int16_t,2> a(stra);
                Audio<int16_t,2> b(strb);
                Audio<int16_t,2> sum;
                  sum = a + b;
                     
         sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
            cout<<"Done"<<endl;
         return 0;

            }

            
         }             
     
    
      }
      else if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-cat")==0)||(string(argv[7]).compare("-cat")==0)){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?10:8)]);
         string strb = string(argv[(outfile?11:9)]);
          string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";

         cout<<"Creating first audio"<<endl;
         if( string(argv[6]).compare("1")==0  ){
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t, 1> a(stra);
                    Audio<int8_t, 1> b(strb);
                    Audio<int8_t, 1> sum;
                     sum = a | b;
         cout<<"Done"<<endl;
         sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;

            }else{
               Audio<int16_t, 1> a(stra);
                Audio<int16_t, 1> b(strb);
                Audio<int16_t, 1> sum;
                 sum = a | b;
         cout<<"Done"<<endl;
         sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;

                

            }
         }else{
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t,2> a(stra);
                    Audio<int8_t,2> b(strb);
                    Audio<int8_t,2> sum;
                     sum = a | b;
         cout<<"Done"<<endl;
         sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;

            }else{
               Audio<int16_t,2> a(stra);
                Audio<int16_t,2> b(strb);
                Audio<int16_t,2> sum;
                 sum = a | b;
         cout<<"Done"<<endl;
         sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;


            }

            
         }             
        
               }
      else if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-cut")==0)||string(argv[7]).compare("-cut")==0){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?12:10)]);
         
         float r1, r2;
         string s1,s2;
         s1 = string(argv[10]);
         istringstream ss1(s1);
         ss1>>r1;
         s2 = string(argv[11]);
         istringstream ss2(s2);
         ss2>>r2;
             string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";
         
         
       
         cout<<"Creating first audio"<<endl;
          if( string(argv[6]).compare("1")==0  ){
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t, 1> a(stra);
                  
                    Audio<int8_t, 1> amp;
                    pair<float, float> f = make_pair(r1, r2);
                   amp = a * f;
                   cout<<"Done"<<endl;

         amp.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;


            }else{
               Audio<int16_t, 1> a(stra);
                
                Audio<int16_t, 1> amp;
                pair<float, float> f = make_pair(r1, r2);
               amp = a * f;
               cout<<"Done"<<endl;

         amp.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;

      

            }
         }else{
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t,2> a(stra);
                  
                    Audio<int8_t,2> amp;
                    pair<float, float> f = make_pair(r1, r2);
                amp = a * f;
                cout<<"Done"<<endl;

         amp.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;


            }else{
               Audio<int16_t,2> a(stra);
               
                Audio<int16_t,2> amp;
                pair<float, float> f = make_pair(r1, r2);
               amp = a * f;
               cout<<"Done"<<endl;

         amp.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;



            }

            
         }             

         
                        }
      else if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-cut")==0)||string(argv[7]).compare("-cut")==0){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?12:10)]);
         
         int r1, r2;
         string s1, s2;
         s1 = string(argv[10]);
         istringstream ss1(s1);
         ss1 >> r1;
         s2 = string(argv[11]);
         istringstream ss2(s2);
         ss2 >> r2;
         
                  pair<int, int> f = make_pair(r1, r2);
                  string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";

         
       
         cout<<"Creating first audio"<<endl;
          if( string(argv[6]).compare("1")==0  ){
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t, 1> a(stra);
                    
                    Audio<int8_t, 1> slice;
                    
         slice = a ^f;
         cout<<"Done"<<endl; 
         slice.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;
            }else{
               Audio<int16_t, 1> a(stra);
                
                Audio<int16_t, 1> slice;
                
         slice = a ^f;
         cout<<"Done"<<endl; 
         slice.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;
                

            }
         }else{
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t,2> a(stra);
                    
                    Audio<int8_t,2> slice;
                    
         slice = a ^f;
         cout<<"Done"<<endl; 
         slice.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;
            }else{
               Audio<int16_t,2> a(stra);
                
                Audio<int16_t,2> slice;
                
         slice = a ^f;
         cout<<"Done"<<endl; 
         slice.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;

            }

            
         }             


         
         
      }
      else  if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-rev")==0)||(string(argv[7]).compare("-rev")==0)){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?10:8)]);
   
         
         string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";
         cout<<"Creating first audio"<<endl;
          if( string(argv[6]).compare("1")==0  ){
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t, 1> a(stra);
                   
                    Audio<int8_t, 1> b;
                     b = a.rev();
   b.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         cout<<"Done"<<endl;
         return 0;
            }else{
               Audio<int16_t, 1> a(stra);
                
                Audio<int16_t, 1> b;
                 b = a.rev();
   b.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         cout<<"Done"<<endl;
         return 0;

            }
         }else{
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t,2> a(stra);
                   
                    Audio<int8_t,2> b;
                     b = a.rev();
   b.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         cout<<"Done"<<endl;
         return 0;
            }else{
               Audio<int16_t,2> a(stra);
                
                Audio<int16_t,2> b;
                 b = a.rev();
   b.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         cout<<"Done"<<endl;
         return 0;

            }

            
         }             

         
      }
      else  if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-rms")==0)||(string(argv[7]).compare("-rms")==0)){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?10:8)]);
         
         
         
       
         cout<<"Creating first audio"<<endl;
          if( string(argv[6]).compare("1")==0  ){
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t, 1> a(stra);
                   double b = a.rms();
         cout<< "The rms of audio file is " << b <<endl;
         
         return 0;
                   
            }else{
               Audio<int16_t, 1> a(stra);
               double b = a.rms();
         cout<< "The rms of audio file is " << b <<endl;
         
         return 0;
                

            }
         }else{
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t,2> a(stra);
                   double b = a.rms();
         cout<< "The rms of audio file is " << b <<endl;
         
         return 0;
                  
            }else{
               Audio<int16_t,2> a(stra);
               double b = a.rms();
         cout<< "The rms of audio file is " << b <<endl;
         
         return 0;
           

            }

            
         }             

         
      }
      
      else if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-norm")==0)||(string(argv[7]).compare("-norm")==0)){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?12:10)]);
         
         int r1, r2;
         string sa , sb;
         sa = string(argv[10]);
         istringstream ssa(sa);
         ssa>>r1;
         sb = string(argv[11]);
         istringstream ssb(sb);
         ssb>>r2;
          pair<int, int> f = make_pair(r1, r2);

         string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";

         cout<<"Creating first audio"<<endl;
          if( string(argv[6]).compare("1")==0  ){
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t, 1> a(stra);
                   
                    Audio<int8_t, 1> norm;
                    norm = a.norm(f);
         cout<<"Done"<<endl;

         norm.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;

            }else{
               Audio<int16_t, 1> a(stra);
                
                Audio<int16_t, 1> norm;
                norm = a.norm(f);
         cout<<"Done"<<endl;

         norm.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;

            }
         }else{
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t,2> a(stra);
                    
                    Audio<int8_t,2> norm;
                    norm = a.norm(f);
         cout<<"Done"<<endl;

         norm.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;

            }else{
               Audio<int16_t,2> a(stra);
              
                Audio<int16_t,2> norm;
                norm = a.norm(f);
         cout<<"Done"<<endl;

         norm.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;


            }

            
         }             
  
               }
      else if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-radd")==0)||(string(argv[7]).compare("-radd")==0)){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?12:10)]);
         string strb = string(argv[(outfile?13:11)]);
         
         float r1, r2;
         string s1, s2;
         s1 = string(argv[10]);
         istringstream ss1(s1);
         (ss1)>>(r1);
         s2 = string(argv[11]);
         istringstream ss2(s2);
         (ss2)>>(r2);
         pair<float, float> f = make_pair(r1, r2);

         string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";

         
         
       
          if( string(argv[6]).compare("1")==0  ){
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t, 1> a(stra);
                    Audio<int8_t, 1> b(strb);
                    Audio<int8_t, 1> sum;
                    
          sum  = a.add(b,f);
         
         cout<<"Done"<<endl;
           sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;

            }else{
               Audio<int16_t, 1> a(stra);
                Audio<int16_t, 1> b(strb);
                Audio<int16_t, 1> sum;
                
          sum  = a.add(b,f);
         
         cout<<"Done"<<endl;
                  sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;


            }
         }else{
            if(string(argv[4]).compare("8")==0){
                   Audio<int8_t,2> a(stra);
                    Audio<int8_t,2> b(strb);
                    Audio<int8_t,2> sum;
                    
          sum  = a.add(b,f);
         
         cout<<"Done"<<endl;
           sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;

            }else{
               Audio<int16_t,2> a(stra);
                Audio<int16_t,2> b(strb);
                Audio<int16_t,2> sum;
                
          sum  = a.add(b,f);
         
         cout<<"Done"<<endl;
           sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;


            }

            
         }             

         
                 
         
            
         
         
                  
         
             }
      
      
      
      
      
      else{
         //error handling.
         cout<<"Enter correct format of commands"<<endl;
         cout<<"samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName] [<ops>] Soundfile [SoundFile2]"<<endl;
         cout<<"where ops is"<<endl;
         cout<<"-add s1 s2"<<endl;
         cout<<"-cut r1 r2"<<endl;
         cout<<"-radd r1 r2 s1 s2"<<endl;
         cout<<"-cat s1 s2"<<endl;
         cout<<"-v r1 r2"<<endl;
         cout<<"-rev s1"<<endl;
          
         cout<<"-rms s1"<<endl;
         cout<<"-norm r1 r2"<<endl;
         cout<<"-fade in n"<<endl;
         cout<<"-fade out n"<<endl;
         return 1;
      }
      
   }
   
  
  
   
     
}


   
   
   

