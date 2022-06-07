#ifndef CYCLONE_ENGINE
#define CYCLONE_ENGINE

#ifdef DLL_EXPORT
#define CYCLONE_DLL __declspec(dllexport)
#else
#define CYCLONE_DLL __declspec(dllimport)
#endif

#endif // !CYCLONE_ENGINE