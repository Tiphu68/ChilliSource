//
//  HashSHA256.h
//  ChilliSource
//  Created by Jordan Brown on 24/02/2017.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2017 Tag Games Limited
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

#ifndef _CHILLISOURCE_CORE_CRYTOGRAPHIC_HASHSHA256_H_
#define _CHILLISOURCE_CORE_CRYTOGRAPHIC_HASHSHA256_H_

#include <ChilliSource/ChilliSource.h>

namespace ChilliSource
{
    //------------------------------------------------------
    /// A collection of methods for working with the SHA256
    /// hashing algorithm.
    ///
    /// @author Jordan Brown
    //------------------------------------------------------
    namespace HashSHA256
    {
        //------------------------------------------------
        /// Hashes the given data using SHA256. The output is
        /// returned as a hex string.
        ///
        /// @author Jordan Brown
        ///
        /// @param The input data.
        /// @param The input data size.
        ///
        /// @return The output hex string.
        //------------------------------------------------
        std::string GenerateHexHashCode(const s8* in_data, u32 in_size);
    }
}

#endif
