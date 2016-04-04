#ifndef __HBGLOBAL_H__
#define __HBGLOBAL_H__


#ifdef HBAPI_LIB

#define HBAPI_EXPORT __declspec(dllexport)

#else

#define HBAPI_EXPORT __declspec(dllimport)

#endif


#endif // __HBGLOBAL_H__
