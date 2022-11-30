#include "DijkstraPathRouter.h"
#include <memory>

struct CDijkstraPathRouter::SImplementation{

    SImplementation(){

    };

    std::size_t VertexCount() const{

    };

    TVertexID AddVertex(std::any tag){

    };
    
    std::any GetVertexTag(TVertexID id) const{

    };
    
    bool AddEdge(TVertexID src, TVertexID dest, double weight, bool bidir = false) {

    };
    
    bool Precompute(std::chrono::steady_clock::time_point deadline) {

    };

    double FindShortestPath(TVertexID src, TVertexID dest, std::vector<TVertexID> &path) {

    };

}

CDijkstraPathRouter::CDijkstraPathRouter(){
    DImplementation = std::make_unique<SImplementation>;

};

CDijkstraPathRouter::~CDijkstraPathRouter(){
    
};

std::size_t CDijkstraPathRouter::VertexCount(){
    return DImplementation->VertexCount();
};

TVertexID CDijkstraPathRouter::AddVertex(std::any tag){
    return DImplementation->AddVertex(std::any tag);
};

std::any CDijkstraPathRouter::GetVertexTag(TVertexID id){
    return DImplementation->GetVertexTag(TVertexID id);
};

bool CDijkstraPathRouter::AddEdge(TVertexID src, TVertexID dest, double weight, bool bidir = false){
    return DImplementation->AddEdge(TVertexID src, TVertexID dest, double weight, bool bidir = false);
};

bool CDijkstraPathRouter::Precompute(std::chrono::steady_clock::time_point deadline) {
    return DImplementation->Precompute(std::chrono::steady_clock::time_point deadline);
};

double CDijkstraPathRouter::FindShortestPath(TVertexID src, TVertexID dest, std::vector<TVertexID> &path) {
    return DImplementation->FindShortestPath(TVertexID src, TVertexID dest, std::vector<TVertexID> &path);
};