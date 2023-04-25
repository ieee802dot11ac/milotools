#include "include/argparse.h"
#include "include/converters.h"
#include <stdlib.h>

int main(int const argc, char const *const *const argv)
{
	int exitCode = EXIT_SUCCESS;

	HXConverterArgs args;
	if ((exitCode = parse_args(argc, argv, &args)) != EXIT_SUCCESS)
		return exitCode;

	if ((exitCode = guess_filetypes_if_unknown(&args)) != EXIT_SUCCESS)
		return exitCode;

	if ((exitCode = convert(args)) != EXIT_SUCCESS)
		return exitCode;

	return exitCode;
}

bool is_conversion_supported(SUPPORTED_INPUT_FILETYPE in, SUPPORTED_OUTPUT_FILETYPE out)
{
	if (in == IFILETYPE_UNKNOWN || out == OFILETYPE_UNKNOWN)
		return false;

	if (in == IFILETYPE_HX_MESH && out == OFILETYPE_WAVEFRONT_OBJ)
		return true;

	if (in == IFILETYPE_HX_TEX && out == OFILETYPE_NETPBM_PAM)
		return true;

	return false;

	/* Until we can promise reliable conversions between various formats,
	 * we should just bruteforce check and not actually use this code.
	 * Note that the enum values were specifically designed along with the
	 * macros TYPE_MESH, TYPE_TEXTEXTURE, TYPE_MAT, etc. so that this code
	 * WILL work even if you uncomment it now.
	 */
	// return (in & TYPE_MASK) == (out & TYPE_MASK);
}


