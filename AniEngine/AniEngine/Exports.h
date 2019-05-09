#pragma once

#include "Exports.h"

#if ENGINEDLL_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif
