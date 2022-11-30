#include "OpenStreetMap.h"
#include <unordered_map>
#include <iostream>

struct COpenStreetMap::SImplementation{

    struct SNode : public CStreetMap::SNode{
        TNodeID ThisNodeID;
        TLocation ThisLocation;
        std::unordered_map<std::string,std::string> NodeAttributes;
        std::vector< std::string > NodeKeys;
        //somehow pass the entity here
        SXMLEntity Entity;

        ~SNode(){};
        TNodeID ID() const noexcept{
           // ThisNodeID = stoi(Entity.AttributeValue("id"));
            return ThisNodeID;
        }

        TLocation Location() const noexcept{
            /*TLocation NodeLocation;
            double lat = stod(Entity.AttributeValue("lat"));
            double lon = stod(Entity.AttributeValue("lon"));
            //TLocation NodeLocation = std::make_pair(lat,lon);
            NodeLocation.first = lat;
            NodeLocation.second = lon;*/
            return ThisLocation;

        }

        std::size_t AttributeCount() const noexcept{
            return NodeKeys.size();
        }

        std::string GetAttributeKey(std::size_t index) const noexcept{
            return index < NodeKeys.size() ? NodeKeys[index] : std::string();
        }

        bool HasAttribute(const std::string &key) const noexcept{
            return NodeAttributes.find(key) != NodeAttributes.end();
        }

        std::string GetAttribute(const std::string &key) const noexcept{
            auto Search = NodeAttributes.find(key);
            if(Search == NodeAttributes.end()){
                return std::string();
            }
            return Search->second;//first is key second is value
        }

    };

    struct SWay : public CStreetMap::SWay{
        std::vector< TNodeID > NodesOfTheWay;
        TWayID ThisWayID;
        std::unordered_map<std::string,std::string> WayAttributes;
        std::vector< std::string > WayKeys;
      

        ~SWay(){};
        TWayID ID() const noexcept{
            return ThisWayID;
        }

        std::size_t NodeCount() const noexcept{
            return NodesOfTheWay.size();
        }

        TNodeID GetNodeID(std::size_t index) const noexcept{
            return index < NodesOfTheWay.size() ? NodesOfTheWay[index] : InvalidNodeID;
        }

        std::size_t AttributeCount() const noexcept{
            //std::cout<<"KEYS SIZE"<<WayKeys.size()<<std::endl;
            return WayKeys.size();
        }

        std::string GetAttributeKey(std::size_t index) const noexcept{
            return index < WayKeys.size() ? WayKeys[index] : std::string();
        }

        bool HasAttribute(const std::string &key) const noexcept{
            return WayAttributes.find(key) != WayAttributes.end();
        }

        std::string GetAttribute(const std::string &key) const noexcept{
            auto Search = WayAttributes.find(key);

            if(Search == WayAttributes.end()){
                //std::cout<<"key not found"<<std::endl;
                return std::string();
            }
           // std::cout<<"KEY FOUNDDDD"<<std::endl;
            return Search->second;//first is key second is value
        }

    };

    std::vector< std::shared_ptr< SWay > > AllWays;
    std::unordered_map< TWayID, std::shared_ptr< SWay > > MappedWays;

