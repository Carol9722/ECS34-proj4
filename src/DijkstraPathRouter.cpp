#include "DijkstraPathRouter.h"
#include <memory>
#include <string>
#include <queue>

struct CDijkstraPathRouter::SImplementation{
    struct Vertex{
        TVertexID id;
        std::any tag;

        Vertex(std::any Vtag){
            tag = Vtag
        }

        ~Vertex(){

        }

    }
    
    SImplementation(){
        priority_queue<Vertex> pq;
    };

    std::size_t VertexCount() const{
        return pq.size();
    };

    TVertexID AddVertex(std::any tag){
        pq.push(Vertex(tag));
        return Vertex(tag)->ID();
    };
    
    std::any GetVertexTag(TVertexID id) const{
        return 0;
    };
    
    bool AddEdge(TVertexID src, TVertexID dest, double weight, bool bidir = false) {
        return 0;
    };
    
    bool Precompute(std::chrono::steady_clock::time_point deadline) {
        return 0;
    };

    double FindShortestPath(TVertexID src, TVertexID dest, std::vector<TVertexID> &path) {
        return 0;
    };

};

CDijkstraPathRouter::CDijkstraPathRouter(){
    DImplementation = std::make_unique<SImplementation>();

};

CDijkstraPathRouter::~CDijkstraPathRouter(){
    
};

std::size_t CDijkstraPathRouter::VertexCount() const noexcept{
    return DImplementation->VertexCount();
};

CPathRouter::TVertexID CDijkstraPathRouter::AddVertex(std::any tag) noexcept{
    return DImplementation->AddVertex(tag);
};

std::any CDijkstraPathRouter::GetVertexTag(TVertexID id) const noexcept{
    return DImplementation->GetVertexTag(id);
};

bool CDijkstraPathRouter::AddEdge(TVertexID src, TVertexID dest, double weight, bool bidir) noexcept{
    return DImplementation->AddEdge(src, dest, weight, bidir);
};

bool CDijkstraPathRouter::Precompute(std::chrono::steady_clock::time_point deadline) noexcept{
    return DImplementation->Precompute(deadline);
};

double CDijkstraPathRouter::FindShortestPath(TVertexID src, TVertexID dest, std::vector<TVertexID> &path) noexcept{
    return DImplementation->FindShortestPath(src, dest, path);
};