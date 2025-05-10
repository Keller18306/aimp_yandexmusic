#pragma once

#include "IUnknownBridge.h"
#include "aimp_sdk/apiGUI.h"
#include <functional>

class CallbackChangeHandler : public IUnknownBridge<IAIMPUIChangeEvents, &IID_IAIMPUIChangeEvents>
{
public:
    // Колбэк без аргументов
    explicit CallbackChangeHandler(std::function<void()> cb)
        : voidCallback(std::move(cb)) {}

    // Колбэк с TSender*
    explicit CallbackChangeHandler(std::function<void(IUnknown *)> cb)
        : typedCallback(std::move(cb)) {}

    void WINAPI OnChanged(IUnknown *Sender) override
    {
        if (typedCallback)
            typedCallback(Sender);
        else if (voidCallback)
            voidCallback();
    }

private:
    std::function<void()> voidCallback;
    std::function<void(IUnknown *)> typedCallback;
};