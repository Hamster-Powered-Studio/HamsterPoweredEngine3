#pragma once

class Timestep
{
public:
    explicit Timestep(double step)
    {
        this->step = step;
    }
    
    double DeltaMinutes() const {return step / 60.0;}
    double DeltaSeconds() const {return step;}
    double DeltaMilliseconds() const {return step * 1000.0;}
    
private:
    double step;
    
};
