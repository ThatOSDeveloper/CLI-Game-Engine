#ifndef API_H
#define API_H
#pragma once

typedef struct {
    int commonitem;
    int uncommonitem;
    int rareitem;
} Items;

typedef struct {
    int money;
    Items item;
} Player;

// Ask a question and get a int returned into a buffer
void askintquestion(char* question, int answeramount, int* buffer, ...);
// Get int and put it into a buffer.
void getint(int buffer);
// OS Free sleep function (somewhat it still has to be unix or windows)
void sleepFunction(int seconds);
// Clear screen function
void clearScreen();

#endif