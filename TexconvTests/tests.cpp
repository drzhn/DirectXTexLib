#include "Texconv.h"

int main()
{
    TextureConversion::TexconvConversionParams params;

    params.format = DXGI_FORMAT_BC1_UNORM;

    uint64_t options =
        (1 << OPT_MIPLEVELS) |
        (1 << OPT_FORMAT) |
        (1 << OPT_FIT_POWEROF2) |
        (1 << OPT_OVERWRITE);

    TextureConversion::Convert(&params, options, "pngTexture.png");
    return 0;
}
