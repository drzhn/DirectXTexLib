#include "Texconv.h"
#include "Blob.h"

#include <fstream>

#include "../DirectXTex/DirectXTex.h"

int main()
{
    AssetConversion::TextureConversionParams params;

    const uint64_t options =
        (1ull << OPT_MIPLEVELS) |
        (1ull << OPT_FORMAT) |
        (1ull << OPT_FIT_POWEROF2) |
        (1ull << OPT_USE_DX10);

    int result = AssetConversion::TextureConversionInit(true, true, COINIT_MULTITHREADED);

    {
        params.format = DXGI_FORMAT_BC1_UNORM;

        AssetConversion::TextureMetadata metadata;
        Blob blob;

        result = AssetConversion::Convert(params, options, "pngTexture.png", metadata, blob);
        bool isHDR = AssetConversion::IsHDR("pngTexture.png");
        std::ofstream fout;
        fout.open("pngTexture.dds", std::ios::binary | std::ios::out);

        fout.write(static_cast<char*>(blob.GetBufferPointer()), blob.GetBufferSize());

        fout.close();
    }

    {
        params.format = DXGI_FORMAT_BC6H_UF16;

        AssetConversion::TextureMetadata metadata;
        Blob blob;

        result = AssetConversion::Convert(params, options, "hdrTexture.hdr", metadata, blob);
        bool isHDR = AssetConversion::IsHDR("hdrTexture.hdr");

        std::ofstream fout;
        fout.open("hdrTexture.dds", std::ios::binary | std::ios::out);

        fout.write(static_cast<char*>(blob.GetBufferPointer()), blob.GetBufferSize());

        fout.close();
    }

    return 0;
}
