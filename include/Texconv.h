#ifndef TEXCONV_H
#define TEXCONV_H

#include <dxgiformat.h>
#include <cstdint>

#define MAX_PATH          260

namespace DirectX
{
    enum TEX_FILTER_FLAGS : unsigned long
    {
        TEX_FILTER_DEFAULT = 0,

        TEX_FILTER_WRAP_U = 0x1,
        TEX_FILTER_WRAP_V = 0x2,
        TEX_FILTER_WRAP_W = 0x4,
        TEX_FILTER_WRAP = (TEX_FILTER_WRAP_U | TEX_FILTER_WRAP_V | TEX_FILTER_WRAP_W),
        TEX_FILTER_MIRROR_U = 0x10,
        TEX_FILTER_MIRROR_V = 0x20,
        TEX_FILTER_MIRROR_W = 0x40,
        TEX_FILTER_MIRROR = (TEX_FILTER_MIRROR_U | TEX_FILTER_MIRROR_V | TEX_FILTER_MIRROR_W),
        // Wrap vs. Mirror vs. Clamp filtering options

        TEX_FILTER_SEPARATE_ALPHA = 0x100,
        // Resize color and alpha channel independently

        TEX_FILTER_FLOAT_X2BIAS = 0x200,
        // Enable *2 - 1 conversion cases for unorm<->float and positive-only float formats

        TEX_FILTER_RGB_COPY_RED = 0x1000,
        TEX_FILTER_RGB_COPY_GREEN = 0x2000,
        TEX_FILTER_RGB_COPY_BLUE = 0x4000,
        // When converting RGB to R, defaults to using grayscale. These flags indicate copying a specific channel instead
        // When converting RGB to RG, defaults to copying RED | GREEN. These flags control which channels are selected instead.

        TEX_FILTER_DITHER = 0x10000,
        // Use ordered 4x4 dithering for any required conversions
        TEX_FILTER_DITHER_DIFFUSION = 0x20000,
        // Use error-diffusion dithering for any required conversions

        TEX_FILTER_POINT = 0x100000,
        TEX_FILTER_LINEAR = 0x200000,
        TEX_FILTER_CUBIC = 0x300000,
        TEX_FILTER_BOX = 0x400000,
        TEX_FILTER_FANT = 0x400000, // Equiv to Box filtering for mipmap generation
        TEX_FILTER_TRIANGLE = 0x500000,
        // Filtering mode to use for any required image resizing

        TEX_FILTER_SRGB_IN = 0x1000000,
        TEX_FILTER_SRGB_OUT = 0x2000000,
        TEX_FILTER_SRGB = (TEX_FILTER_SRGB_IN | TEX_FILTER_SRGB_OUT),
        // sRGB <-> RGB for use in conversion operations
        // if the input format type is IsSRGB(), then SRGB_IN is on by default
        // if the output format type is IsSRGB(), then SRGB_OUT is on by default

        TEX_FILTER_FORCE_NON_WIC = 0x10000000,
        // Forces use of the non-WIC path when both are an option

        TEX_FILTER_FORCE_WIC = 0x20000000,
        // Forces use of the WIC path even when logic would have picked a non-WIC path when both are an option
    };

    enum TEX_COMPRESS_FLAGS : unsigned long
    {
        TEX_COMPRESS_DEFAULT = 0,

        TEX_COMPRESS_RGB_DITHER = 0x10000,
        // Enables dithering RGB colors for BC1-3 compression

        TEX_COMPRESS_A_DITHER = 0x20000,
        // Enables dithering alpha for BC1-3 compression

        TEX_COMPRESS_DITHER = 0x30000,
        // Enables both RGB and alpha dithering for BC1-3 compression

        TEX_COMPRESS_UNIFORM = 0x40000,
        // Uniform color weighting for BC1-3 compression; by default uses perceptual weighting

        TEX_COMPRESS_BC7_USE_3SUBSETS = 0x80000,
        // Enables exhaustive search for BC7 compress for mode 0 and 2; by default skips trying these modes

        TEX_COMPRESS_BC7_QUICK = 0x100000,
        // Minimal modes (usually mode 6) for BC7 compression

