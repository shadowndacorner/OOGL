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

#include <GL/GL/VertexArray.hpp>
#include <assert.h>

namespace GL
{
	VertexArray::VertexArray()
	{
		if (SupportsDSA())
		{
			gc.Create(obj, glCreateVertexArrays, glDeleteVertexArrays);
		}
		else
		{
			gc.Create(obj, glGenVertexArrays, glDeleteVertexArrays);
		}
	}

	VertexArray::VertexArray( const VertexArray& other )
	{
		gc.Copy( other.obj, obj );
	}

	VertexArray::~VertexArray()
	{
		gc.Destroy( obj );
	}

	VertexArray::operator GLuint() const
	{
		return obj;
	}

	const VertexArray& VertexArray::operator=( const VertexArray& other )
	{
		gc.Copy( other.obj, obj, true );
		return *this;
	}

	void VertexArray::BindAttribute( const Attribute& attribute, const VertexBuffer& buffer, Type::type_t type, uint count, uint stride, intptr_t offset )
	{
		glBindVertexArray( obj );
		glBindBuffer( buffer.GetType(), buffer );
		glEnableVertexAttribArray( attribute );
		glVertexAttribPointer( attribute, count, type, GL_FALSE, stride, (const GLvoid*)offset );
	}

	void VertexArray::BindElements( const VertexBuffer& elements )
	{
		assert(elements.GetType() == BufferTypes::ElementBuffer);
		glBindVertexArray( obj );
		glBindBuffer( elements.GetType(), elements );
	}

	void VertexArray::BindTransformFeedback( uint index, const VertexBuffer& buffer )
	{
		glBindVertexArray( obj );
		glBindBufferBase( GL_TRANSFORM_FEEDBACK_BUFFER, index, buffer );
	}

	GC VertexArray::gc;
}