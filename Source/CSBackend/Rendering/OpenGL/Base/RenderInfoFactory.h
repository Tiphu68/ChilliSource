//
//  The MIT License (MIT)
//
//  Copyright (c) 2016 Tag Games Limited
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifndef _CSBACKEND_RENDERING_OPENGL_BASE_RENDERINFOFACTORY_H_
#define _CSBACKEND_RENDERING_OPENGL_BASE_RENDERINFOFACTORY_H_

#include <ChilliSource/ChilliSource.h>

#include <ChilliSource/Core/Base/RenderInfo.h>

namespace CSBackend
{
    namespace OpenGL
    {
        /// A factory for creating new instances of RenderInfo. This will query openGL
        /// to gather information about the rendering capabilities of the current device.
        ///
        namespace RenderInfoFactory
        {
            /// @return The RenderInfo for this device.
            ///
            ChilliSource::RenderInfo CreateRenderInfo() noexcept;
        }
    }
}

#endif
