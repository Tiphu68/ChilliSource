//
//  OrthographicCameraComponent.cpp
//  ChilliSource
//  Created by Scott Downie on 23/06/2014.
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

#include <ChilliSource/Rendering/Camera/OrthographicCameraComponent.h>

#include <ChilliSource/Core/Base/Screen.h>
#include <ChilliSource/Core/Delegate/MakeDelegate.h>
#include <ChilliSource/Core/Event/IConnectableEvent.h>

namespace ChilliSource
{
    CS_DEFINE_NAMEDTYPE(OrthographicCameraComponent);
    //----------------------------------------------------------
    //----------------------------------------------------------
    OrthographicCameraComponent::OrthographicCameraComponent(const Vector2& viewportSize, f32 nearClip, f32 farClip, ViewportResizePolicy resizePolicy)
    : CameraComponent(nearClip, farClip), m_viewportSize(viewportSize), m_currentViewportSize(viewportSize), m_resizePolicy(resizePolicy)
    {
        switch(m_resizePolicy)
        {
            case ViewportResizePolicy::k_none:
                break;
            case ViewportResizePolicy::k_scaleWithScreen:
                m_referenceScreenSize = m_screen->GetResolution();
                m_screenResizedConnection = m_screen->GetResolutionChangedEvent().OpenConnection(MakeDelegate(this, &OrthographicCameraComponent::OnResolutionChanged));
                break;
        }
        
        m_projMat = CalculateProjectionMatrix();
    }
    //----------------------------------------------------------
    //----------------------------------------------------------
    bool OrthographicCameraComponent::IsA(InterfaceIDType in_interfaceId) const
    {
        return (in_interfaceId == CameraComponent::InterfaceID || in_interfaceId == OrthographicCameraComponent::InterfaceID);
    }
    //------------------------------------------------------
    //------------------------------------------------------
    void OrthographicCameraComponent::SetViewportSize(const Vector2& in_size)
    {
        m_viewportSize = in_size;
        m_currentViewportSize = in_size;
        m_referenceScreenSize = m_screen->GetResolution();
        
        m_projMat = CalculateProjectionMatrix();
    }
    //------------------------------------------------------
    //------------------------------------------------------
    Matrix4 OrthographicCameraComponent::CalculateProjectionMatrix()
    {
        return Matrix4::CreateOrthographicProjectionLH(m_currentViewportSize.x, m_currentViewportSize.y, m_nearClip, m_farClip);
    }
    //------------------------------------------------------
    //------------------------------------------------------
    void OrthographicCameraComponent::UpdateFrustum()
    {
        m_frustum.CalculateClippingPlanes(GetView() * GetProjection());
    }
    //------------------------------------------------------
    //------------------------------------------------------
    void OrthographicCameraComponent::OnResolutionChanged(const Vector2& in_resolution)
    {
        switch(m_resizePolicy)
        {
            case ViewportResizePolicy::k_none:
                break;
            case ViewportResizePolicy::k_scaleWithScreen:
                m_currentViewportSize = m_viewportSize/m_referenceScreenSize * in_resolution;
                m_projMat = CalculateProjectionMatrix();
                break;
        }
    }
}

