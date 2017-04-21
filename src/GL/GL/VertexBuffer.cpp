/*
	Copyright (C) 2012 Alexander Overvoorde

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#include <GL/Platform.hpp>
#include <GL/GL/VertexBuffer.hpp>
#include <vector>
#include <cassert>

namespace GL
{
	VertexBuffer::VertexBuffer() : type(BufferTypes::None)
	{
		if (SupportsDSA())
		{
			gc.Create(obj, glCreateBuffers, glDeleteBuffers);
		}
		else
		{
			gc.Create(obj, glGenBuffers, glDeleteBuffers);
		}
	}

	VertexBuffer::VertexBuffer( const VertexBuffer& other ) : type(other.type)
	{
		gc.Copy( other.obj, obj );
	}

	VertexBuffer::~VertexBuffer()
	{
		gc.Destroy( obj );
	}

	uint32_t VertexBuffer::GetType() const
	{
		return type;
	}

	uint32_t VertexBuffer::GetHandle() const
	{
		return obj;
	}

	void VertexBuffer::Initialize(const BufferTypes::buffer_type_t & tgtype)
	{
		assert(type == BufferTypes::None);
		type = tgtype;
	}

	VertexBuffer::operator GLuint() const
	{
		return obj;
	}

	const VertexBuffer& VertexBuffer::operator=( const VertexBuffer& other )
	{
		gc.Copy( other.obj, obj, true );
		return *this;
	}

	void VertexBuffer::Data(const void* data, size_t length, BufferUsage::buffer_usage_t usage)
	{
		if (SupportsDSA())
		{
			glNamedBufferData(obj, length, data, usage);
		}
		else
		{
			glBindBuffer(type, obj);
			glBufferData(type, length, data, usage);
		}
	}

	void VertexBuffer::SubData(const void* data, size_t offset, size_t length)
	{
		if (SupportsDSA())
		{
			glNamedBufferSubData(obj, offset, length, data);
		}
		else
		{
			glBindBuffer(type, obj);
			glBufferSubData(type, offset, length, data);
		}
	}

	void VertexBuffer::GetSubData(void* data, size_t offset, size_t length)
	{
		glBindBuffer(type, obj);
		glGetBufferSubData(type, offset, length, data);
	}

	GC VertexBuffer::gc;
}