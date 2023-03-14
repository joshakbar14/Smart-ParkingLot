
#ifndef PIGPIO_EXPORT_H
#define PIGPIO_EXPORT_H

#ifdef PIGPIO_STATIC_DEFINE
#  define PIGPIO_EXPORT
#  define PIGPIO_NO_EXPORT
#else
#  ifndef PIGPIO_EXPORT
#    ifdef pigpio_EXPORTS
        /* We are building this library */
#      define PIGPIO_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define PIGPIO_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef PIGPIO_NO_EXPORT
#    define PIGPIO_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef PIGPIO_DEPRECATED
#  define PIGPIO_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef PIGPIO_DEPRECATED_EXPORT
#  define PIGPIO_DEPRECATED_EXPORT PIGPIO_EXPORT PIGPIO_DEPRECATED
#endif

#ifndef PIGPIO_DEPRECATED_NO_EXPORT
#  define PIGPIO_DEPRECATED_NO_EXPORT PIGPIO_NO_EXPORT PIGPIO_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PIGPIO_NO_DEPRECATED
#    define PIGPIO_NO_DEPRECATED
#  endif
#endif

#endif /* PIGPIO_EXPORT_H */
