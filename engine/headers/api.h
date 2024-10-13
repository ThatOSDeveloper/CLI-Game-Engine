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

void askintquestion(char* question, int answeramount, int* buffer, ...);
void getint(int buffer);

#endif