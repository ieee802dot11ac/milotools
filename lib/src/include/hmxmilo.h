// hmxmilo.h - Harmonix Milo "scene"s (officially ObjectDirs but that's a boring name)
#ifndef HMXMILO_H
#define HMXMILO_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmx.h"
#include "hmxui.h"
#include "hmxtexture.h"
#include "hmxtransanim.h"

typedef enum {
	/// <summary>
	/// Raw data. Uncompressed.
	/// </summary>
	NONE = 0,
	/// <summary>
	/// Raw data. Compressed with GZip.
	/// <para>*FreQ</para>
	/// </summary>
	GZIP = 1,
	/// <summary>
	/// Structured as milo. No compression.
	/// <para>*RBN</para>
	/// </summary>
	MILO_A = 0xCA,
	/// <summary>
	/// Structured as milo. Compressed with ZLib.
	/// <para>*GH1</para>
	/// <para>*GH2</para>
	/// <para>*GH80's</para>
	/// <para>*RB1</para>
	/// <para>*RBTP Vol. 1</para>
	/// <para>*RB2</para>
	/// <para>*ACDC RB</para>
	/// <para>*RBTB Vol. 2</para>
	/// <para>*RBTP Classic Rock</para>
	/// <para>*RBTP Country</para>
	/// <para>*TBRB</para>
	/// <para>*RBTP Metal</para>
	/// <para>*LRB</para>
	/// <para>*GDRB</para>
	/// <para>*RBTP Country 2</para>
	/// </summary>
	MILO_B = 0xCB,
	/// <summary>
	/// Structured as milo. Compressed with GZip.
	/// <para>*Amp</para>
	/// <para>*KR1</para>
	/// <para>*KR2</para>
	/// <para>*KR3</para>
	/// </summary>
	MILO_C = 0xCC,
	/// <summary>
	/// Structured as milo. Compressed with ZLib.
	/// <para>*RB3</para>
	/// <para>*DC1</para>
	/// <para>*DC2</para>
	/// <para>*RBB</para>
	/// <para>*DC3</para>
	/// </summary>
	MILO_D = 0xCD
} BlockStructure;

typedef struct {
	char* type;
	char* name;
	union {
		HX_BUTTON_EX buttonx;
		HX_CAMERA camera;
		HX_ENVIRON environment;
		HX_LABEL_EX labelx;
		HX_LIGHT light;
		HX_MATERIAL material;
		HX_MESH mesh;
		HX_PICTURE_EX picturex;
		HX_TEXTURE texture;
		HX_TRANSFORM transform;
		HX_TRANSFORM_ANIM transanim;
		HX_UI_BUTTON button;
		HX_UI_COLOR color;
		HX_UI_COMPONENT component;
		HX_UI_LABEL label;
		HX_UI_LIST list;
	}; // if you run into more, god help you
} HX_MILOOBJECT;

typedef struct {
	HX_STRING type;
	HX_STRING name;

	u32 offset;
	u32 size;
} HX_MILOENTRY;

typedef struct {
	HX_STRING dir_type; // class_name
	HX_STRING dir_name;

	// String table info for names/classes
	u32 string_table_string_count;
	u32 string_table_used_size;
	// those guys were >v10. these are normal
	i32 entry_count;
	HX_MILOENTRY* entries;
} HX_MILOENTRIES;

typedef struct {
	i32 ext_count;
	HX_STRING* ext_paths;
} HX_EXTERNALRESOURCES;

typedef struct {
	i32 version; // 6 (Freq), 10 (Amp/GH1), 24 (GH2), 25 (GDRB), 28 (RBN/DC1), 32 (DC2/DC3)
	HX_MILOENTRIES meta;

	// Used in GH1-era games
	// Paths usually reference external textures
	// Note: Can be collection of nulls
	HX_EXTERNALRESOURCES resources; // v10 only!

	HX_MILOOBJECT dirEntry; // v11+

	HX_MILOOBJECT* children;
} HX_MILOFILE;

typedef struct {
	u8 version[4]; // one of: 0, 1, 0xCABEDEAF, 0xCBBEDEAF, 0xCCBEDEAF, 0xCDBEDEAF (LE)
	u32 offset;
	i32 blockCount;
	i32 maxBlockSize; // in effect this limits the max block size to 4 gibibytes but if you're making a milo that big please stop
	u32* sizes; // blockCount wide
} HX_MILOHEADER;

int hmx_milo_decompress(FILE* file, char *outfilename);
int hmx_milo_compress(FILE* file, char *outfilename, BlockStructure mode);
HX_MILOFILE *hmx_milo_load (FILE *file);
void hmx_milo_cleanup(HX_MILOFILE* milo);
void hmx_milo_print(HX_MILOFILE* milo);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
