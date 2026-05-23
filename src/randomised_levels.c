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
}

uint16_t DaysSinceNewYear() {
    struct tm* currentTime = localtime(time(NULL));

    return currentTime->tm_yday;
}

size_t* GetRandomIndex(size_t count, size_t index) {
    struct tm* currentTime = localtime(time(NULL));
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
    int currentIndex = 0;
    int i;
    while (remaining.count > 0) {
        i = SeedableRNG_Next(&rng) % remaining.count;
        indicies[currentIndex] = RemainingIndicies_Pop(&remaining, i);
        
        if (currentIndex == index) {
            break;
        }
        currentIndex++;
    }

    return indicies[index];
}

Level GetTodaysLevel(LevelArray* levels) {
    LevelArray_Shuffle(levels);
    size_t currentIndex = GetRandomIndex(levels->count, DaysSinceNewYear() % 183);
    return levels->elements[currentIndex];
}