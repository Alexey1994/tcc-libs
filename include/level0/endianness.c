#ifndef ENDIANNESS_INCLUDED
#define ENDIANNESS_INCLUDED


#define LITTLE_ENDIAN 1234
#define BIG_ENDIAN 4321


#define BYTE_ORDER LITTLE_ENDIAN


#if BYTE_ORDER == LITTLE_ENDIAN

#define get_big_endian_Number16(x) (((x & 0x00FF) << 8) \
	| ((x & 0xFF00) >> 8))

#define get_big_endian_Number32(x) (((x & 0x000000FF) << 24) \
	| ((x & 0x0000FF00) << 8) \
	| ((x & 0x00FF0000) >> 8) \
	| ((x & 0xFF000000) >> 24))

#define get_big_endian_Number64(x) (((x & 0x00000000000000FF) << 56) \
	| ((x & 0x000000000000FF00) << 40) \
	| ((x & 0x0000000000FF0000) << 24) \
	| ((x & 0x00000000FF000000) << 8) \
	| ((x & 0x000000FF00000000) >> 8) \
	| ((x & 0x0000FF0000000000) >> 24) \
	| ((x & 0x00FF000000000000) >> 40) \
	| ((x & 0xFF00000000000000) >> 56))

#define get_little_endian_Number16(x) x
#define get_little_endian_Number32(x) x
#define get_little_endian_Number64(x) x

#endif


#if BYTE_ORDER == BIG_ENDIAN

#define get_big_endian_Number16(x) x
#define get_big_endian_Number32(x) x
#define get_big_endian_Number64(x) x

#define get_little_endian_Number16(x) (((x & 0x00FF) << 8) \
	| ((x & 0xFF00) >> 8))

#define get_little_endian_Number32(x) (((x & 0x000000FF) << 24) \
	| ((x & 0x0000FF00) << 8) \
	| ((x & 0x00FF0000) >> 8) \
	| ((x & 0xFF000000) >> 24))

#define get_little_endian_Number64(x) (((x & 0x00000000000000FF) << 56) \
	| ((x & 0x000000000000FF00) << 40) \
	| ((x & 0x0000000000FF0000) << 24) \
	| ((x & 0x00000000FF000000) << 8) \
	| ((x & 0x000000FF00000000) >> 8) \
	| ((x & 0x0000FF0000000000) >> 24) \
	| ((x & 0x00FF000000000000) >> 40) \
	| ((x & 0xFF00000000000000) >> 56))

#endif


#endif//ENDIANNESS_INCLUDED