        TEX_COMPRESS_SRGB_IN = 0x1000000,
        TEX_COMPRESS_SRGB_OUT = 0x2000000,
        TEX_COMPRESS_SRGB = (TEX_COMPRESS_SRGB_IN | TEX_COMPRESS_SRGB_OUT),
        // if the input format type is IsSRGB(), then SRGB_IN is on by default
        // if the output format type is IsSRGB(), then SRGB_OUT is on by default

        TEX_COMPRESS_PARALLEL = 0x10000000,
        // Compress is free to use multithreading to improve performance (by default it does not use multithreading)
    };

    enum CNMAP_FLAGS : unsigned long
    {
        CNMAP_DEFAULT = 0,

        CNMAP_CHANNEL_RED = 0x1,
        CNMAP_CHANNEL_GREEN = 0x2,
        CNMAP_CHANNEL_BLUE = 0x3,
        CNMAP_CHANNEL_ALPHA = 0x4,
        CNMAP_CHANNEL_LUMINANCE = 0x5,
        // Channel selection when evaluting color value for height
        // Luminance is a combination of red, green, and blue

        CNMAP_MIRROR_U = 0x1000,
        CNMAP_MIRROR_V = 0x2000,
        CNMAP_MIRROR = 0x3000,
        // Use mirror semantics for scanline references (defaults to wrap)

        CNMAP_INVERT_SIGN = 0x4000,
        // Inverts normal sign

        CNMAP_COMPUTE_OCCLUSION = 0x8000,
        // Computes a crude occlusion term stored in the alpha channel
    };

    constexpr float TEX_THRESHOLD_DEFAULT = 0.5f;
        // Default value for alpha threshold used when converting to 1-bit alpha
}

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

    enum
    {
        ROTATE_709_TO_HDR10 = 1,
        ROTATE_HDR10_TO_709,
        ROTATE_709_TO_2020,
        ROTATE_2020_TO_709,
        ROTATE_P3D65_TO_HDR10,
        ROTATE_P3D65_TO_2020,
        ROTATE_709_TO_P3D65,
        ROTATE_P3D65_TO_709,
    };

    static_assert(OPT_MAX <= 64, "dwOptions is a unsigned int bitfield");

    struct SConversion
    {
        wchar_t szSrc[MAX_PATH];
        wchar_t szFolder[MAX_PATH];
    };

    template<typename T>
    struct SValue
    {
        const wchar_t*  name;
        T               value;
    };

    #define CODEC_DDS 0xFFFF0001
    #define CODEC_TGA 0xFFFF0002
    #define CODEC_HDP 0xFFFF0003
    #define CODEC_JXR 0xFFFF0004
    #define CODEC_HDR 0xFFFF0005
    #define CODEC_PPM 0xFFFF0006
    #define CODEC_PFM 0xFFFF0007

    #ifdef USE_OPENEXR
    #define CODEC_EXR 0xFFFF0008
    #endif
}

namespace TextureConversion
{
    struct TexconvConversionParams
    {
        size_t width = 0;
        size_t height = 0;
        size_t mipLevels = 0;
        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
        DirectX::TEX_FILTER_FLAGS dwFilter = DirectX::TEX_FILTER_DEFAULT;
        DirectX::TEX_FILTER_FLAGS dwSRGB = DirectX::TEX_FILTER_DEFAULT;
        DirectX::TEX_FILTER_FLAGS dwConvert = DirectX::TEX_FILTER_DEFAULT;
        DirectX::TEX_COMPRESS_FLAGS dwCompress = DirectX::TEX_COMPRESS_DEFAULT;
        DirectX::TEX_FILTER_FLAGS dwFilterOpts = DirectX::TEX_FILTER_DEFAULT;
        uint32_t FileType = CODEC_DDS;
        uint32_t maxSize = 16384;
        int adapter = -1;
        float alphaThreshold = DirectX::TEX_THRESHOLD_DEFAULT;
        float alphaWeight = 1.f;
        DirectX::CNMAP_FLAGS dwNormalMap = DirectX::CNMAP_DEFAULT;
        float nmapAmplitude = 1.f;
        float wicQuality = -1.f;
        uint32_t colorKey = 0;
        uint32_t dwRotateColor = 0;
        float paperWhiteNits = 200.f;
        float preserveAlphaCoverageRef = 0.0f;
        bool keepRecursiveDirs = false;
    };


    int Convert(TexconvConversionParams* params, uint64_t options, const char* filePath);
}
#endif // TEXCONV_H
