#include "CGameObjectArray__Delete__0.hpp"
#include "CGameObjectArray.hpp"
#include "Functions.hpp"
#include "NWNXApi.h"

using namespace Hooks;
using namespace Hooks::CGameObjectArray__Delete__0;

std::unique_ptr<FunctionHook> Hooks::CGameObjectArray__Delete__0::g_hookPtr;

void Hooks::CGameObjectArray__Delete__0::Hook()
{
    g_hookPtr = std::make_unique<FunctionHook>(
        "CGameObjectArray::Delete__0",
        Functions::CGameObjectArray__Delete__0,
        getFuncAddr(&CGameObjectArray__Delete__0__Hook));
}

void Hooks::CGameObjectArray__Delete__0::Unhook()
{
    g_hookPtr.reset();
}

uint32_t Hooks::CGameObjectArray__Delete__0__Hook(::CGameObjectArray* thisPtr, uint32_t objId)
{
    const uint32_t ret = g_hookPtr->callOriginal<CallingConvention::ThisCall, uint32_t>(thisPtr, objId);
    CGameObjectArray::g_objectMap.Remove(objId);
    return ret;
}