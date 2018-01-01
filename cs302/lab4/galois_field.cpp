#include "galois_field.h"

#define GF_FIRST_BIT (1 << 31)
#define GF_MULTBY_TWO(p) (((p) & GF_FIRST_BIT) ? (((p) << 1) ^ pp) : (p) << 1);

Galois_Field::Galois_Field(int w)
{
  unsigned int pp, a, b, p, basep, exp, i, j;

  W = w;
  if (W == 8) {
    pp = 0x11d;
    Mult_Table_8.resize(256*256, 0);
    Div_Table_8.resize(256*256, 0);
    for (a = 1; a < 256; a++) {
      b = 1;
      p = a;
      do {
        Mult_Table_8[(a<<8)|b] = p;
        Div_Table_8[(p<<8)|b] = a;
        p <<= 1;
        if (p & (1 << 8)) p ^= pp;
        b <<= 1;
        if (b & (1 << 8)) b ^= pp;
      } while (b != 1);
    }
  } else if (W == 16) {
    pp = 0x1100b;
    Log_Table_16.resize(1 << 16);
    ILog_Table_16.resize(1 << 17);
    a = 1;
    b = 0;
    do {
      Log_Table_16[a] = b;
      ILog_Table_16[b] = a;
      ILog_Table_16[b+((1<<16)-1)] = a;
      b++;
      a <<= 1;
      if (a & (1 << 16)) a ^= pp;
    } while (a != 1);
  } else if (W == 32) {
    pp = 0x400007;
    Tables_32.resize(7);
    for (i = 0; i < 7; i++) Tables_32[i].resize(256*256);
    basep = 1;
    for (exp = 0; exp < 7; exp++) {
      for (j = 0; j < 256; j++) Tables_32[exp][j] = 0;
      for (i = 0; i < 256; i++) Tables_32[exp][(i<<8)]= 0;
      Tables_32[exp][(1<<8)|1] = basep;
      for (i = 2; i < 256; i++) {
        if (i&1) {
          p = Tables_32[exp][((i^1)<<8)|1];
          Tables_32[exp][(i<<8)|(1)] = p ^ basep;
        } else {
          p = Tables_32[exp][((i>>1)<<8)|1];
          Tables_32[exp][(i<<8)|(1)] = GF_MULTBY_TWO(p);
        }
      }
      for (i = 1; i < 256; i++) {
        p = Tables_32[exp][(i<<8)|(1)];
        for (j = 1; j < 256; j++) {
          if (j&1) {
            Tables_32[exp][(i<<8)|j] = Tables_32[exp][(i<<8)|(j^1)] ^ p;
          } else {
            Tables_32[exp][(i<<8)|j] = GF_MULTBY_TWO(Tables_32[exp][(i<<8)|(j>>1)]);
          }
        }
      }
      for (i = 0; i < 8; i++) basep = GF_MULTBY_TWO(basep);
    }
  } else {
    cerr << "Galois Fields only supported for w = 8, 16, 32\n";
  }
}

unsigned int Galois_Field::Multiply(unsigned int a, unsigned int b)
{
  unsigned int p, tb, i, j;
  switch (W) {
  case 8:
    return Mult_Table_8[(a<<8)|b];
    break;
  case 16:
    if (a == 0 || b == 0) return 0;
    return ILog_Table_16[Log_Table_16[a]+Log_Table_16[b]];
    break;
  case 32:
    p = 0;
    for (i = 0; i < 4; i++) {
      tb = b;
      for (j = 0; j < 4; j++) {
        p ^= Tables_32[i+j][((a&0xff)<<8)|(tb&0xff)];
        tb >>= 8;
      }
      a >>= 8;
    }
    return p;
  default:
    fprintf(stderr, "Multiply not implemented for w = %d\n", W);
    exit(1);
  }
}

unsigned int Galois_Field::Inverse(unsigned int a)
{
  unsigned int e_i, e_im1, e_ip1;
  unsigned int d_i, d_im1, d_ip1;
  unsigned int y_i, y_im1, y_ip1;
  unsigned int c_i;

  switch (W) {
  case 8:
    return Div_Table_8[(1<<8)|a];
    break;
  case 16:
    return Divide(1, a);
    break;
  case 32:

    if (a == 0) return -1;
    e_im1 = 0x400007;
    e_i = a;
    d_im1 = 32;
    for (d_i = d_im1-1; ((1 << d_i) & e_i) == 0; d_i--) ;
    y_i = 1;
    y_im1 = 0;
  
    while (e_i != 1) {
  
      e_ip1 = e_im1;
      d_ip1 = d_im1;
      c_i = 0;
  
      while (d_ip1 >= d_i) {
        c_i ^= (1 << (d_ip1 - d_i));
        e_ip1 ^= (e_i << (d_ip1 - d_i));
        d_ip1--;
        while ((e_ip1 & (1 << d_ip1)) == 0) d_ip1--;
      }
  
      y_ip1 = y_im1 ^ Multiply(c_i, y_i);
      y_im1 = y_i;
      y_i = y_ip1;
  
      e_im1 = e_i;
      d_im1 = d_i;
      e_i = e_ip1;
      d_i = d_ip1;
    }
  
    return y_i;
    break;
  default:
    fprintf(stderr, "Inverse not implemented for w = %d\n", W);
    exit(1);
  }
}

unsigned int Galois_Field::Divide(unsigned int a, unsigned int b)
{
  switch (W) {
  case 8:
    return Div_Table_8[(a<<8)|b];
    break;
  case 16:
    if (a == 0 || b == 0) return 0;
    return ILog_Table_16[((1<<16)-1)+Log_Table_16[a]-Log_Table_16[b]];
    break;
  case 32:
    return Multiply(a, Inverse(b));
  default:
    fprintf(stderr, "Divide not implemented for w = %d\n", W);
    exit(1);
  }
}
