//=====================================================================================
// Blob - Bitmap image container
//=====================================================================================
#include "Blob.h"

#include <cstring>

#include "Winerror.h"


Blob& Blob::operator= (Blob&& moveFrom) noexcept
{
    if (this != &moveFrom)
    {
        Release();

        m_buffer = moveFrom.m_buffer;
        m_size = moveFrom.m_size;

        moveFrom.m_buffer = nullptr;
        moveFrom.m_size = 0;
    }
    return *this;
}

void Blob::Release() noexcept
{
    if (m_buffer)
    {
        _aligned_free(m_buffer);
        m_buffer = nullptr;
    }

    m_size = 0;
}

_Use_decl_annotations_
HRESULT Blob::Initialize(size_t size) noexcept
{
    if (!size)
        return E_INVALIDARG;

    Release();

    m_buffer = _aligned_malloc(size, 16);
    if (!m_buffer)
    {
        Release();
        return E_OUTOFMEMORY;
    }

    m_size = size;

    return S_OK;
}

HRESULT Blob::Trim(size_t size) noexcept
{
    if (!size)
        return E_INVALIDARG;

    if (!m_buffer)
        return E_UNEXPECTED;

    if (size > m_size)
        return E_INVALIDARG;

    m_size = size;

    return S_OK;
}

HRESULT Blob::Resize(size_t size) noexcept
{
    if (!size)
        return E_INVALIDARG;

    if (!m_buffer || !m_size)
        return E_UNEXPECTED;

    void *tbuffer = _aligned_malloc(size, 16);
    if (!tbuffer)
        return E_OUTOFMEMORY;

    memcpy(tbuffer, m_buffer, std::min(m_size, size));

    Release();

    m_buffer = tbuffer;
    m_size = size;

    return S_OK;
}
