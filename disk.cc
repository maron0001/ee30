#include <list>
#include <vector>
#include <cstdlib>
#include <cstdio>

int fcfs(int curr_pos, std::list<int> requests, std::list<int> *order) {
    int distance = 0, next_pos;

    while (!requests.empty()) {
        next_pos = requests.front();
        requests.pop_front();
        order->push_back(next_pos);
        
        distance += abs(next_pos - curr_pos);
        curr_pos = next_pos;
    }

    return distance;
}

int main(int argc, char *argv[]) {
    // put all the algorithms into a vector of function pointers
    std::vector<int (*)(int, std::list<int>, std::list<int>*)> v;

    v.push_back(fcfs);

    // set up problem requirements
    int curr_pos = 2255;
    std::list<int> requests = {2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};

    for (auto f: v) {
        std::list<int> order;
        int distance = (*f)(curr_pos, requests, &order);

        printf("distance %d: visited", distance);

        for (auto pos: order) {
            printf(" %d", pos);
        }

        printf("\n");
    }
}
