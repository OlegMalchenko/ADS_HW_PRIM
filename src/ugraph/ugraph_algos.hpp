////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Contains implementations of some algorithms for undirected graph.
/// \author     Sergey Shershakov
/// \version    0.1.0
/// \date       21.09.2020
/// \copyright  © Sergey Shershakov 2020.
///             This code is for educational purposes of the course "Algorithms
///             and Data Structures" provided by the Faculty of Computer Science
///             at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///
////////////////////////////////////////////////////////////////////////////////


/// Algorithm's implemented by Malchenko Oleg M. 15.10.2020


#ifndef UGRAPH_ALGOS_HPP
#define UGRAPH_ALGOS_HPP

#include <set>

#include "lbl_ugraph.hpp"




template<typename Vertex, typename Weight>
class PriorityQueue
{
public:
    typedef std::multimap<Vertex, Weight> WVmapExtracts; //qVt
    typedef std::set<std::pair<Weight, Vertex>> WVsorts; //smarter labellings stored in ascending order // qWt
public:

    PriorityQueue() = default;

    void insert(const Vertex& givenV, const Weight& givenW)
    {
        _qVt.insert(std::make_pair(givenV, givenW));
        _qWt.insert(std::make_pair(givenW, givenV));
    }

    void setNew(const Vertex& givenV, const Weight& givenW)
    {
        remove(givenV);
        insert(givenV, givenW);
    }

    void remove(const Vertex& removableV)
    {
        typename std::multimap<Vertex, Weight>::iterator wIter = _qVt.find(removableV);
        if(wIter != _qVt.end()) {
            _qWt.erase(std::make_pair(wIter->second /*Weight*/, removableV));
            _qVt.erase(wIter);

        }
    }

    Weight getCost(const Vertex& costReurn)
    {
        typename std::multimap<Vertex, Weight>::iterator wIter = _qVt.find(costReurn);
        return wIter->second;
    }

    bool isEmpty() const
    {
        if (_qVt.empty() && _qWt.empty()){
            return true;
        }
        else {
            return false;
        }
    }

    Vertex getMin() const
    {
        return _qWt.begin()->second;
    }

private:
    WVmapExtracts _qVt;
    WVsorts _qWt;
};




template<typename Vertex, typename EdgeLbl>
std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge>
findMSTPrim(const EdgeLblUGraph<Vertex, EdgeLbl>& g)
{
    std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge> res;

    PriorityQueue<Vertex, EdgeLbl> pQueue;

    std::set<Vertex> nonConsiderVisit;
    std::map<Vertex, Vertex> connectedThrough;



    typename std::map<Vertex, Vertex>::iterator connectIT;
    typename EdgeLblUGraph<Vertex, EdgeLbl>::VertexIterPair vertexITP = g.getVertices();
    typename EdgeLblUGraph<Vertex, EdgeLbl>::EdgeIterPair edgeITP = g.getEdges();
    typename EdgeLblUGraph<Vertex, EdgeLbl>::EdgeIter edgeIT = edgeITP.first;
    typename EdgeLblUGraph<Vertex, EdgeLbl>::VertexIter vertexIT = vertexITP.first;

    while (vertexIT != vertexITP.second)
    {
        pQueue.insert(*vertexIT, INT_MAX);
        /* ∞ is being assigned to each dist val., assuming edge labellings are ints*/
        ++vertexIT;
    }

    pQueue.setNew(edgeIT->first, 0); //assumig integers as vals.

    while (g.getVerticesNum() > nonConsiderVisit.size())
    {
        Vertex minExV = pQueue.getMin();

        nonConsiderVisit.insert(minExV);

        typename EdgeLblUGraph<Vertex, EdgeLbl>::AdjListCIterPair edgeRng = g.getAdjEdges(minExV);

        pQueue.remove(minExV);

        typename EdgeLblUGraph<Vertex, EdgeLbl>::AdjListCIter edgeSrc = edgeRng.first;
        while (edgeSrc != edgeRng.second)
        {
            Vertex anyAdj = edgeSrc->second;
            EdgeLbl anyAdjWeight;

            g.getLabel(minExV, anyAdj, anyAdjWeight); //getting anyAdjWeight parameter [refers]

            if ((nonConsiderVisit.find(anyAdj) == nonConsiderVisit.end()) && (pQueue.getCost(anyAdj) > anyAdjWeight)) //picking a correct vertex for Minimem vertex update
            {
                pQueue.setNew(anyAdj, anyAdjWeight);

                connectIT = connectedThrough.find(anyAdj);

                /*fulfilling the minimum spanning tree map*/
                if (connectIT == connectedThrough.end())
                {
                    connectedThrough.insert(std::make_pair(anyAdj, minExV)); //inserting a new minedge connect
                }
                else
                {
                    connectIT->second = minExV;
                }
            }
            ++edgeSrc;
        }
    }


    connectIT = connectedThrough.begin();
    while (connectIT != connectedThrough.end())
    {
        /*since all mappings have unique keys*/
        res.insert(std::make_pair(connectIT->first, connectIT->second));
        ++connectIT;
    }


    return res;
}

/////////////////////////////////////////////////////////////////////
///																  ///
///																  ///
/// can be found at:https://github.com/OlegMalchenko/ADS_HW_PRIM/ ///
///                                                               ///
///                                                               ///
/////////////////////////////////////////////////////////////////////



#endif // UGRAPH_ALGOS_HPP
