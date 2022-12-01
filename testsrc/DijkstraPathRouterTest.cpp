#include <gtest/gtest.h>
#include "DijkstraPathRouter.h"
#include<iostream>

TEST(DijkstraPathRouter, RouteEmptyTest){
    CDijkstraPathRouter DijkstraPathRouter;
    ASSERT_EQ(DijkstraPathRouter.VertexCount(), 0);
}

TEST(DijkstraPathRouter, AddVertexTest){
    CDijkstraPathRouter DijkstraPathRouter;
    int id1 = DijkstraPathRouter.AddVertex('A');
    int id2 = DijkstraPathRouter.AddVertex(1);
    int id3 = DijkstraPathRouter.AddVertex(3.2);
    ASSERT_EQ(DijkstraPathRouter.VertexCount(), 3);
}

TEST(DijkstraPathRouter, FindVertexTest){
    CDijkstraPathRouter DijkstraPathRouter;
    int id1 = DijkstraPathRouter.AddVertex('A');
    int id2 = DijkstraPathRouter.AddVertex('B');
    ASSERT_EQ(DijkstraPathRouter.VertexCount(), 2);
    EXPECT_EQ(DijkstraPathRouter.GetVertexTag(id1), 'A');
    EXPECT_EQ(DijkstraPathRouter.GetVertexTag(id2), 'B');
}

TEST(DijkstraPathRouter, AddEdgeTest){
    CDijkstraPathRouter DijkstraPathRouter;
    int id1 = DijkstraPathRouter.AddVertex('A');
    int id2 = DijkstraPathRouter.AddVertex('B');
    int id3 = DijkstraPathRouter.AddVertex('C');
    int id4 = DijkstraPathRouter.AddVertex('D');
    DijkstraPathRouter.AddEdge(id1,id2,3);
    DijkstraPathRouter.AddEdge(id2,id3,5);
    ASSERT_EQ(DijkstraPathRouter.VertexCount(),4);
    EXPECT_EQ(DijkstraPathRouter.GetVertexTag(id2), 'B');
}

TEST(DijkstraPathRouter, ShortestDistanceTest){
    CDijkstraPathRouter DijkstraPathRouter;
    int id1 = DijkstraPathRouter.AddVertex('A');
    int id2 = DijkstraPathRouter.AddVertex('B');
    int id3 = DijkstraPathRouter.AddVertex('C');
    int id4 = DijkstraPathRouter.AddVertex('D');
    DijkstraPathRouter.AddEdge(id1,id2,3);
    DijkstraPathRouter.AddEdge(id2,id3,5);
    DijkstraPathRouter.AddEdge(id3,id4,10);
    DijkstraPathRouter.AddEdge(id1,id3,3);
    std::vector<CPathRouter::TVertexID> pathid;
    ASSERT_EQ(DijkstraPathRouter.VertexCount(),4);
    EXPECT_EQ(DijkstraPathRouter.FindShortestPath(id1, id4, pathid), 13);
    EXPECT_EQ(pathid[0], id1);
    EXPECT_EQ(pathid[1], id3);
    EXPECT_EQ(pathid[2], id4);
}




