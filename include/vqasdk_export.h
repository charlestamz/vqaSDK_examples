
#ifndef VQASDK_EXPORT_H
#define VQASDK_EXPORT_H

#ifdef VQASDK_STATIC_DEFINE
#  define VQASDK_EXPORT
#  define VQASDK_NO_EXPORT
#else
#  ifndef VQASDK_EXPORT
#    ifdef vqasdk_EXPORTS
        /* We are building this library */
#      define VQASDK_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VQASDK_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VQASDK_NO_EXPORT
#    define VQASDK_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VQASDK_DEPRECATED
#  define VQASDK_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef VQASDK_DEPRECATED_EXPORT
#  define VQASDK_DEPRECATED_EXPORT VQASDK_EXPORT VQASDK_DEPRECATED
#endif

#ifndef VQASDK_DEPRECATED_NO_EXPORT
#  define VQASDK_DEPRECATED_NO_EXPORT VQASDK_NO_EXPORT VQASDK_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VQASDK_NO_DEPRECATED
#    define VQASDK_NO_DEPRECATED
#  endif
#endif

#endif /* VQASDK_EXPORT_H */
