// The basic idea is "keep deleting leaves layer-by-layer, until reach the root."
//
// Specifically, first find all the leaves, then remove them. After removing, some
// nodes will become new leaves. So we can continue remove them. Eventually, there
// is only 1 or 2 nodes left. If there is only one node left, it is the root. If
// there are 2 nodes, either of them could be a possible root.
// 
// Time Complexity: Since each node will be removed at most once, the complexity is O(n).
//
// Updates:
// More precisely, if the number of nodes is V, and the number of edges is E. The
// space complexity is O(V+2E), for storing the whole tree. The time complexity is
// O(E), because we gradually remove all the neighboring information. As some
// friends pointing out, for a tree, if V=n, then E=n-1. Thus both time complexity
// and space complexity become O(n).

class Solution {
  public:
      
      struct Node
      {
          unordered_set<int> neighbor;
          bool isLeaf()const{return neighbor.size()==1;}
      };
      
      vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
          
          vector<int> buffer1;
          vector<int> buffer2;
          vector<int>* pB1 = &buffer1;
          vector<int>* pB2 = &buffer2;
          if(n==1)
          {
              buffer1.push_back(0);
              return buffer1;
          }
          if(n==2)
          {
              buffer1.push_back(0);
              buffer1.push_back(1);
              return buffer1;
          }
          
          // build the graph
          vector<Node> nodes(n);
          for(auto p:edges)
          {
              nodes[p.first].neighbor.insert(p.second);
              nodes[p.second].neighbor.insert(p.first);
          }
          
          // find all leaves
          for(int i=0; i<n; ++i)
          {
              if(nodes[i].isLeaf()) pB1->push_back(i);
          }

          // remove leaves layer-by-layer            
          while(1)
          {
              for(int i : *pB1)
              {
                  for(auto n: nodes[i].neighbor)
                  {
                      nodes[n].neighbor.erase(i);
                      if(nodes[n].isLeaf()) pB2->push_back(n);
                  }
              }
              if(pB2->empty())
              {
                  return *pB1;
              }
              pB1->clear();
              swap(pB1, pB2);
          }
          
      }
  };
