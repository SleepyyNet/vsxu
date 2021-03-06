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

#ifndef VSX_STRING_H
#define VSX_STRING_H

#include <container/vsx_avector.h>
#include <cstring>
#include <ctype.h>
#include <vsx_platform.h>
 
class vsx_string
{
  mutable vsx_avector<char> data;

  // deal with the terminating 0 character
  inline bool zero_test() const VSX_ALWAYS_INLINE
  {
    return (data[data.get_used()-1]);
  }

  inline void zero_add() const VSX_ALWAYS_INLINE
  {
    if (!data.size()) {
      data.push_back((char)0);
    } else
    if (zero_test())
    data.push_back((char)0);
  }

public:

  inline char* get_pointer() const VSX_ALWAYS_INLINE
  {
  	return data.get_pointer();
  }

  inline void zero_remove() const VSX_ALWAYS_INLINE
  {
    if (data.size())
    if (!data[data.size()-1])
    data.reset_used(data.size()-1);
  }
  // data manipulation
  inline const char* c_str() const VSX_ALWAYS_INLINE
  {
    zero_add();
    return data.get_pointer();
  }
  
  inline char* c_copy() const VSX_ALWAYS_INLINE
  {
  	zero_add();
  	char* n = new char[this->size()+1];
  	for (size_t i = 0; i <= this->size(); i++) {
  		n[i] = data[i];
  	}
  	return n;
  }

  inline void push_back(const char p) VSX_ALWAYS_INLINE
  {
    zero_remove();
    data.push_back(p);
  }

  inline void push_back_(const char p) VSX_ALWAYS_INLINE
  {
    data.push_back(p);
  }

  inline char pop_back() const VSX_ALWAYS_INLINE
  {
    zero_remove();
    if (data.size()) {
      char f = data[data.size()-1];
      data.reset_used(data.size()-1);
      return f;
    }
    return 0;
  }

  inline size_t size() const VSX_ALWAYS_INLINE
  {
    if (!data.size()) return 0;

    if (data[data.get_used()-1])
    return data.get_used(); else
      return data.get_used()-1;
  }

  inline void clear() VSX_ALWAYS_INLINE
  {
    data.reset_used();
  }

  inline void empty() VSX_ALWAYS_INLINE
  {
    data.reset_used();
  }

  char& operator[](int index) const VSX_ALWAYS_INLINE
  {
  	if (index < 0) index = 0;

    return data[index];
  }

  void make_lowercase() VSX_ALWAYS_INLINE
  {
    for (unsigned long i = 0; i < data.size(); ++i)
    {
			data[i] = tolower(data[i]);
    }
	}
  
  // constructors
  vsx_string()
  {
  }

//----------------------------------------------------------------------------
// OTHER VSX_STRING REFERENCE
//----------------------------------------------------------------------------
 
  vsx_string(const vsx_string& foo)
  {
//    printf("copy constructor\n");
    *this = foo;
  }
//#

//----------------------------------------------------------------------------
// NULLTERMINATED CHAR*
//----------------------------------------------------------------------------
  vsx_string(const char* ss)
  {
    *this = ss;
  }

  vsx_string(const char* ss, size_t max_len)
  {
    for (size_t i = 0; i < max_len; i++)
    {
      push_back( ss[i] );
    }
    zero_add();
  }

  inline const vsx_string& operator=(const vsx_string& ss) VSX_ALWAYS_INLINE
  {
    if (&ss != this) {
      //printf("copying with =\n");
      data.clear();
      int sss = ss.size();
      if (sss > 0)
      data[sss-1] = 0;
			char* dp = data.get_pointer();
			char* sp = ss.get_pointer();
      for (int i = 0; i < sss; ++i) {
        //printf("%d+",ss[i]);
        dp[i] = sp[i];
      }
      return *this;
    }
    return *this;
  };

  inline const vsx_string operator+(const vsx_string& right) const VSX_ALWAYS_INLINE
  {
    //printf("a1\n");
    vsx_string n;
    unsigned long i = 0;
    while (i < data.get_used()) {
      if (data[i] != 0) n.push_back_(data[i]);
      ++i;
    }
    for (i = 0; i < (unsigned long)right.size(); ++i)
    {
      n.push_back_(right[i]);
    }
    return n;
  };

  inline const vsx_string& operator+=(const vsx_string& right) VSX_ALWAYS_INLINE
  {
    zero_remove();
    size_t i = 0;
    while (i < right.size()) {
      data.push_back(right[i]);
      ++i;
    }
    return *this;
  }


  inline const vsx_string& operator=(const char* ss) VSX_ALWAYS_INLINE
  {
    data.clear();
    char* si = (char*)ss;
    while (si && *si != 0) {
      data.push_back(*si);
      ++si;
    }
    return *this;
  }


