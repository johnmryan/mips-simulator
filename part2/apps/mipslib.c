#include "mipslib.h"

void mips_printint(int n)
{
  asm volatile ("ori $v0, $0, 1");
  asm volatile ("syscall");
}

void mips_printchar(char a)
{
  asm volatile ("ori $v0, $0, 11");
  asm volatile ("syscall");
}

void mips_printstr(char *s)
{
  asm volatile ("ori $v0, $0, 4");
  asm volatile ("syscall");
}

void* mips_alloc(unsigned n)
{
  unsigned ptrVal;
  asm volatile ("ori $v0, $0, 9");
  asm volatile ("syscall");
  asm volatile ("sw $v0, 0(%0)" : "=r" (ptrVal));
  return (void*) ptrVal;
}

int mips_putchar(char c)
{
  asm volatile ("ori $v0, $0, 11");
  asm volatile ("syscall");
  return 0;
}

/*
 Copyright (c) 2004,2008 Kustaa Nyholm / SpareTimeLabs

 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this list
 of conditions and the following disclaimer.

 Redistributions in binary form must reproduce the above copyright notice, this
 list of conditions and the following disclaimer in the documentation and/or other
 materials provided with the distribution.

 Neither the name of the Kustaa Nyholm or SpareTimeLabs nor the names of its
 contributors may be used to endorse or promote products derived from this software
 without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 OF SUCH DAMAGE.

 ----------------------------------------------------------------------

 */

#define putchar(c) mips_putchar(c)

static char* bf;
static char buf[12];
static unsigned int num;
static char uc;
static char zs;

static void out(char c) {
  *bf++ = c;
}

static void outDgt(char dgt) {
  out(dgt+(dgt<10 ? '0' : (uc ? 'A' : 'a')-10));
  zs=1;
}

static void divOut(unsigned int div) {
  unsigned char dgt=0;
  while (num>=div) {
    num -= div;
    dgt++;
  }
  if (zs || dgt>0)
    outDgt(dgt);
}

void tfp_printf(char *fmt, ...)
{
  va_list va;
  char ch;
  char* p;

  va_start(va,fmt);

  while ((ch=*(fmt++))) {
    if (ch!='%') {
      putchar(ch);
    }
    else {
      char lz=0;
      char w=0;
      ch=*(fmt++);
      if (ch=='0') {
        ch=*(fmt++);
        lz=1;
      }
      if (ch>='0' && ch<='9') {
        w=0;
        while (ch>='0' && ch<='9') {
          w=(((w<<2)+w)<<1)+ch-'0';
          ch=*fmt++;
        }
      }
      bf=buf;
      p=bf;
      zs=0;
      switch (ch) {
      case 0:
        goto abort;
      case 'u':
      case 'd' :
        num=va_arg(va, unsigned int);
        if (ch=='d' && (int)num<0) {
          num = -(int)num;
          out('-');
        }
        divOut(1000000000);
        divOut(100000000);
        divOut(10000000);
        divOut(1000000);
        divOut(100000);
        divOut(10000);
        divOut(1000);
        divOut(100);
        divOut(10);
        outDgt(num);
        break;
      case 'x':
      case 'X' :
        uc= ch=='X';
        num=va_arg(va, unsigned int);
        divOut(0x10000000);
        divOut(0x1000000);
        divOut(0x100000);
        divOut(0x10000);
        divOut(0x1000);
        divOut(0x100);
        divOut(0x10);
        outDgt(num);
        break;
      case 'c' :
        out((char)(va_arg(va, int)));
        break;
      case 's' :
        p=va_arg(va, char*);
        break;
      case '%' :
        out('%');
      default:
        break;
      }
      *bf=0;
      bf=p;
      while (*bf++ && w > 0)
        w--;
      while (w-- > 0)
        putchar(lz ? '0' : ' ');
      while ((ch= *p++))
        putchar(ch);
    }
  }
  abort:;
  va_end(va);
}

