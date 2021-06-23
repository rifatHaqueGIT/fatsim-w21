#include "fatsim.h"
#include <cstdio>
#include <queue>
#include <algorithm>

std::vector<long> fat_check(const std::vector<long> & fat)
{
   std::vector<std::vector<long>> adj_list(fat.size());//list of adjacent nodes
   long val = 0;//used for dfs as a placeholder
   long length = 0;//holds the depth/length of the branch in dfs
   std::queue<long> queue;//used for iteratively doing dfs
   std::vector<long> results;// used to hold our result
   std::vector<int> visit(fat.size());// used for dfs, makes sure we don't get stuck in an infinite loop
   std::vector<long> negNodes;// the first nodes attached to our end(-1)
   
   //As pavol has in his hint to use an adjacency vector
  for(size_t i = 0; i < fat.size(); i++){// go through the fat vector and fill in both negNodes and adj_list
    if(fat[i] == -1) {negNodes.push_back(i);}// if its -1  we put the indexinto our negNodes
    else{
      //place the adjacents in adj_list
      adj_list[i].push_back(fat[i]);
      adj_list[fat[i]].push_back(i);
    }
  }
  
  if(negNodes.size() > 0){// We do not have any branches if we do not have an end node(-1)
 //Go through the negative nodes
  for(const auto & n : negNodes) {// go through each of the nodes attached to -1
    queue.push(n);// push in our first node for nth branch
    queue.push(-2);//using -2 as indicator of a new depth (using negative two b/c we use -1 already)
    length = 0;// set length for this branch to zero
    visit[n] = 1;// set that we have visited n(the first node after -1)
    while(!queue.empty()){// while queue is not empty. Queue will e empty if we reach the end of all nodes
      val = queue.front();// get the first value in our queue
      if(val == -2)
      { // Indicates we've reached a new depth
        length ++;// increase the depth we've reached for this nth branch
        queue.pop();// pop the -2 from queue
        if(queue.empty()) break;//if the queue is empty then we've reached the max depth of this branch so we should break
        //this also prevents us from getting an error where we call for a value from queue but their is no value
        val = queue.front();//get the next value (and there will be one or we would not reach here)
        queue.push(-2);// push in the indicator for the next depth
      }
      visit[val] = 1;// set visit so that we know that we have already iteratorated over val
      queue.pop();// pop val out the queue
      for(const auto & adj : adj_list[val])// check the adjacents of val
        {
          if(visit[adj] == 0)//IF WE HAVE NOT VISITED THE NODE
            queue.push(adj);// add it to our queue
        }
        
    }
    results.push_back(length);// the nth branch has finished, now we push back our result for the nth branch
  }
}
  std::sort(results.begin(), results.end());// sort it in ascending order
  return results;// and result is returned
}

