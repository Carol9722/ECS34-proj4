#include <gtest/gtest.h>
#include "DSVReader.h"
#include "DSVWriter.h"
#include "StringUtils.h"
#include "StringDataSource.h"
#include "StringDataSink.h"
#include "CSVBusSystem.h"
#include<iostream>


TEST(CSVBusSystem, RouteEmptyTest){
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id\nA,101");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes,',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    ASSERT_EQ(BusSystem.StopCount(),0);
    ASSERT_EQ(BusSystem.RouteCount(),1);
    EXPECT_EQ (BusSystem.StopByIndex(0),nullptr);
}


TEST(CSVBusSystem, StopEmptyTest){
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,101");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes,',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    ASSERT_EQ(BusSystem.StopCount(),1);
    ASSERT_EQ(BusSystem.RouteCount(),0);
    EXPECT_EQ(BusSystem.RouteByIndex(0),nullptr);
}


TEST(CSVBusSystem, StopInvalid){
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,1001\n2,1002");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id\nA,22\nB,23");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes,',');

    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    ASSERT_EQ(BusSystem.StopCount(),2);
    EXPECT_EQ (BusSystem.RouteByIndex(2),nullptr);
    EXPECT_EQ (BusSystem.RouteByName("C"),nullptr);
}


TEST(CSVBusSystem, RouteInvalid){
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,1001\n2,1002");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id\nA,22\nB,23");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes,',');

    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    ASSERT_EQ(BusSystem.RouteCount(),2);
    EXPECT_EQ(BusSystem.StopByIndex(2),nullptr);
    EXPECT_EQ (BusSystem.StopByID(3),nullptr);
    EXPECT_EQ (BusSystem.RouteByIndex(1)->GetStopID(1),static_cast <int> (CBusSystem::InvalidStopID));
}

TEST(CSVBusSystem, StopTest){
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,1001\n2,1002\n3,1003\n4,1004");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes,',');

    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    ASSERT_EQ(BusSystem.StopCount(),4);
    ASSERT_EQ(BusSystem.RouteCount(),0);
    EXPECT_EQ(BusSystem.StopByIndex(0)->ID(),1);
    EXPECT_EQ (BusSystem.StopByID(1)->NodeID(),1001);
    EXPECT_EQ(BusSystem.StopByIndex(1)->ID(),2);
    EXPECT_EQ (BusSystem.StopByID(2)->NodeID(),1002);
    EXPECT_EQ(BusSystem.StopByIndex(2)->ID(),3);
    EXPECT_EQ (BusSystem.StopByID(3)->NodeID(),1003);
    EXPECT_EQ(BusSystem.StopByIndex(3)->ID(),4);
    EXPECT_EQ (BusSystem.StopByID(4)->NodeID(),1004);

}

TEST(CSVBusSystem, RouteTest){
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id\nA,22\nA,23\nA,24\nB,33\nB,34");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes,',');

    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    ASSERT_EQ(BusSystem.StopCount(),0);
    ASSERT_EQ(BusSystem.RouteCount(),2);
    EXPECT_EQ (BusSystem.RouteByIndex(0)->Name(),"A");
    EXPECT_EQ (BusSystem.RouteByName("A")->GetStopID(0),22);
    EXPECT_EQ (BusSystem.RouteByName("A")->GetStopID(1),23);
    EXPECT_EQ (BusSystem.RouteByName("A")->GetStopID(2),24);
    EXPECT_EQ (BusSystem.RouteByIndex(1)->Name(),"B");
    EXPECT_EQ (BusSystem.RouteByName("B")->GetStopID(0),33);
    EXPECT_EQ (BusSystem.RouteByName("B")->GetStopID(1),34);

}


TEST(CSVBusSystem, UnorderedRouteTest){
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id\nA,22\nB,33\nA,23\nB,34\nA,24");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes,',');

    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    ASSERT_EQ(BusSystem.StopCount(),0);
    ASSERT_EQ(BusSystem.RouteCount(),2);
    EXPECT_EQ (BusSystem.RouteByIndex(0)->Name(),"A");
    EXPECT_EQ (BusSystem.RouteByName("A")->GetStopID(0),22);
    EXPECT_EQ (BusSystem.RouteByName("A")->GetStopID(1),23);
    EXPECT_EQ (BusSystem.RouteByName("A")->GetStopID(2),24);
    EXPECT_EQ (BusSystem.RouteByIndex(1)->Name(),"B");
    EXPECT_EQ (BusSystem.RouteByName("B")->GetStopID(0),33);
    EXPECT_EQ (BusSystem.RouteByName("B")->GetStopID(1),34);


}