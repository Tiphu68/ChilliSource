//
//  HttpRequestSystem.h
//  ChilliSource
//  Created by Ian Copland on 08/11/2011.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2011 Tag Games Limited
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

#ifdef CS_TARGETPLATFORM_ANDROID

#ifndef _CSBACKEND_PLATFORM_ANDROID_HTTP_HTTPREQUESTSYSTEM_H_
#define _CSBACKEND_PLATFORM_ANDROID_HTTP_HTTPREQUESTSYSTEM_H_

#include <CSBackend/Platform/Android/Main/JNI/Core/Java/JavaSystem.h>
#include <CSBackend/Platform/Android/Main/JNI/ForwardDeclarations.h>
#include <CSBackend/Platform/Android/Main/JNI/Networking/Http/HttpRequest.h>
#include <ChilliSource/Networking/Http/HttpRequestSystem.h>

#include <vector>

namespace CSBackend
{
	namespace Android
	{	
		//--------------------------------------------------------------------------------------------------
		/// Android implementation of the http connection system. Reponsible for making http requests to remote
		/// urls and managing the lifetime of the requests and the connections. Uses the Java
		/// HttpUrlConnection library
		///
		/// @author Ian Copland
		//--------------------------------------------------------------------------------------------------
		class HttpRequestSystem final : public ChilliSource::HttpRequestSystem
		{
		public:

			CS_DECLARE_NAMEDTYPE(HttpRequestSystem);

			//--------------------------------------------------------------------------------------------------
			/// @author Ian Copland
			///
			/// @param Interface ID
            ///
			/// @return Whether object if of argument type
			//--------------------------------------------------------------------------------------------------
            bool IsA(ChilliSource::InterfaceIDType in_interfaceId) const override;
            //--------------------------------------------------------------------------------------------------
            /// Causes the system to issue an Http GET request.
            ///
            /// @author S Downie
            ///
            /// @param URL
            /// @param Delegate that is called on request completed. Completion can be failure as well as success
            /// @param Request timeout in seconds
            ///
            /// @return A pointer to the request. The system owns this pointer.
            //--------------------------------------------------------------------------------------------------
            HttpRequest* MakeGetRequest(const std::string& in_url, const HttpRequest::Delegate& in_delegate, u32 in_timeoutSecs = k_defaultTimeoutSecs) override;
            //--------------------------------------------------------------------------------------------------
            /// Causes the system to issue an Http GET request.
            ///
            /// @author S Downie
            ///
            /// @param URL
            /// @param Key value headers to attach to the request
            /// @param Delegate that is called on request completed. Completion can be failure as well as success
            /// @param Request timeout in seconds
            ///
            /// @return A pointer to the request. The system owns this pointer.
            //--------------------------------------------------------------------------------------------------
            HttpRequest* MakeGetRequest(const std::string& in_url, const ChilliSource::ParamDictionary& in_headers, const HttpRequest::Delegate& in_delegate, u32 in_timeoutSecs = k_defaultTimeoutSecs) override;
            //--------------------------------------------------------------------------------------------------
            /// Causes the system to issue an Http POST request with the given body.
            ///
            /// @author S Downie
            ///
            /// @param URL
            /// @param POST body
            /// @param Delegate that is called on request completed. Completion can be failure as well as success
            /// @param Request timeout in seconds
            ///
            /// @return A pointer to the request. The system owns this pointer.
            //--------------------------------------------------------------------------------------------------
            HttpRequest* MakePostRequest(const std::string& in_url, const std::string& in_body, const HttpRequest::Delegate& in_delegate, u32 in_timeoutSecs = k_defaultTimeoutSecs) override;
            //--------------------------------------------------------------------------------------------------
            /// Causes the system to issue an Http POST request with the given body.
            ///
            /// @author S Downie
            ///
            /// @param URL
            /// @param POST body
            /// @param Key value headers to attach to the request
            /// @param Delegate that is called on request completed. Completion can be failure as well as success
            /// @param Request timeout in seconds
            ///
            /// @return A pointer to the request. The system owns this pointer.
            //--------------------------------------------------------------------------------------------------
            HttpRequest* MakePostRequest(const std::string& in_url, const std::string& in_body, const ChilliSource::ParamDictionary& in_headers, const HttpRequest::Delegate& in_delegate, u32 in_timeoutSecs = k_defaultTimeoutSecs) override;
			//--------------------------------------------------------------------------------------------------
            /// Equivalent to calling cancel on every incomplete request in progress.
            ///
            /// @author Ian Copland
            //--------------------------------------------------------------------------------------------------
            void CancelAllRequests() override;
            //--------------------------------------------------------------------------------------------------
            /// Checks if the device is internet ready
            ///
            /// @author Ian Copland
            ///
            /// @param Delegate to call when reachability is determined
            //--------------------------------------------------------------------------------------------------
            void CheckReachability(const ReachabilityResultDelegate& in_reachabilityDelegate) const override;

		private:
            friend ChilliSource::HttpRequestSystemUPtr ChilliSource::HttpRequestSystem::Create();
            //--------------------------------------------------------------------------------------------------
            /// Private constructor to fore use of factory method
            ///
            /// @author Ian Copland
            //--------------------------------------------------------------------------------------------------
            HttpRequestSystem() = default;
            //------------------------------------------------------------------
            /// Concrete method to which all MakeRequest overloads feed.
            ///
            /// @author S Downie
            ///
            /// @param Type (POST or GET)
            /// @param Url
            /// @param Body (POST only)
            /// @param Headers
            /// @param Completion delegate
            /// @param Request timeout in seconds
            ///
            /// @return Request. Owned by the system.
            //------------------------------------------------------------------
            HttpRequest* MakeRequest(HttpRequest::Type in_type, const std::string& in_url, const std::string& in_body, const ChilliSource::ParamDictionary& in_headers, const HttpRequest::Delegate& in_delegate, u32 in_timeoutSecs);
			//--------------------------------------------------------------------------------------------------
            /// Sets up the java HttpRequestSystem
            ///
            /// @author HMcLaughlin
            //--------------------------------------------------------------------------------------------------
            void OnInit() override;
			//--------------------------------------------------------------------------------------------------
            /// Poll the connection on active requests
            ///
            /// @author Ian Copland
			///
			/// @param Time since last update in seconds
			//--------------------------------------------------------------------------------------------------
            void OnUpdate(f32 in_timeSinceLastUpdate) override;
            //--------------------------------------------------------------------------------------------------
            /// Called when the system is destroyed. Cancels all pending requests
            ///
            /// @author Ian Copland
			//--------------------------------------------------------------------------------------------------
            void OnDestroy() override;

		private:

			std::vector<HttpRequest*> m_requests;

            JavaSystemUPtr m_javaSystem;
		};
	}

}

#endif

#endif
