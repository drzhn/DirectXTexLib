#include "Texconv.h"
#include "Blob.h"

#include <fstream>

int main()
{
    AssetConversion::TextureConversionParams params;

    params.format = DXGI_FORMAT_BC1_UNORM;

    const uint64_t options =
        (1ull << OPT_MIPLEVELS) |
        (1ull << OPT_FORMAT) |
        (1ull << OPT_FIT_POWEROF2);

    AssetConversion::TextureMetadata metadata;
    Blob blob;


    AssetConversion::Convert(params, options, "pngTexture.png", metadata, blob);

    std::ofstream fout;
    fout.open("pngTexture.dds", std::ios::binary | std::ios::out);

    fout.write(static_cast<char*>(blob.GetBufferPointer()), blob.GetBufferSize());

    fout.close();
    return 0;
}
