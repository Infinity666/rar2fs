/*
    Copyright (C) 2009 Hans Beckerus (hans.beckerus@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    This program take use of the freeware "Unrar C++ Library" (libunrar)
    by Alexander Roshal and some extensions to it.

    Unrar source may be used in any software to handle RAR archives
    without limitations free of charge, but cannot be used to re-create
    the RAR compression algorithm, which is proprietary. Distribution
    of modified Unrar source in separate form or as a part of other
    software is permitted, provided that it is clearly stated in
    the documentation and source comments that the code may not be used
    to develop a RAR (WinRAR) compatible archiver.
*/

#ifndef DIRCACHE_H_
#define DIRCACHE_H_

#include <platform.h>
#include <time.h>
#include "dirlist.h"

extern pthread_rwlock_t dir_access_lock;

struct dircache_entry {
        struct dir_entry_list dir_entry_list;
        struct timespec mtim;
        int ts_valid;
};

struct dircache_cb {
        int (*stale)(const char *path);
        int (*free)(const char *path, struct dir_entry_list *);
};

struct dircache_entry *dircache_alloc(const char *path);
struct dircache_entry *dircache_get(const char *path);
void dircache_invalidate(const char *path);
void dircache_init(struct dircache_cb *cb);
void dircache_destroy();

#endif

