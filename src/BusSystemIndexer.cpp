#include "BusSystemIndexer.h"

struct CBusSystemIndexer::SImplementation{
    std::shared_ptr<CBusSystem> BusSystem;

    SImplementation(std::shared_ptr<CBusSystem> bussystem){
        BusSystem = bussystem;
    };

    std::size_t StopCount() const {
        return BusSystem->StopCount();
    };
    std::size_t RouteCount() const {
        return BusSystem->RouteCount();

    };
    std::shared_ptr<SStop> SortedStopByIndex(std::size_t index) const {
        for ()
    };
    std::shared_ptr<SRoute> SortedRouteByIndex(std::size_t index) const {
        return BusSystem->StopByIndex(index);
    };
    std::shared_ptr<SStop> StopByNodeID(TNodeID id) const {
        return BusSystem->StopByID(id);
    };
    bool RoutesByNodeIDs(TNodeID src, TNodeID dest, std::unordered_set<std::shared_ptr<SRoute> > &routes) const {
        
    };
    bool RouteBetweenNodeIDs(TNodeID src, TNodeID dest) const {

    };
};

CBusSystemIndexer::CBusSystemIndexer(std::shared_ptr<CBusSystem> bussystem){
    DImplementation = std::make_unique<SImplementation>(std::shared_ptr<CBusSystem> bussystem);
};

CBusSystemIndexer::~CBusSystemIndexer(){
    
};

std::size_t CBusSystemIndexer::StopCount() const {
    return DImplementation->StopCount();
};

std::size_t CBusSystemIndexer::RouteCount() const {
    return DImplementation->RouteCount();
};

std::shared_ptr<SStop> CBusSystemIndexer::SortedStopByIndex(std::size_t index) const {
    return DImplementation->SortedStopByIndex(index);
};

std::shared_ptr<SRoute> CBusSystemIndexer::SortedRouteByIndex(std::size_t index) const {
    return DImplementation->SortedRouteByIndex(index);
};

std::shared_ptr<SStop> CBusSystemIndexer::StopByNodeID(TNodeID id) const {
    return DImplementation->StopByNodeID(id);
};

bool CBusSystemIndexer::RoutesByNodeIDs(TNodeID src, TNodeID dest, std::unordered_set<std::shared_ptr<SRoute> > &routes) const {
    return DImplementation->RoutesByNodeIDs(src, dest, routes);
};

bool CBusSystemIndexer::RouteBetweenNodeIDs(TNodeID src, TNodeID dest) const {
    return DImplementation->RouteBetweenNodeIDs(src, dest);
};
