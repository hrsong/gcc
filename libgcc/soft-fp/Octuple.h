/* Software floating-point emulation.

   Definitions for IEEE Octuple Precision.

   Coded by: Howard Song */



#ifndef SOFT_FP_OCTUPLE_H

#define SOFT_FP_OCTUPLE_H	1



#if _FP_W_TYPE_SIZE < 64

# error "Here's a nickel, kid. Go buy yourself a real computer."

#endif



#if _FP_W_TYPE_SIZE < 128

# define _FP_FRACTBITS_O	(4*_FP_W_TYPE_SIZE)

# define _FP_FRACTBITS_DW_O	(8*_FP_W_TYPE_SIZE)

#endif



#define _FP_FRACBITS_O		237

#define _FP_FRACXBITS_O		(_FP_FRACTBITS_O - _FP_FRACBITS_O)

#define _FP_WFRACBITS_O		(_FP_WORKBITS + _FP_FRACBITS_O)

#define _FP_WFRACXBITS_O	(_FP_FRACTBITS_O - _FP_WFRACBITS_O)

#define _FP_EXPBITS_O		19

#define _FP_EXPBIAS_O		262143

#define _FP_EXPMAX_O		524287



#define _FP_QNANBIT_O		\

	((_FP_W_TYPE) 1 << (_FP_FRACBITS_O-2) % _FP_W_TYPE_SIZE)

#define _FP_QNANBIT_SH_O		\

	((_FP_W_TYPE) 1 << (_FP_FRACBITS_O-2+_FP_WORKBITS) % _FP_W_TYPE_SIZE)

#define _FP_IMPLBIT_O		\

	((_FP_W_TYPE) 1 << (_FP_FRACBITS_O-1) % _FP_W_TYPE_SIZE)

#define _FP_IMPLBIT_SH_O		\

	((_FP_W_TYPE) 1 << (_FP_FRACBITS_O-1+_FP_WORKBITS) % _FP_W_TYPE_SIZE)

#define _FP_OVERFLOW_O		\

	((_FP_W_TYPE) 1 << (_FP_WFRACBITS_O % _FP_W_TYPE_SIZE))



#define _FP_WFRACBITS_DW_O	(2 * _FP_WFRACBITS_O)

#define _FP_WFRACXBITS_DW_O	(_FP_FRACTBITS_DW_O - _FP_WFRACBITS_DW_O)

#define _FP_HIGHBIT_DW_O	\

  ((_FP_W_TYPE) 1 << (_FP_WFRACBITS_DW_Q - 1) % _FP_W_TYPE_SIZE)



typedef float TFtype __attribute__ ((mode (TF)));



#if _FP_W_TYPE_SIZE < 128



union _FP_UNION_O

{

  TFtype flt;

  struct _FP_STRUCT_LAYOUT

  {

# if __BYTE_ORDER == __BIG_ENDIAN

    unsigned sign : 1;

    unsigned exp : _FP_EXPBITS_O;

    unsigned long frac3 : _FP_FRACBITS_O - (_FP_IMPLBIT_O != 0)-(_FP_W_TYPE_SIZE * 3);

    unsigned long frac2 : _FP_W_TYPE_SIZE;

    unsigned long frac1 : _FP_W_TYPE_SIZE;

    unsigned long frac0 : _FP_W_TYPE_SIZE;

# else

    unsigned long frac0 : _FP_W_TYPE_SIZE;

    unsigned long frac1 : _FP_W_TYPE_SIZE;

    unsigned long frac2 : _FP_W_TYPE_SIZE;

    unsigned long frac3 : _FP_FRACBITS_O - (_FP_IMPLBIT_O != 0)-(_FP_W_TYPE_SIZE * 3);

    unsigned exp : _FP_EXPBITS_O;

    unsigned sign : 1;

# endif /* not bigendian */

  } bits;

};





# define FP_DECL_O(X)		_FP_DECL (4, X)

# define FP_UNPACK_RAW_O(X, val)	_FP_UNPACK_RAW_4 (O, X, (val))

# define FP_UNPACK_RAW_OP(X, val)	_FP_UNPACK_RAW_4_P (O, X, (val))

# define FP_PACK_RAW_O(val, X)	_FP_PACK_RAW_4 (O, (val), X)

# define FP_PACK_RAW_OP(val, X)			\

  do						\

    {						\

      if (!FP_INHIBIT_RESULTS)			\

	_FP_PACK_RAW_4_P (O, (val), X);		\

    }						\

  while (0)



