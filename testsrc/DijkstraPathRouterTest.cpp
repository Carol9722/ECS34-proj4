#include <gtest/gtest.h>
#include "DijkstraPathRouter.h"
#include<iostream>
#include<string>

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
    EXPECT_EQ(std::any_cast<char>(DijkstraPathRouter.GetVertexTag(id1)), 'A');
    EXPECT_EQ(std::any_cast<char>(DijkstraPathRouter.GetVertexTag(id2)), 'B');
}

TEST(DijkstraPathRouter, SimpleTest){
    CDijkstraPathRouter DijkstraPathRouter;
    std::vector< CPathRouter::TVertexID > Vertices;
    for(std::size_t Index = 0; Index < 6; Index++){
        Vertices.push_back(DijkstraPathRouter.AddVertex(Index));
        EXPECT_EQ(Index, std::any_cast<std::size_t>(DijkstraPathRouter.GetVertexTag(Vertices.back())));
    }
    DijkstraPathRouter.AddEdge(Vertices[0],Vertices[4],2);
    DijkstraPathRouter.AddEdge(Vertices[1],Vertices[3],10);
    DijkstraPathRouter.AddEdge(Vertices[2],Vertices[0],0);
    DijkstraPathRouter.AddEdge(Vertices[2],Vertices[1],3);
    DijkstraPathRouter.AddEdge(Vertices[3],Vertices[2],7);
    DijkstraPathRouter.AddEdge(Vertices[4],Vertices[5],100);
    DijkstraPathRouter.AddEdge(Vertices[5],Vertices[3],5);
    std::vector< CPathRouter::TVertexID > Path;
    std::vector< CPathRouter::TVertexID > ExpectedPath = {Vertices[2],Vertices[1],Vertices[3]};
    EXPECT_EQ(13.0,DijkstraPathRouter.FindShortestPath(Vertices[2],Vertices[3],Path));
    EXPECT_EQ(Path,ExpectedPath);
}
