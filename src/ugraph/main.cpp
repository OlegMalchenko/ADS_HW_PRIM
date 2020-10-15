////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Main module for smoke-test-project for undirected graphs.
/// \author     Sergey Shershakov
/// \version    0.1.0
/// \date       18.09.2020
/// \copyright  © Sergey Shershakov 2020.
///             This code is for educational purposes of the course "Algorithms
///             and Data Structures" provided by the Faculty of Computer Science
///             at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///
////////////////////////////////////////////////////////////////////////////////


#include <iostream>

#include "ugraph.hpp"
#include "ugraph_algos.hpp"

void test1()
{
/*
    EdgeLblUGraph<int, int> g;
    g.addLblEdge(1, 2, 4);
    g.addLblEdge(2, 3, 8);
    g.addLblEdge(3, 1, 8);
    g.addLblEdge(4, 3, 3);
    g.addLblEdge(4, 1, 16);
    g.addLblEdge(4, 5, 1);

    std::set<EdgeLblUGraph<int, int>::Edge> returns = findMSTPrim(g);
    std::set<EdgeLblUGraph<int, int>::Edge>::iterator it = returns.begin();

    std::cout << "{";
    for(;it != returns.end();++it)
    {
        std::cout << "( " << it->first << ", " <<it->second << "), ";
    }
    std::cout << "}\n";
*/


}

int main()
{
    std::cout << "Let's do some undirected graphs!\n";

    test1();

    std::cout << "\n\nBye-bye!\n\n";
    return 0;
}

