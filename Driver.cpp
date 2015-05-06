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
      
      if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-add")==0)||string(argv[7]).compare("-add")==0){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?10:8)]);
         string strb = string(argv[(outfile?11:9)]);
         cout<<"Creating first audio"<<endl;
         vector<int> details  = loadFile(argv);
         if(details(2)==1){
            
         }
         Audio<> a(stra);
         
         cout<<"Creating second audio"<<endl;
         cout<<strb<<endl;
         Audio b(strb);
         Audio sum = a + b;
         cout<<"Done"<<endl;
         string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";
         
         
         sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;
      }
      else if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-cat")==0)||string(argv[7]).compare("-cat")==0){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?10:8)]);
         string strb = string(argv[(outfile?11:9)]);
         cout<<"Creating first audio"<<endl;
         Audio a(stra);
         
         cout<<"Creating second audio"<<endl;
         cout<<strb<<endl;
         Audio b(strb);
         Audio sum = a | b;
         cout<<"Done"<<endl;
         string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";
         
         
         sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;
      }
      else if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-cut")==0)||string(argv[7]).compare("-cut")==0){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?12:10)]);
         
         float r1, r2;
         istringstream ss1(string(argv[10]));
         ss1>>r1;
         istringstream ss2(string(argv[11]));
         ss2>>r2;
         
         
       
         cout<<"Creating first audio"<<endl;
         Audio a(stra);
         pair<float, float> f = make_pair(r1, r2);
         
         
         
         Audio amp = a * f;
         cout<<"Done"<<endl;
         string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";
         
         
         amp.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;
      }
      else if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-cut")==0)||string(argv[7]).compare("-cut")==0){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?12:10)]);
         
         int r1, r2;
         istringstream ss1(string(argv[10]));
         ss1>>r1;
         istringstream ss2(string(argv[11]));
         ss2>>r2;
         
         
       
         cout<<"Creating first audio"<<endl;
         Audio a(stra);
         pair<int, int> f = make_pair(r1, r2);
         
         
         
         Audio slice = a ^f;
         cout<<"Done"<<endl;
         string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";
         
         
         slice.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;
      }
      else  if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-rev")==0)||string(argv[7]).compare("-rev")==0){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?10:8)]);
         
         
         
       
         cout<<"Creating first audio"<<endl;
         Audio a(stra);
         Audio b = a.rev();
         
         
         
         
         cout<<"Done"<<endl;
         string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";
         
         
         b.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;
      }
      else  if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-rms")==0)||string(argv[7]).compare("-rms")==0){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?10:8)]);
         
         
         
       
         cout<<"Creating first audio"<<endl;
         Audio a(stra);
         Audio b = a.rms();
         
         
         
         
         cout<<"Done"<<endl;
         string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";
         
         
         b.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;
      }
      else  if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-rms")==0)||string(argv[7]).compare("-rms")==0){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?10:8)]);
         
         
         
       
         cout<<"Creating first audio"<<endl;
         Audio a(stra);
         double b = a.rms();
          
         
         
         
         
         cout<<"Done"<<endl;
         cout<< "The rms value is "<< b<<endl;
         
      }
      else if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-norm")==0)||string(argv[7]).compare("-norm")==0){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?12:10)]);
         
         float r1, r2;
         istringstream ss1(string(argv[10]));
         ss1>>r1;
         istringstream ss2(string(argv[11]));
         ss2>>r2;
         
         
       
         cout<<"Creating first audio"<<endl;
         Audio a(stra);
         pair<float, float> f = make_pair(r1, r2);
        
         
            
         
         
         Audio norm = a.norm(f);
         cout<<"Done"<<endl;
         string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";
         
         
         norm.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;
      }
      else if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-radd")==0)||string(argv[7]).compare("-radd")==0){
            //addition.
         bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?12:10)]);
         string strb = string(argv[(outfile?13:11)]);
         
         float r1, r2;
         istringstream ss1(string(argv[10]));
         ss1>>r1;
         istringstream ss2(string(argv[11]));
         ss2>>r2;
         
         
       
         cout<<"Creating first audio"<<endl;
         Audio a(stra);
         
         
         cout<<"Creating second audio"<<endl;
         Audio b(stra);
         
         pair<float, float> f = make_pair(r1, r2);
        
         
            
         
         
         Audio sum  = a.add(b,f);
         
         cout<<"Done"<<endl;
         string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";
         
         
         sum.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;
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

"samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName] [<ops>] Soundfile [SoundFile2]"
vector<int> loadfile(char*[] args){
   vector<int> data(3);
   int sampleRate, bitCount, noChannels;
   
   string samp = string(args[2]);
   istringstream ss(samp);
   ss >> sampleRate;
   data.push_pack(sampleRate);
   
   string bits = string(args[4]);
   istringstream ss1(bits);
   ss1 >> bitCount;
   data.push_pack(bitCount);
   
   
   string chan  = string(args[6]);
   istringstream ss2(chan);
   ss2 >>  noChannels;
   data.push_pack(noChannels);
   
   return data;

   
   
   
}
