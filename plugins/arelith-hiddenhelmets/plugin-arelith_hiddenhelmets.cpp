#include "NWNXArelithHiddenHelmets.hpp"
#include <memory>

std::unique_ptr<CNWNXBase> g_plugin;

extern "C" CNWNXBase* GetClassObject()
{
    if (g_plugin == nullptr)
    {
        g_plugin = std::make_unique<NWNXArelithHiddenHelmets>();
    }

    return g_plugin.get();
}