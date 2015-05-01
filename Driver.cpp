#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utilit>
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
	}else{
      
            if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-add")==0)||string(argv[7]).compare("-add")==0){
            //addition.
            bool outfile = string(argv[7]).compare("-o")==0;
         string stra= string(argv[(outfile?10:8)]);
         string strb = string(argv[(outfile?11:9)]);
         cout<<"Creating first audio"<<endl;
         Audio a(stra);
         
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
      }else   if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-cat")==0)||string(argv[7]).compare("-cat")==0){
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
      }else if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-cut")==0)||string(argv[7]).compare("-cut")==0){
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
         pair<int, int> f = make_pair(r1, r2);
         
         
         
         Audio slice = a ^f;
         cout<<"Done"<<endl;
         string c = string(argv[6]);
         string channels = (c.compare("1")==0)?"mono":"stereo";
         string name = outfile?string(argv[8]):"out";
         
         
         slice.save(name + "_"+ string(argv[2])+ "_"+  string(argv[4])+ "_"+ channels+".raw");
         return 0;
      }else if((string(argv[7]).compare("-o")==0  && string(argv[9]).compare("-cut")==0)||string(argv[7]).compare("-cut")==0){
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

      else{
         cout<<"Enter correct format of commands"<<endl;
         cout<<"imageops -a l1 l2"<<endl;
         cout<<"imageops -s l1 l2"<<endl;
         cout<<"imageops -i l1"<<endl;
         cout<<"imageops -l l1 l2"<<endl;
         cout<<"imageops -t l1 f"<<endl;
          cout<<"imageops -f l1 g"<<endl;
         return 1;
      }
      
   }
   
  
  
   
     
}  
  