//
//  VideoOverlayView.mm
//  ChilliSource
//  Created by Ian Copland on 11/04/2014.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2014 Tag Games Limited
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

#ifdef CS_TARGETPLATFORM_IOS

#import <CSBackend/Platform/iOS/Video/Base/VideoOverlayView.h>

@implementation VideoOverlayView

//---------------------------------------------------
//---------------------------------------------------
- (id) initWithFrame:(CGRect)in_frame
{
    if (self = [super initWithFrame: in_frame])
    {
        return self;
    }
    return nil;
}
//---------------------------------------------------
//---------------------------------------------------
- (void) touchesBegan:(NSSet*)in_touches withEvent:(UIEvent*)in_event
{
}
//---------------------------------------------------
//---------------------------------------------------
- (void) touchesMoved:(NSSet*)in_touches withEvent:(UIEvent*)in_event
{
}
//---------------------------------------------------
//---------------------------------------------------
- (void) touchesEnded:(NSSet*)in_touches withEvent:(UIEvent*)in_event
{
}
//---------------------------------------------------
//---------------------------------------------------
- (void) touchesCancelled:(NSSet*)in_touches withEvent:(UIEvent*)in_event
{
}

@end

#endif
