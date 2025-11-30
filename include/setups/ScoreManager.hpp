//
// Created by evest on 28.11.2025.
//
#pragma once

class ScoreManager {
public:
    void addHit() { ++humansHit_; }
    int humansHit() const { return humansHit_; }
    void resetHumansHit() { humansHit_ = 0; }
private:
    int humansHit_ = 0;

};