  inline const vsx_string operator+(const char* const right) const VSX_ALWAYS_INLINE
  {
    vsx_string n;
    unsigned long i = 0;
    while (i < data.get_used() && data[i] != 0) {
      n.push_back_(data[i]);
      ++i;
    }
    i = 0;
    while (right[i] != 0) {
      n.push_back_(right[i]);
      ++i;
    }
    return n;
  }


  const vsx_string& operator+=(const char* right) VSX_ALWAYS_INLINE
  {
    zero_remove();
    int i = 0;
    while (right[i] != 0)
    {
      data.push_back(right[i]);
      ++i;
    }
    return *this;
  }


//----------------------------------------------------------------------------
// SINGLE CHAR
//----------------------------------------------------------------------------

  inline vsx_string(const char& ss) VSX_ALWAYS_INLINE
  {
    *this = ss;
  }

  inline const vsx_string& operator=(const char& ss) VSX_ALWAYS_INLINE
  {
    data.clear();
    data.push_back(ss);
    return *this;
  }

  inline const vsx_string operator+(const char& right) const VSX_ALWAYS_INLINE
  {
    vsx_string n = *this;
    n.zero_remove();
    n.push_back_(right);
    return n;
  }

  inline const vsx_string& operator+=(const char& right) VSX_ALWAYS_INLINE
  {
    push_back(right);
    return *this;
  }
  
  inline friend const vsx_string operator+(const char* left, const vsx_string& right) VSX_ALWAYS_INLINE
  {
    vsx_string n;
    size_t i = 0;
    while (left[i] != 0)
    {
      n.push_back_(left[i]);
      ++i;
    }
    i = 0;
    while (i < right.size()) {
      n.push_back_(right[i]);
      ++i;
    }
    return n;
  }


  inline friend int operator==(const vsx_string& left,const vsx_string& right) VSX_ALWAYS_INLINE
  {
    if (left.size() != right.size()) return 0;
    return !strcmp(left.c_str(), right.c_str());
  }

  inline friend int operator<(const vsx_string& left,const vsx_string& right) VSX_ALWAYS_INLINE
  {
    return strcmp(left.c_str(), right.c_str())<0;
  }

  inline friend int operator<=(const vsx_string& left,const vsx_string& right) VSX_ALWAYS_INLINE
  {
    return strcmp(left.c_str(), right.c_str())<=0;
  }

  inline friend int operator>(const vsx_string& left,const vsx_string& right) VSX_ALWAYS_INLINE
  {
    return strcmp(left.c_str(), right.c_str())>0;
  }

  inline friend int operator>=(const vsx_string& left,const vsx_string& right) VSX_ALWAYS_INLINE
  {
    return strcmp(left.c_str(), right.c_str())>=0;
  }

  inline friend int operator!=(const vsx_string& left,const vsx_string& right) VSX_ALWAYS_INLINE
  {
    if (left.size() != right.size()) return 1;
    return strcmp(left.c_str(), right.c_str());
  }
 
  inline int find(const vsx_string& search, int start = 0) const VSX_ALWAYS_INLINE
  {
    if (search.size() == 0) return 0;
    size_t found = 0; // if this is equal to search.size() we're done
    if (start > (int)size()) return -1;
		if (start < 0) return -1;
    for (; start < (int)size(); ++start)
    {
      if (data[start] == search[found])
      {
        ++found;
        if (found == search.size()) 
        {
          int f = start-(found-1);
          if (f < 0) return 0; else
          return f;
        }
      } else found = 0;
    }
    return -1;
  }

  inline const vsx_string substr(int start, int length = -1) VSX_ALWAYS_INLINE
  {
    vsx_string n;
    zero_remove();
    if (length == -1) length = size();
    if (start < 0) {
    	int s = -start;
    	start = size()-s;
    	if (length == -1)
    	length = s;
    	else
    	if (length > s) length = s;
    }
    if (start < (int)size()) {
      while (start < (int)size() && length) {
        n.push_back(data[start]);
        ++start;
        --length;
      }
    }
    return n;
  }
  
  inline void insert(int pos, char key) VSX_ALWAYS_INLINE
  {
    *this = substr(0,pos) + key + substr(pos);
  }

  inline void erase(int pos, int num) VSX_ALWAYS_INLINE
  {
    *this = substr(0,pos) + substr(pos+num);
  }

  inline void trim_lf() VSX_ALWAYS_INLINE
  {
    if ( !this->size() ) return;
    if ( (*this)[this->size()-1] == 0x0A ) this->pop_back();
    if ( (*this)[this->size()-1] == 0x0D ) this->pop_back();
  }

};


#endif
