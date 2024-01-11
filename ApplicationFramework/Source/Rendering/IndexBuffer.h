#pragma once

namespace Visionary
{
    class IndexBuffer {
    public:
        IndexBuffer(const unsigned int* indices, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;
        unsigned int GetCount() const;
        unsigned int GetRendererID() const;
    private:
        unsigned int m_RendererID;
        unsigned int m_Count;
    };
}