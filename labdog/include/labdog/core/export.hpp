#ifndef LABDOG_EXPORT_HPP
#define LABDOG_EXPORT_HPP

#if defined(_WIN32) && defined(LABDOG_EXPORTS)
    #define LABDOG_API __declspec(dllexport)
#else
    #define LABDOG_API
#endif // _WIN32

#endif // LABDOG_EXPORT_HPP