    std::vector< std::shared_ptr< SNode > > AllNodes;
    std::unordered_map< TNodeID, std::shared_ptr< SNode > > MappedNodes;
   
// maybe make a vector or smth to store the parsed nodes. youre reading in data 
    SImplementation(std::shared_ptr<CXMLReader> src){
        SXMLEntity Entity;

        // check osm start first
        while(src->ReadEntity(Entity)){//while u havent hit the end element of node or way
            if(Entity.DNameData == "osm" && Entity.DType == SXMLEntity::EType::EndElement){
                break;
            }
            if(Entity.DNameData == "node" && Entity.DType == SXMLEntity::EType::StartElement ){
                std::vector< std::string > NewKeyVect;
                std::unordered_map<std::string,std::string> NewAttMap;
                //std::cout<<"LOOPLOPP"<<std::endl;
                //std::cout<<"NAME DATA: "<<Entity.DNameData<<std::endl;
                auto NewNode = std::make_shared<SNode>();
               // std::cout<<"First NOde ID "<<Entity.AttributeValue("id")<<std::endl;
                NewNode->ThisNodeID = stoi(Entity.AttributeValue("id"));//made id
                //NewNode->ThisNodeID = 1;
                //make location
                TLocation NodeLocation;
                double lat = stod(Entity.AttributeValue("lat"));
                double lon = stod(Entity.AttributeValue("lon"));
                NodeLocation.first = lat;
                NodeLocation.second = lon;
                NewNode->ThisLocation = NodeLocation;
                while(src->ReadEntity(Entity)){
                    if(Entity.DNameData == "tag"){
                        if(Entity.DType == SXMLEntity::EType::StartElement){
                            //std::cout<<"TAAAAAAAGGGGGG"<<std::endl;
                            NewKeyVect.push_back(Entity.AttributeValue("k"));
                            //std::cout<<"K IS : "<<Entity.AttributeValue("k")<<std::endl;
                            NewNode->NodeKeys = NewKeyVect;
                            //std::cout<<"ERROR"<<std::endl;

                            NewAttMap.insert({ Entity.AttributeValue("k"), Entity.AttributeValue("v") });
                            // std::cout<<"REEEEEEEEE"<<std::endl;
                            NewNode->NodeAttributes = NewAttMap;
                            //std::cout<<"FAIL LOL"<<std::endl;
                        }
                        else if(Entity.DType == SXMLEntity::EType::EndElement){
                            continue;
                        }
                    }
                    else{
                        //std::cout<<"WE BROKE OUT"<<std::endl;
                        break;
                    }
                }
                
                AllNodes.push_back(NewNode);
                MappedNodes[NewNode->ID()] = NewNode;
            }
            if(Entity.DNameData == "way" && Entity.DType == SXMLEntity::EType::StartElement){//probaby check its also startelement
                std::vector < std::string > TempKeyVect;
                std::unordered_map<std::string,std::string> TempAttMap;
                //special one
                std::vector< TNodeID > TempNodesOfTheWay;

                auto NewWay = std::make_shared<SWay>();
                //std::cout<<"PRINTING THE NODE BY INDEX "<<NodeByIndex(0)->ID()<<std::endl;
                NewWay->ThisWayID = stoi(Entity.AttributeValue("id"));//make id
                

                while(src->ReadEntity(Entity)){
                    if(Entity.DNameData == "tag"){
                        if(Entity.DType == SXMLEntity::EType::StartElement){
                            TempKeyVect.push_back(Entity.AttributeValue("k"));
                            NewWay->WayKeys = TempKeyVect;
                            //std::cout<<"ATT VALL IS"<< Entity.AttributeValue("v")<<std::endl;
                            TempAttMap.insert({ Entity.AttributeValue("k"), Entity.AttributeValue("v") });
                            NewWay->WayAttributes = TempAttMap;
                        }
                        else if(Entity.DType == SXMLEntity::EType::EndElement){
                            continue;
                        }

                    }
                    else if(Entity.DNameData == "nd"){
                        if(Entity.DType == SXMLEntity::EType::StartElement){
                            //std::cout<<"ID VALUE"<<Entity.AttributeValue("ref")<<std::endl;
                            TempNodesOfTheWay.push_back(stoi(Entity.AttributeValue("ref")));
                            NewWay->NodesOfTheWay = TempNodesOfTheWay;
                        }
                        else if(Entity.DType == SXMLEntity::EType::EndElement){
                            continue;
                        }
                        
                    }
                    else{
                        break;
                    }

                }

                // Parse rest assing id keys all that. proly in a func
                AllWays.push_back(NewWay);
                MappedWays[NewWay->ID()] = NewWay;
            }

        }
        

    }
//you acc have to implement these
    std::size_t NodeCount() const noexcept{
        return AllNodes.size();

    }

    std::size_t WayCount() const noexcept{
        return AllWays.size();
    }

    std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const noexcept{
        if(index >= NodeCount()){
            return NULL;
        }
        else{
            return AllNodes[index];
        }
    }

    std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const noexcept{
        //return MappedNodes->second;
        auto Search = MappedNodes.find(id);
        if(Search == MappedNodes.end()){
            return NULL;//or 0 or nullptr or NULL not sure
        }
        return Search->second;
    }

    std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const noexcept{
        if(index >= WayCount()){
            return NULL;
        }
        else{
            return AllWays[index];
        }
    }

    std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const noexcept{
        auto Search = MappedWays.find(id);
        if(Search == MappedWays.end()){
            return NULL;//or 0 or nullptr or NULL not sure
        }
        return Search->second;
    }
};
//...................... 
COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src){
    DImplementation = std::make_unique<SImplementation>(src);
}

COpenStreetMap::~COpenStreetMap(){

}

std::size_t COpenStreetMap::NodeCount() const noexcept{
    return DImplementation->NodeCount();
}

std::size_t COpenStreetMap::WayCount() const noexcept{
    return DImplementation->WayCount();
}

std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByIndex(std::size_t index) const noexcept{
    return DImplementation->NodeByIndex(index);
}

std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByID(TNodeID id) const noexcept{
    return DImplementation->NodeByID(id);
}

std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByIndex(std::size_t index) const noexcept{
    return DImplementation->WayByIndex(index);
}

std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByID(TWayID id) const noexcept{
    return DImplementation->WayByID(id);
}

