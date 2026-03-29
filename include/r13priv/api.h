#pragma once
#ifndef R13_PRIVATE_ACCESS
#    error "This should NOT be included by files not part of R13"
#endif

#if defined(_WIN32) || defined(_WIN64)
#    if defined(DLL)
#        define API __declspec(dllexport)
#    else
#        define API __declspec(dllimport)
#    endif
#else
#    define API
#endif