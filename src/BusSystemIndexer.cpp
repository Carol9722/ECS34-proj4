#include "BusSystemIndexer.h"
#include "BusSystem.h"
#include <memory>
#include <string>
#include <iostream>

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
        return nullptr;
    };

    std::shared_ptr<SRoute> SortedRouteByIndex(std::size_t index) const {
        return BusSystem->RouteByIndex(index);
    };

    std::shared_ptr<SStop> StopByNodeID(TNodeID id) const {
        return BusSystem->StopByID(id);
    };

    bool RoutesByNodeIDs(TNodeID src, TNodeID dest, std::unordered_set<std::shared_ptr<SRoute> > &routes) const {
        return 0;
    };
    bool RouteBetweenNodeIDs(TNodeID src, TNodeID dest) const {
        return 0;
    };
};

CBusSystemIndexer::CBusSystemIndexer(std::shared_ptr<CBusSystem> bussystem){
    DImplementation = std::make_unique<SImplementation>(bussystem);
};

CBusSystemIndexer::~CBusSystemIndexer(){
    
};

std::size_t CBusSystemIndexer::StopCount() const noexcept {
    return DImplementation->StopCount();
};

std::size_t CBusSystemIndexer::RouteCount() const noexcept {
    return DImplementation->RouteCount();
};

std::shared_ptr<CBusSystem::SStop> CBusSystemIndexer::SortedStopByIndex(std::size_t index) const noexcept {
    return DImplementation->SortedStopByIndex(index);
};

std::shared_ptr<CBusSystem::SRoute> CBusSystemIndexer::SortedRouteByIndex(std::size_t index) const noexcept {
    return DImplementation->SortedRouteByIndex(index);
};

std::shared_ptr<CBusSystem::SStop> CBusSystemIndexer::StopByNodeID(TNodeID id) const noexcept {
    return DImplementation->StopByNodeID(id);
};

bool CBusSystemIndexer::RoutesByNodeIDs(TNodeID src, TNodeID dest, std::unordered_set<std::shared_ptr<CBusSystem::SRoute> > &routes) const noexcept {
    return DImplementation->RoutesByNodeIDs(src, dest, routes);
};

bool CBusSystemIndexer::RouteBetweenNodeIDs(TNodeID src, TNodeID dest) const noexcept {
    return DImplementation->RouteBetweenNodeIDs(src, dest);
};
