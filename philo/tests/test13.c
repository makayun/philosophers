#include <stdio.h>

void callPhilosophers(int totalPhilosophers) {
    int i, philosopher;

    for (i = 0; i <= totalPhilosophers * 2; i++) {
        philosopher = (i % totalPhilosophers) + 1;
        if (i % 2 == 1)
            printf("%d, ", philosopher);
        else
            printf("%d, ", (philosopher + totalPhilosophers / 2 - 1) % totalPhilosophers + 1);
    }
}

int main() {
    int philosophers = 5; // Change this value based on the number of philosophers
    callPhilosophers(philosophers);

    return 0;
}