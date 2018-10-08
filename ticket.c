#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

// GLOBALS
int wall_clock; // clock to synchronize threads
int N; // number of customers per seller
char seat_map[10][10][5]; // seat map
int row_order_for_M[10] = {4,5,3,6,2,7,1,8,0,9}; // row order for middle-price sellers
int h_sold = 0, m_sold = 0, l_sold = 0, sold_out_turned_away = 0, closed_turned_away = 0; // stats

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// integer comparison function for qsort()
int compare(const void* a, const void* b) {
    return (*(int *)a - *(int *)b);
}

void *sell(void *seller_type_ptr) {
    int i, j, k, *queue, done, ready_time = 0;
    char *seller_type = seller_type_ptr; // cast pointer

    queue = malloc(N * sizeof(int));
    if (queue == NULL) {
        printf("error! memory allocation failed");
    }

    // generate random customers
    for (i = 0; i < N; i++) {
        queue[i] = rand() % 60;
    }

    // sort the queue
    qsort((void *) queue, N, sizeof(int), compare);

    i = 0;

    while (i < N && wall_clock < 60) {
        done = 0;

        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);

        if (wall_clock == 60) { // time to close the ticket window
            pthread_mutex_unlock(&mutex);
            break;
        }

        if (queue[i] == wall_clock) { // customer just arrived
            printf("[0:%02d] %c%c: customer %c%c%02d arrived in queue\n", wall_clock, seller_type[0], seller_type[1], seller_type[0], seller_type[1], i+1);
        }

        if (queue[i] <= wall_clock && ready_time <= wall_clock) { // ready to serve next customer

            if (seller_type[0] == 'H') {
                for (j = 0; !done && j < 10; j++)
                    for (k = 0; !done && k < 10; k++)
                        if (strlen(seat_map[j][k]) == 0) { // seat is available
                            sprintf(seat_map[j][k], "%c%c%02d", seller_type[0], seller_type[1], i+1);
                            printf("[0:%02d] %c%c: assigned seat %d to customer %c%c%02d\n", wall_clock, seller_type[0], seller_type[1], j*10+k+1, seller_type[0], seller_type[1], i+1);
                            h_sold++;
                            done = 1;
                        }

                if (done)
                    ready_time = wall_clock + rand() % 2 + 1;
            }
            
            if (seller_type[0] == 'M') {
                for (j = 0; !done && j < 10; j++)
                    for (k = 0; !done && k < 10; k++)
                        if (strlen(seat_map[row_order_for_M[j]][k]) == 0) { // seat is available
                            sprintf(seat_map[row_order_for_M[j]][k], "%c%c%02d", seller_type[0], seller_type[1], i+1);
                            printf("[0:%02d] %c%c: assigned seat %d to customer %c%c%02d\n", wall_clock, seller_type[0], seller_type[1], row_order_for_M[j]*10+k+1, seller_type[0], seller_type[1], i+1);
                            m_sold++;
                            done = 1;
                        }

                if (done)
                    ready_time = wall_clock + rand() % 3 + 2;
            }
            
            if (seller_type[0] == 'L') {
                for (j = 9; !done && j >= 0; j--)
                    for (k = 0; !done && k < 10; k++)
                        if (strlen(seat_map[j][k]) == 0) { // seat is available
                            sprintf(seat_map[j][k], "%c%c%02d", seller_type[0], seller_type[1], i+1);
                            printf("[0:%02d] %c%c: assigned seat %d to customer %c%c%02d\n", wall_clock, seller_type[0], seller_type[1], j*10+k+1, seller_type[0], seller_type[1], i+1);
                            l_sold++;
                            done = 1;
                        }

                if (done)
                    ready_time = wall_clock + rand() % 4 + 4;
            }

            if (!done) //sold out
                while (i < N && queue[i] <= wall_clock) {
                    printf("[0:%02d] %c%c: sold out. customer %c%c%02d turned away\n", wall_clock, seller_type[0], seller_type[1], seller_type[0], seller_type[1], i+1);
                    sold_out_turned_away++;
                    i++;
                }
            else
                i++;
        }

         pthread_mutex_unlock(&mutex);
    }

    // ticket sales closed
    while (i < N) {
        printf("[0:%02d] %c%c: ticket sales closed. customer %c%c%02d turned away\n", wall_clock, seller_type[0], seller_type[1], seller_type[0], seller_type[1], i+1);
        closed_turned_away++;
        i++;
    }

    free(queue);
    return NULL;
}

void wakeup_all_seller_threads(void) {
    pthread_mutex_lock(&mutex);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    // give enough time for all threads to finish
    struct timespec ts = {0, 1000000L}; // 1ms

    nanosleep(&ts, NULL);
}

int main(int argc, char *argv[]) {
    int i, j;
    pthread_t tids[10];
    char seller_type[10][2];

    // check arguments
    if (argc != 2) {
       printf("please provide N");
       return 1; // abnormal termination
    }

    sscanf(argv[1], "%d", &N); // get N
    srand(time(NULL)); // seed pseudorandom generator

    memset(seat_map, 0, 5*10*10);

    seller_type[0][0] = 'H';
    seller_type[0][1] = '1';
    pthread_create(&tids[0], NULL, sell, seller_type[0]);

    for (i = 1; i < 4; i++) {
        seller_type[i][0] = 'M';
        seller_type[i][1] = '0' + i;
        pthread_create(&tids[i], NULL, sell, seller_type[i]);
    }

    for (i = 4; i < 10; i++) {
        seller_type[i][0] = 'L';
        seller_type[i][1] = '0' + i - 3;
        pthread_create(&tids[i], NULL, sell, seller_type[i]);
    }

    // run clock 61 times (the last time is to close the ticket window)
    for (wall_clock = 0; wall_clock < 61; wall_clock++) {
        wakeup_all_seller_threads();
    }

    for (i = 0; i < 10; i++) {
        pthread_join(tids[i], NULL);
    }

    // print seat map
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("[%4s]", seat_map[i][j]);
        }
        printf("\n");
    }

    // print statistics
    printf("H sold: %d\nM sold: %d\nL sold: %d\nTurned away (sold out): %d\nTurned away (sales closed): %d\n", h_sold, m_sold, l_sold, sold_out_turned_away, closed_turned_away);

    return 0;
}
