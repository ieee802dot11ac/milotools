// filetypes.h - Supported filetypes
/* LICENSE */
#ifndef FILETYPES_H
#define FILETYPES_H
#ifdef __cplusplus
extern "C" {
#endif


#define BIT(n)			(1 << n)
#define BITS(length)		(BIT(length) - 1)
#define BITMASK(length, shift)	(BITS(length) << shift)

#define FORMAT_SHIFT		0
#define FORMAT_BIT_COUNT	4
#define FORMAT_MASK		BITMASK(FORMAT_BIT_COUNT, FORMAT_SHIFT)
#define FORMAT(n)		((n & BITS(FORMAT_BIT_COUNT)) << FORMAT_SHIFT)

#define TYPE_SHIFT		FORMAT_BIT_COUNT
#define TYPE_BIT_COUNT		4
#define TYPE_MASK		BITMASK(TYPE_BIT_COUNT, TYPE_SHIFT)
#define TYPE(n)			((n & BITS(TYPE_BIT_COUNT)) << TYPE_SHIFT)

#define TYPE_MESH		TYPE(0)
#define TYPE_TEXTURE	TYPE(1)
#define TYPE_MATERIAL	TYPE(2)
#define TYPE_SCENE		TYPE(3)
#define TYPE_LIGHT		TYPE(4)
#define TYPE_CAMERA		TYPE(5)
#define TYPE_ENVIRONMENT    TYPE(6)
#define TYPE_UI_LABEL	TYPE(7)
#define TYPE_UI_BUTTON	TYPE(8)
#define TYPE_MILO		TYPE(9)
#define TYPE_DIRECTORY	TYPE(10)
#define TYPE_ANIMATION	TYPE(11)


typedef enum {
	IFILETYPE_UNKNOWN	= -1,
	IFILETYPE_HX_MESH	= TYPE_MESH	| FORMAT(0),
	IFILETYPE_HX_TEX	= TYPE_TEXTURE	| FORMAT(0),
	IFILETYPE_HX_BMP	= TYPE_TEXTURE	| FORMAT(1),
	IFILETYPE_HX_MAT	= TYPE_MATERIAL	| FORMAT(0),
	IFILETYPE_HX_LIT	= TYPE_LIGHT	| FORMAT(0),
	IFILETYPE_HX_CAM	= TYPE_CAMERA	| FORMAT(0),
	IFILETYPE_HX_ENVIRON	= TYPE_ENVIRONMENT	| FORMAT(0),
	IFILETYPE_HX_LBLX	= TYPE_UI_LABEL	| FORMAT(0),
	IFILETYPE_HX_BTNX	= TYPE_UI_BUTTON	| FORMAT(0),
	IFILETYPE_HX_PICX	= TYPE_TEXTURE	| FORMAT(2),
	IFILETYPE_HX_MILO	= TYPE_MILO	| FORMAT(0),
	IFILETYPE_HX_RAWMILO	= TYPE_MILO	| FORMAT(1),
	IFILETYPE_DIR	= TYPE_DIRECTORY| FORMAT(0),
	IFILETYPE_HX_ARK	= TYPE_DIRECTORY| FORMAT(1),
	IFILETYPE_HX_TNM	= TYPE_ANIMATION| FORMAT(1),
} SUPPORTED_INPUT_FILETYPE;

typedef enum {
	OFILETYPE_UNKNOWN	= -1,
	OFILETYPE_WAVEFRONT_OBJ	= TYPE_MESH	| FORMAT(0),
	OFILETYPE_WAVEFRONT_MTL	= TYPE_MATERIAL	| FORMAT(0),
	OFILETYPE_NETPBM_PAM	= TYPE_TEXTURE	| FORMAT(0),
	OFILETYPE_PNG		= TYPE_TEXTURE	| FORMAT(1),
	OFILETYPE_HX_MILO	= TYPE_MILO	| FORMAT(0),
	OFILETYPE_HX_RAWMILO	= TYPE_MILO	| FORMAT(1),
	OFILETYPE_DIR		= TYPE_DIRECTORY	| FORMAT(0), // maybe do autozip? instant ark?
	OFILETYPE_HX_ARK	= TYPE_DIRECTORY	| FORMAT(1),
} SUPPORTED_OUTPUT_FILETYPE;


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
