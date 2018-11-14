#include <list>
#include <vector>
#include <cstdlib>
#include <cstdio>

const char *fcfs(int curr_pos, std::list<int> requests, std::list<int> *order, int *distance);
const char *sstf(int curr_pos, std::list<int> requests, std::list<int> *order, int *distance);
const char *scan(int curr_pos, std::list<int> requests, std::list<int> *order, int *distance);
const char *look(int curr_pos, std::list<int> requests, std::list<int> *order, int *distance);
const char *cscan(int curr_pos, std::list<int> requests, std::list<int> *order, int *distance);
const char *clook(int curr_pos, std::list<int> requests, std::list<int> *order, int *distance);

int main(int argc, char *argv[]) {
    // make vector of function pointers

    // param: current position
    // param: list of pending requests
    // mutates: list of processed requests
    // mutates: total distance
    // returns: name of algorithm
    std::vector<const char * (*)(int, std::list<int>, std::list<int> *, int *)> v;

    // push_back all the functions we have declared
    v.push_back(fcfs);
    v.push_back(sstf);
    v.push_back(scan);
    v.push_back(look);
    v.push_back(cscan);
    v.push_back(clook);

    // set up problem requirements
    int curr_pos = 2255;
    std::list<int> requests = {2055, 1175, 2304, 2700, 513, 1680, 256, 1401, 4922, 3692};

    // loop through each function
    for (auto f: v) {
        int distance;
        std::list<int> order;
        
        printf("algorithm: %s\n", (*f)(curr_pos, requests, &order, &distance));
        printf("total distance: %d\nvisited:", distance);

        for (auto pos: order) {
            printf(" %d", pos);
        }

        printf("\n\n");
    }

    return 0;
}

const char *fcfs(int curr_pos, std::list<int> requests, std::list<int> *order, int *distance) {
    *distance = 0;

    while (!requests.empty()) {
        *distance += abs(requests.front() - curr_pos);
        curr_pos = requests.front();

        order->push_back(requests.front());
        requests.pop_front();
    }

    return "fcfs";
}

const char *sstf(int curr_pos, std::list<int> requests, std::list<int> *order, int *distance) {
    *distance = 0;

    while (!requests.empty()) {
        auto pos = requests.begin();
        
        for (auto it = requests.begin(); it != requests.end(); it++) {
            if (abs(*it - curr_pos) < abs(*pos - curr_pos))
                pos = it;
        }

        *distance += abs(*pos - curr_pos);
        curr_pos = *pos;

        order->push_back(*pos);
        requests.erase(pos);
    }

    return "sstf";
}

const char *scan(int curr_pos, std::list<int> requests, std::list<int> *order, int *distance) {
    int direction = 1; // going up
    *distance = 0;

    while (!requests.empty()) {
        auto pos = requests.begin();
        
        // bootstrap initial search position
        for (auto it = requests.begin(); it != requests.end(); it++) {
            if (direction == 1 && *it > curr_pos)
                pos = it;

            if (direction == -1 && *it < curr_pos)
                pos = it;
        }   

        for (auto it = requests.begin(); it != requests.end(); it++) {
            if (abs(*it - curr_pos) < abs(*pos - curr_pos)) {
                if (direction == 1 && *it > curr_pos) {
                    pos = it;
                }
                
                if (direction == -1 && *it < curr_pos) {
                    pos = it;
                }
            }
        }

        if (direction == 1 && *pos < curr_pos) { // could not find valid target
            *distance += 4999 - curr_pos; // move to 4999
            curr_pos = 4999;
            order->push_back(4999);
            direction = -1; // now going down

            continue;
        }

        *distance += abs(*pos - curr_pos);
        curr_pos = *pos;

        order->push_back(*pos);
        requests.erase(pos);
    }

    return "scan";
}

const char *look(int curr_pos, std::list<int> requests, std::list<int> *order, int *distance) {
    int direction = 1; // going up
    *distance = 0;

    while (!requests.empty()) {
        auto pos = requests.begin();
        
        // bootstrap initial search position
        for (auto it = requests.begin(); it != requests.end(); it++) {
            if (direction == 1 && *it > curr_pos)
                pos = it;

            if (direction == -1 && *it < curr_pos)
                pos = it;
        }   

        for (auto it = requests.begin(); it != requests.end(); it++) {
            if (abs(*it - curr_pos) < abs(*pos - curr_pos)) {
                if (direction == 1 && *it > curr_pos) {
                    pos = it;
                }
                
                if (direction == -1 && *it < curr_pos) {
                    pos = it;
                }
            }
        }

        if (direction == 1 && *pos < curr_pos) { // could not find valid target
            direction = -1; // now going down
            continue;
        }

        *distance += abs(*pos - curr_pos);
        curr_pos = *pos;

        order->push_back(*pos);
        requests.erase(pos);
    }

    return "look";
}

const char *cscan(int curr_pos, std::list<int> requests, std::list<int> *order, int *distance) {
    *distance = 0;

    while (!requests.empty()) {
        auto pos = requests.begin();
        
        // bootstrap initial search position
        for (auto it = requests.begin(); it != requests.end(); it++) {
            if (*it > curr_pos)
                pos = it;
        }   

        for (auto it = requests.begin(); it != requests.end(); it++) {
            if (*it > curr_pos && abs(*it - curr_pos) < abs(*pos - curr_pos)) {
                pos = it;
            }
        }

        if (*pos < curr_pos) { // could not find valid target
            *distance += 4999 - curr_pos; // move to 4999
            curr_pos = 4999;
            order->push_back(4999);
            
            *distance += 4999; // move to 0
            curr_pos = 0;
            order->push_back(0);

            continue;
        }

        *distance += abs(*pos - curr_pos);
        curr_pos = *pos;

        order->push_back(*pos);
        requests.erase(pos);
    }

    return "c-scan";
}

const char *clook(int curr_pos, std::list<int> requests, std::list<int> *order, int *distance) {
    *distance = 0;

    while (!requests.empty()) {
        auto pos = requests.begin();
        
        // bootstrap initial search position
        for (auto it = requests.begin(); it != requests.end(); it++) {
            if (*it > curr_pos)
                pos = it;
        }   

        for (auto it = requests.begin(); it != requests.end(); it++) {
            if (*it > curr_pos && abs(*it - curr_pos) < abs(*pos - curr_pos)) {
                pos = it;
            }
        }

        if (*pos < curr_pos) { // could not find valid target
            // find minimum
            pos = requests.begin();
            for (auto it = requests.begin(); it != requests.end(); it++) {
                if (*it < *pos)
                    pos = it;
            }
        }

        *distance += abs(*pos - curr_pos);
        curr_pos = *pos;

        order->push_back(*pos);
        requests.erase(pos);
    }

    return "c-look";
}
