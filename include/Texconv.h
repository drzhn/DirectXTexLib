#ifndef TEXCONV_H
#define TEXCONV_H

#include <dxgiformat.h>
#include <cstdint>

class Blob;

namespace
{
    enum OPTIONS : uint64_t
    {
        OPT_RECURSIVE = 1,
        OPT_FILELIST,
        OPT_WIDTH,
        OPT_HEIGHT,
        OPT_MIPLEVELS,
        OPT_FORMAT,
        OPT_FILTER,
        OPT_SRGBI,
        OPT_SRGBO,
        OPT_SRGB,
        OPT_PREFIX,
        OPT_SUFFIX,
        OPT_OUTPUTDIR,
        OPT_TOLOWER,
        OPT_OVERWRITE,
        OPT_FILETYPE,
        OPT_HFLIP,
        OPT_VFLIP,
        OPT_DDS_DWORD_ALIGN,
        OPT_DDS_BAD_DXTN_TAILS,
        OPT_USE_DX10,
        OPT_USE_DX9,
        OPT_TGA20,
        OPT_WIC_QUALITY,
        OPT_WIC_LOSSLESS,
        OPT_WIC_MULTIFRAME,
        OPT_NOLOGO,
        OPT_TIMING,
        OPT_SEPALPHA,
        OPT_NO_WIC,
        OPT_TYPELESS_UNORM,
        OPT_TYPELESS_FLOAT,
        OPT_PREMUL_ALPHA,
        OPT_DEMUL_ALPHA,
        OPT_EXPAND_LUMINANCE,
        OPT_TA_WRAP,
        OPT_TA_MIRROR,
        OPT_FORCE_SINGLEPROC,
        OPT_GPU,
        OPT_NOGPU,
        OPT_FEATURE_LEVEL,
        OPT_FIT_POWEROF2,
        OPT_ALPHA_THRESHOLD,
        OPT_ALPHA_WEIGHT,
        OPT_NORMAL_MAP,
        OPT_NORMAL_MAP_AMPLITUDE,
        OPT_BC_COMPRESS,
        OPT_COLORKEY,
        OPT_TONEMAP,
        OPT_X2_BIAS,
        OPT_PRESERVE_ALPHA_COVERAGE,
        OPT_INVERT_Y,
        OPT_RECONSTRUCT_Z,
        OPT_ROTATE_COLOR,
        OPT_PAPER_WHITE_NITS,
        OPT_BCNONMULT4FIX,
        OPT_SWIZZLE,
        OPT_MAX
    };
}

namespace AssetConversion
{
    struct TextureMetadata
    {
        size_t width;
        size_t height; // Should be 1 for 1D textures
        size_t depth; // Should be 1 for 1D or 2D textures
        size_t arraySize; // For cubemap, this is a multiple of 6
        size_t mipLevels;
        DXGI_FORMAT format;
    };

    struct TextureConversionParams
    {
        size_t width = 0;
        size_t height = 0;
        size_t mipLevels = 0;
        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
    };

    int TextureConversionInit();

    int Convert(
        const TextureConversionParams& params,
        uint64_t options,
        const char* filePath,
        TextureMetadata& outMetadata,
        Blob& outBlob
    );

    bool IsHDR(const char* filePath);
}
#endif // TEXCONV_H
