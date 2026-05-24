#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StringBuilder {
    char* chars;
    size_t count;
    size_t capacity;
} StringBuilder;

void StringBuilder__Resize(StringBuilder* sb) {
    size_t newCapacity = sb->capacity << 1;
    sb->chars = realloc(sb->chars, newCapacity);
    sb->capacity = newCapacity;
}

void StringBuilder_Append(StringBuilder* sb, char* toAppend, size_t count) {
    if (sb->count + count > sb->capacity) {
        StringBuilder__Resize(sb);
    }

    memcpy(sb->chars + sb->count, toAppend, count);
    sb->count += count;
}

void StringBuilder_Terminate(StringBuilder* sb) {
    StringBuilder_Append(sb, "\0", 1);
    sb->count -= 1;
}

void StringBuilder_Initialise(StringBuilder* sb, size_t capacity) {
    if (sb->chars != NULL) {
        return;
    }
    
    sb->chars = malloc(capacity * sizeof(char));
    sb->count = 0;
    sb->capacity = capacity;
}

void StringBuilder_Free(StringBuilder* sb) {
    if (sb->chars == NULL) {
        return;
    }

    free(sb->chars);
    sb->chars = NULL;
    sb->count = 0;
    sb->capacity = 0;
}