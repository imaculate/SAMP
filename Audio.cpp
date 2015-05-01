#include "Audio.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstlib>
#include <memory>
#include "Audio.h"


using namespace std;
namespace MSHIMA001{


Audio::Audio(int w, int h, unsigned char* buffer):width(w), height(h){
   
  
   
   data.reset(buffer);
 
   
}


      
      

Audio::Audio( string fileName){
   load(fileName);
   
      
      
}


Audio::~Audio(){ // destructor

      
      
      
   data = nullptr;
   height = width = 0;
      
      
   

   
   
}
   
   //copy constructor
Audio::Audio(const Audio& N):width(N.width), height(N.height){
   cout<<"In copy constructor"<<endl;
   cout<<"allocating memory"<<endl;
 
   unsigned char* buffer  = new unsigned char[N.width*N.height];
  
   
        
   for(int j =0; j< height*width; j++){
      
            
     
      buffer[j] =  N.data[j];
            
            
            
         
   }
          
   cout<<" done allocating memory"<<endl;
   
   data.reset(buffer);

}
   
   //move constructor
Audio::Audio(Audio&& N): width(N.width), height(N.height){
cout<<"In move "<<endl;



   
   unsigned char* buffer  = new unsigned char[N.width*N.height];
   for(int j =0; j< height*width; j++){
      
            
     
      buffer[j] =  N.data[j];
            
            
            
         
   }
          
  
   
   data.reset(buffer);

      
   N.height = N.width = 0;
   N.data = nullptr;
   
}
   
   //assignment operator
   
Audio& Audio::operator=(const Audio& N ){
   if(this == &N)
      return *this;
      
 
   
   if(data != nullptr){
     
      data = nullptr;
      
   }
   
        
   width = N.width;
   height  = N.height;
   unsigned char* buffer = new unsigned char[width*height];
         
   for(int j =0; j< height*width; j++){
            
          
      buffer[j] =  N.data[j];
            
            
            
         
   }
          
     

   
   data.reset(buffer);


   
   return *this;
      
}
   //move assignment operator.
Audio& Audio::operator=(Audio&& N){
cout<<"in move op"<<endl;
   if(this == &N)
      return *this;
      
   
   if(data != nullptr){
     
      data = nullptr;
   }

      
   width = N.width;
   height  = N.height;
    unsigned char* buffer = new unsigned char[width*height];
         
   for(int j =0; j< height*width; j++){
            
          
      buffer[j] =  N.data[j];
            
            
            
         
   }
          
     

   
   data.reset(buffer);
   
   N.data = nullptr;
   N.height = N.width = 0;
   
   return *this;
}
   
