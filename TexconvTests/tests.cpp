#include "Texconv.h"

int main()
{
    TextureConversion::TexconvConversionParams params;

    params.format = DXGI_FORMAT_BC1_UNORM;

    const uint64_t options =
        (1ull << OPT_MIPLEVELS) |
        (1ull << OPT_FORMAT) |
        (1ull << OPT_FIT_POWEROF2) |
        (1ull << OPT_OVERWRITE);

    TextureConversion::TextureMetadata metadata;
    std::vector<char*> data;


    TextureConversion::Convert(params, options, "pngTexture.png", metadata, data);
    return 0;
}
