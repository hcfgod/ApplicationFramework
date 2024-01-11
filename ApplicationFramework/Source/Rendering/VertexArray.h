#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Visionary
{
    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void Bind() const;
        void Unbind() const;
        unsigned int GetRendererID() const;
    private:
        unsigned int m_RendererID;
    };
}