#include "XMLWriter.h"
#include <expat.h>
#include <deque>

struct CXMLWriter::SImplementation{

};

CXMLWriter :: CXMLWriter(std::shared_ptr< CDataSink > sink){
   
}

CXMLWriter:: ~CXMLWriter(){

}

bool CXMLWriter::Flush(){
    return 0;
}

bool CXMLWriter::WriteEntity(const SXMLEntity &entity){
    return 0;
}