#ifndef __LIBPGN_EXPORT_H
#define __LIBPGN_EXPORT_H

/* Common Microsoft behavior designing systems.
 */
#if defined(_WIN32)
    /* MS-DOS DLL needs to know
     * which functions are exported.
     */
    #define PGN_EXPORT __declspec(dllexport)
#else
    #define PGN_EXPORT
#endif

#endif // __LIBPGN_EXPORT_H
