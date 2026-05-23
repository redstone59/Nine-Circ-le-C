#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "level.c"
#include "seedable_rng.c"

typedef struct RemainingIndicies {
    size_t* elements;
    size_t count;
} RemainingIndicies;

void RemainingIndicies_Initialise(RemainingIndicies* indicies) {
    for (int i = 0; i < indicies->count; i++) {
        indicies->elements[i] = i;
    }
}

size_t RemainingIndicies_Pop(RemainingIndicies* indicies, size_t index) {
    size_t value = indicies->elements[index];
    for (int i = index; i < indicies->count - 1; i++) {
        indicies->elements[i] = indicies->elements[i + 1];
    }
    indicies->count--;
    return value;
}

uint16_t DaysSinceNewYear() {
    time_t currentEpoch = time(NULL);
    struct tm* currentTime = localtime(&currentEpoch);

    return currentTime->tm_yday;
}

size_t GetRandomIndex(size_t count) {
    time_t currentEpoch = time(NULL);
    struct tm* currentTime = localtime(&currentEpoch);
    uint32_t seed = currentTime->tm_year;
    if (currentTime->tm_mon >= 5) {
        seed += 10000;
    }

    SeedableRNG rng = (SeedableRNG) {
        .state = seed
    };

    size_t remainingElements[count];
    RemainingIndicies remaining = (RemainingIndicies) {
        .elements = remainingElements,
        .count = count
    };
    RemainingIndicies_Initialise(&remaining);
    
    size_t indicies[count];
    int index = currentTime->tm_yday % 183;
    int currentIndex = 0;
    int i;
    while (remaining.count > 0) {
        i = SeedableRNG_Next(&rng) % remaining.count;
        indicies[currentIndex] = RemainingIndicies_Pop(&remaining, i);
        currentIndex++;
    }

    return indicies[index];
}

Level GetTodaysLevel(LevelArray* levels) {
    size_t currentIndex = GetRandomIndex(levels->count);
    return levels->elements[currentIndex];
}