# define FP_UNPACK_O(X, val)			\

  do						\

    {						\

      _FP_UNPACK_RAW_4 (O, X, (val));		\

      _FP_UNPACK_CANONICAL (O, 4, X);		\

    }						\

  while (0)



# define FP_UNPACK_QP(X, val)			\

  do						\

    {						\

      _FP_UNPACK_RAW_4_P (O, X, (val));		\

      _FP_UNPACK_CANONICAL (O, 4, X);		\

    }						\

  while (0)



# define FP_UNPACK_SEMIRAW_O(X, val)		\

  do						\

    {						\

      _FP_UNPACK_RAW_4 (O, X, (val));		\

      _FP_UNPACK_SEMIRAW (O, 4, X);		\

    }						\

  while (0)



# define FP_UNPACK_SEMIRAW_OP(X, val)		\

  do						\

    {						\

      _FP_UNPACK_RAW_4_P (O, X, (val));		\

      _FP_UNPACK_SEMIRAW (O, 4, X);		\

    }						\

  while (0)



# define FP_PACK_O(val, X)			\

  do						\

    {						\

      _FP_PACK_CANONICAL (O, 4, X);		\

      _FP_PACK_RAW_4 (O, (val), X);		\

    }						\

  while (0)



# define FP_PACK_OP(val, X)			\

  do						\

    {						\

      _FP_PACK_CANONICAL (O, 4, X);		\

      if (!FP_INHIBIT_RESULTS)			\

	_FP_PACK_RAW_4_P (O, (val), X);		\

    }						\

  while (0)



# define FP_PACK_SEMIRAW_O(val, X)		\

  do						\

    {						\

      _FP_PACK_SEMIRAW (O, 4, X);		\

      _FP_PACK_RAW_4 (O, (val), X);		\

    }						\

  while (0)



# define FP_PACK_SEMIRAW_OP(val, X)		\

  do						\

    {						\

      _FP_PACK_SEMIRAW (O, 4, X);		\

      if (!FP_INHIBIT_RESULTS)			\

	_FP_PACK_RAW_4_P (O, (val), X);		\

    }						\

  while (0)



# define FP_ISSIGNAN_O(X)		_FP_ISSIGNAN (O, 4, X)

# define FP_NEG_O(R, X)			_FP_NEG (O, 4, R, X)

# define FP_ADD_O(R, X, Y)		_FP_ADD (O, 4, R, X, Y)

# define FP_SUB_O(R, X, Y)		_FP_SUB (O, 4, R, X, Y)

# define FP_MUL_O(R, X, Y)		_FP_MUL (O, 4, R, X, Y)

# define FP_DIV_O(R, X, Y)		_FP_DIV (O, 4, R, X, Y)

# define FP_SQRT_O(R, X)		_FP_SQRT (O, 4, R, X)

# define _FP_SQRT_MEAT_O(R, S, T, X, Q)	_FP_SQRT_MEAT_4 (R, S, T, X, (O))

# define FP_FMA_O(R, X, Y, Z)		_FP_FMA (O, 4, 8, R, X, Y, Z)



# define FP_CMP_O(r, X, Y, un, ex)	_FP_CMP (O, 4, (r), X, Y, (un), (ex))

# define FP_CMP_EQ_O(r, X, Y, ex)	_FP_CMP_EQ (O, 4, (r), X, Y, (ex))

# define FP_CMP_UNORD_O(r, X, Y, ex)	_FP_CMP_UNORD (O, 4, (r), X, Y, (ex))



# define FP_TO_INT_O(r, X, rsz, rsg)	_FP_TO_INT (O, 4, (r), X, (rsz), (rsg))

# define FP_TO_INT_ROUND_O(r, X, rsz, rsg)	\

  _FP_TO_INT_ROUND (O, 4, (r), X, (rsz), (rsg))

# define FP_FROM_INT_O(X, r, rs, rt)	_FP_FROM_INT (O, 4, X, (r), (rs), rt)



# define _FP_FRAC_HIGH_O(X)	_FP_FRAC_HIGH_4 (X)

# define _FP_FRAC_HIGH_RAW_O(X)	_FP_FRAC_HIGH_4 (X)



# define _FP_FRAC_HIGH_DW_O(X)	_FP_FRAC_HIGH_8 (X)

#endif /* not _FP_W_TYPE_SIZE < 128 */



#endif /* !SOFT_FP_OCTUPLE_H */
