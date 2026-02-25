#pragma once 

// Anti-jam control 
void startAntiJam(); 
void stopAntiJam(); 
void antiJamTask(void*);
extern bool antiJamEnabled;