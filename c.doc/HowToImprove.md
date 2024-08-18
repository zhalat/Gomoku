//todo
1. logging game tree   
It would be usefull to know why algorithm takes certain decision (move) but not other.
Having such knowledge helps to improve desicion tree.

2. Split browsing tree into multiple cores.  
Right know algorithm uses signle core while browsing game tree.
Splitting browsing game tree thru all avaliable cores should significantly improve game responsivness
Remember that since c++17 many algorithm has execution policy which is able to run ex. search in many thread
```C++
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <thread>
#include <mutex>

int main() {
    std::vector<int> data(100, 1);
    std::mutex mtx;

    auto compute = [&](int& x) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "Index processed by thread "
                      << std::this_thread::get_id() << "\n";
        }
        x += 1;
    };

    std::for_each(std::execution::par, data.begin(), data.end(), compute);

    return 0;
}
```
4. Monte Carlo Algorithm  
At the final stage of decision making (a few best movies) use monter carlo 
 
5. Tournaments  
Two processes playing against each other as a quality measurement after each major changes.