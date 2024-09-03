/* libpgn - PGN file parser.
 * Copyright (C) 2024 youkwhd <lolywk@tutanota.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __LIBPGN_EXPORT_H
#define __LIBPGN_EXPORT_H

#if defined(_WIN32)
    /* MS-DOS DLL needs to know
     * which functions are exported.
     */
    #define PGN_EXPORT __declspec(dllexport)
#else
    #define PGN_EXPORT
#endif

void __pgn_export(void);

#endif // __LIBPGN_EXPORT_H
