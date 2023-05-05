#ifndef BLOB_H
#define BLOB_H

#include <intsafe.h>
#include <utility>

//---------------------------------------------------------------------------------
// Memory blob (allocated buffer pointer is always 16-byte aligned)
class Blob
{
public:
    Blob() noexcept : m_buffer(nullptr), m_size(0)
    {
    }

    Blob(Blob&& moveFrom) noexcept : m_buffer(nullptr), m_size(0) { *this = std::move(moveFrom); }
    ~Blob() { Release(); }

    Blob& __cdecl operator=(Blob&& moveFrom) noexcept;

    Blob(const Blob&) = delete;
    Blob& operator=(const Blob&) = delete;

    HRESULT __cdecl Initialize(_In_ size_t size) noexcept;

    void __cdecl Release() noexcept;

    void*__cdecl GetBufferPointer() const noexcept { return m_buffer; }
    size_t __cdecl GetBufferSize() const noexcept { return m_size; }

    HRESULT __cdecl Resize(size_t size) noexcept;
    // Reallocate for a new size

    HRESULT __cdecl Trim(size_t size) noexcept;
    // Shorten size without reallocation

private:
    void* m_buffer;
    size_t m_size;
};
#endif // BLOB_H
