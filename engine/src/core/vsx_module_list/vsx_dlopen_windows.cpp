/**
* Project: VSXu Engine: Realtime modular visual programming engine.
*
* This file is part of Vovoid VSXu Engine.
*
* @author Jonatan Wallmander, Robert Wenzel, Vovoid Media Technologies AB Copyright (C) 2003-2013
* @see The GNU Lesser General Public License (LGPL)
*
* VSXu Engine is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*
* You should have received a copy of the GNU Lesser General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <io.h>
#include <windows.h>
#include <stdio.h>
#include "vsx_dlopen.h"


HMODULE vsx_dlopen::open(const char *filename)
{
  HMODULE winlibrary = LoadLibrary( filename );
  return winlibrary;
}

int  vsx_dlopen::close(HMODULE handle)
{
  return FreeLibrary( handle );
}


char*  vsx_dlopen::error()
{
  DWORD dw = GetLastError();
  char* message = (char*)malloc(sizeof(char)*64);
  sprintf(message, "windows error code %d", dw);
  return message;
}


void* vsx_dlopen::sym(HMODULE handle, const char *symbol)
{
  return GetProcAddress( handle, symbol );
}