   //method to read input files
bool  Audio::load(std::string fileName){

   int  w, h;
 
   ifstream file(fileName , ios::in |ios::binary);
   string line;
   
   if (file.is_open()) {
      getline (file,line);
      
   
      cout<<"reading header info"<<endl;
      while(line.compare("255")!=0){
        
         if(line.at(0)!='#'){
         
            
            if(line.compare("P5")!=0){
               cout<<line<<endl;
               istringstream iss(line);
            
               iss >> h;
               iss >> w;
            
               width = w;
               height =  h;
            }
            
         }
         getline(file ,line);
         
         cout<<line<<endl;
      }
      
      cout<<"height "<<height<<"width "<< width<<endl;
      int64_t l = h*w;
      cout<<l<<endl;
        
      data.reset(new unsigned char[width*height]);
  //    unsigned char buffer[l];
   
     skipws(file);
         
      cout<<"Done with header info"<<endl;
      file.read((char*)&data[0], w*h);
        if (file)
      std::cout << "all characters read successfully."<<file.gcount()<<endl;
    else
      std::cout << "error: only " << file.gcount() << " could be read"<<endl;
         
         
       
         
    //   data.reset(buffer);
      
     
        
          
      file.close();
        
      return true;
        
      
   }
   else{
      cout<<"Unable to open file, ensure correct filename"<<endl;	
      return false;	
   }

               
   
      
              
  
   

      

}
void Audio::save(std::string fileName ){
   cout<<"saving"<<endl;
   ofstream head(fileName, ios::out|ios::binary);
   if(head){
      head<<"P5"<<endl;
      head<<"# this is result image saved!"<<endl;
      head<< height<< " "<< width<< endl;
      head<<"255"<<endl;
    
      
       
      unsigned char byte;// = data.get();
      for(auto i=this->begin();i!=end();++i){
         //cout<<int(*i)<<" ";
         byte  = *i;
         head.write((char*)&byte,1);
      }
      
      
    
      head.close();
   }
   else{
      cout<<"Unable to open file"<<endl;
   }


     
   
}
   
Audio::Iterator Audio::begin(void) const{ // etc
   return  Iterator(data.begin());

       
   
}
Audio::Iterator Audio::end(void) const{
   return Iterator(data.end());
}
   
Audio Audio::operator+(const Audio& N ){;
   cout<<"Adding"<<endl;
  
   cout<<"copy constructiong"<<endl;
   if(N.height != height || N.width != width ){
      cerr<< "Can't add these arrs, dimensions don't match"<<endl;
      return *this;
   }
    Audio temp(*this);//copy constructor
   
   cout<<"iterators creating"<<endl;
   Audio::Iterator beg = temp.begin(), end = temp.end();
   Audio::Iterator inStart = N.begin(), inEnd = N.end();
   cout<<"iterators created"<<endl;

   while ( beg != end) { 
   
      int check = (*beg + *inStart);
      if(check> 255){
         check = 255;
      }
         
   
      *beg = check; 
   
   ++beg;
   ++inStart;
   } 

   
   
   return temp;
      
      
   
}
Audio operator|(const Audio& N ){


}
Audio operator^(const Audio& N ){


}
Audio operator*(pair<float, float> F){


}

ostream& operator<<(ostream& head, const Audio& N ){


   if(head){
      head<<"P5"<<endl;
      head<<"# this is result image saved!"<<endl;
      head<< N.height<< " "<< N.width<< endl;
      head<<"255"<<endl;
    
      
       
      unsigned char byte;// = data.get();
      for(auto i=N.begin();i!=N.end();++i){
         //cout<<int(*i)<<" ";
         byte  = *i;
         head.write((char*)&byte,1);
      }
      
      
    
     
      return head;
   }
   else{
      cout<<"Unable to open file"<<endl;
   }



   
   
   
}
istream& operator>>( istream& file,  Audio& N ){
    string line;
    int h,w;
   
   if (file) {
      getline (file,line);
      
   
      cout<<"reading header info"<<endl;
      while(line.compare("255")!=0){
        
         if(line.at(0)!='#'){
         
            
            if(line.compare("P5")!=0){
               cout<<line<<endl;
               istringstream iss(line);
            
               iss >> h;
               iss >> w;
            
               N.width = w;
               N.height =  h;
            }
            
         }
         getline(file ,line);
         
         cout<<line<<endl;
      }
      
      cout<<"height "<<N.height<<"width "<< N.width<<endl;
      int64_t l = h*w;
      cout<<l<<endl;
        
      N.data.reset(new unsigned char[N.width*N.height]);
  //    unsigned char buffer[l];
   
     skipws(file);
         
      cout<<"Done with header info"<<endl;
      file.read((char*)(&(N.data[0])), w*h);
        if (file)
      std::cout << "all characters read successfully."<<file.gcount()<<endl;
    else
      std::cout << "error: only " << file.gcount() << " could be read"<<endl;
         
         
       
         
    //   data.reset(buffer);
      
     
        
          
    
        
      return file;
        
      
   }
   else{
      cout<<"Unable to open file, ensure correct filename"<<endl;	
      return file;	
   }

               
   
      
              
  
   

   
}

bool MSHIMA001::Audio::operator==(const Audio& N) {
   if(sizeof(N.data.get())!= sizeof(data.get()))
      return false;
      
   for(int i = 0; i< sizeof(data.get()); i++){
      if(data[i]!= N.data[i])
         return false;
      
   }
   return true;
}
   
}