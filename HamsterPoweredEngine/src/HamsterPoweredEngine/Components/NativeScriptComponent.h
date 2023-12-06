#pragma once

struct NativeScriptComponent
{
public:
    virtual void OnBegin();
    virtual void OnUpdate(float ts);
    virtual void OnDestroyed();
    
};
