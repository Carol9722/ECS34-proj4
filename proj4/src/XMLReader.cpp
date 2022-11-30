#include "XMLReader.h"
#include "StringUtils.h"
#include <expat.h>
#include <deque>
#include <iostream>

struct CXMLReader::SImplementation{
    std::shared_ptr< CDataSource > DSource;
    //std::string str = *DSource;
    XML_Parser DParser;
    std::deque<SXMLEntity> DEntities;

    void StartElement(const XML_Char *name, const XML_Char **atts){
        SXMLEntity NewEntity;
        size_t Index = 0;
        NewEntity.DNameData = name;
        while(atts[Index]){
            NewEntity.SetAttribute(atts[Index],atts[Index+1]);
            Index += 2;
        }
        NewEntity.DType = SXMLEntity::EType::StartElement;
        DEntities.push_back(NewEntity);
    };

    void EndElement(const XML_Char *name){
        SXMLEntity NewEntity;
        NewEntity.DNameData = name;

        NewEntity.DType = SXMLEntity::EType::EndElement;
        DEntities.push_back(NewEntity);
        //std::cout<<NewEntity<<std::endl;
    };

    void CharacterData(const XML_Char *s, int len){
        SXMLEntity NewEntity;
        //NewEntity.DNameData = std::string (s,len);
        std::string str;
        for(int i= 0;i<len;i++){
            str.push_back(s[i]);
        }
        for(int i = 0; i<len;i++){
            if (str[i]=='|'){
                str[i]= '&';
            }
        }
        std::string newstring;
        newstring = StringUtils::Replace(str,"&amp;","&");
        str = StringUtils::Replace(newstring,"&quot;","\"");
        newstring = StringUtils::Replace(str,"&apos;","'");
        str = StringUtils::Replace(newstring,"&lt;","<");
        newstring = StringUtils::Replace(str,"&gt;",">");
        //std::cout<<"FAKESTRING ="<<fakestr<<std::endl;

        NewEntity.DNameData = newstring;
        //std::cout<<"RANDOMString"<<std::endl;
        //std::cout<<len<<std::endl;

       // std::cout<<NewEntity.DNameData<<std::endl;
        
        NewEntity.DType = SXMLEntity::EType::CharData;
        DEntities.push_back(NewEntity);
        
    };

    static void StartElementCallback(void *userData, const XML_Char *name, const XML_Char **atts){
        SImplementation *ReaderImplementation = (SImplementation *)userData;
        ReaderImplementation->StartElement(name,atts);
    };

    static void EndElementCallback(void *userData, const XML_Char *name){
        SImplementation *ReaderImplementation = (SImplementation *)userData;
        ReaderImplementation->EndElement(name);
    };

    static void CharacterDataCallback(void *userData, const XML_Char *s, int len){
        SImplementation *ReaderImplementation = (SImplementation *)userData;
        ReaderImplementation->CharacterData(s,len);
    };

    SImplementation(std::shared_ptr< CDataSource > src){
        DSource = src;
        //std::cout<<"DSOURDEHere:"<<DSource<<std::endl;

        DParser = XML_ParserCreate(NULL);
        XML_SetUserData(DParser,this);
        XML_SetElementHandler(DParser,StartElementCallback,EndElementCallback);
        XML_SetCharacterDataHandler(DParser,CharacterDataCallback);
    };

    ~SImplementation(){
        XML_ParserFree(DParser);
    }

    bool End() const{
        if (DEntities.size() == 0)
        {
            return true;
        }
        else{
            return false;
        }

    };

    bool ReadEntity(SXMLEntity &entity, bool skipcdata){
        bool Done = false;
        std::shared_ptr< CDataSource > CopySource;
        CopySource = DSource;
        //std::cout<<"COPYSOURDE:"<<CopySource<<std::endl;
        //std::cout<<"DSOURDE:"<<*DSource<<std::endl;


        while(!Done){
            //std::cout<<"MADE IT OUT OF FIRST LOOP"<<std::endl;
            std::vector<char> Buffer;
            //std::cout<<"BUFFER IS: "<<Buffer[i]<<std::endl;
            if(CopySource->Read(Buffer, 4000)){//128
                //std::cout<<"??????????"<<std::endl;
                int charchecker =0;
                for (int i = 0;i<Buffer.size();i++){
                    //std::cout<<"BUFFER WAS: "<<Buffer[i]<<std::endl;
                    if(Buffer[i]=='<'){
                        charchecker = 0;
                    }
                    if (Buffer[i]=='>'){
                        charchecker = 1;
                    }
                    if (Buffer[i]=='&'&&charchecker==1){
                        Buffer[i]='|';
                    }
                    //std::cout<<"BUFFER ISNOW: "<<Buffer[i]<<std::endl;
                }
                XML_Parse(DParser,Buffer.data(),Buffer.size(),DSource->End());
                //std::cout<<"LOOP ENDS AT PARSE"<<std::endl;/*
            }
            
            if(!DEntities.empty()){
                while(skipcdata == true)
                {
                    if (DEntities.front().DType ==  SXMLEntity::EType::CharData){
                        DEntities.pop_front();
                        continue;
                    }
                    else{
                        entity = DEntities.front();
                        DEntities.pop_front();
                        Done = true;
                        return true;  
                    }  
                }
               
                entity = DEntities.front();
                DEntities.pop_front();
               // std::cout<<"MADE IT OUT OF SECOND LOOP"<<std::endl;


                Done = true;
                return true;
                
            }
        
     
        }
        
    
    };

};

        
CXMLReader::CXMLReader(std::shared_ptr< CDataSource > src){
    DImplementation = std::make_unique<SImplementation>(src);
}

CXMLReader::~CXMLReader(){
}

bool CXMLReader::End() const{
    return DImplementation->End();
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata){
    return DImplementation->ReadEntity(entity,skipcdata);
}
