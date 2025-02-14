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

#ifdef CS_TARGETPLATFORM_RPI

#include <CSBackend/Platform/RPi/Input/TextEntry/TextEntry.h>

#include <ChilliSource/Core/Base/Application.h>
#include <ChilliSource/Core/Delegate/MakeDelegate.h>
#include <ChilliSource/Core/Threading/TaskScheduler.h>
#include <CSBackend/Platform/RPi/Core/Base/DispmanWindow.h>

#include <X11/keysym.h>

namespace CSBackend
{
	namespace RPi
	{
		CS_DEFINE_NAMEDTYPE(TextEntry);

		//----------------------------------------------------------------------------------
		bool TextEntry::IsA(ChilliSource::InterfaceIDType interfaceId) const noexcept
		{
			return interfaceId == ChilliSource::TextEntry::InterfaceID || interfaceId == TextEntry::InterfaceID;
		}

		//----------------------------------------------------------------------------------
		void TextEntry::Activate(const std::string& text, ChilliSource::TextEntryType type, ChilliSource::TextEntryCapitalisation capitalisation, const TextBufferChangedDelegate& changeDelegate, const TextInputDeactivatedDelegate& deactivateDelegate) noexcept
		{
            CS_ASSERT(ChilliSource::Application::Get()->GetTaskScheduler()->IsMainThread(), "Cannot activate system text entry outside of main thread.");
            CS_ASSERT(!m_active, "Cannot activate TextEntry system while already active.");

            m_active = true;
			m_text = text;
			m_textBufferChangedDelegate = changeDelegate;
			m_textInputDeactivatedDelegate = deactivateDelegate;
			DispmanWindow::Get()->SetTextEntryDelegates(ChilliSource::MakeDelegate(this, &TextEntry::OnTextEntered));
		}

		//----------------------------------------------------------------------------------
        void TextEntry::Deactivate() noexcept
        {
            CS_ASSERT(ChilliSource::Application::Get()->GetTaskScheduler()->IsMainThread(), "Cannot deactivate system text entry outside of main thread.");
            CS_ASSERT(m_active, "Cannot deactivate TextEntry system when not active.");

			DispmanWindow::Get()->RemoveTextEntryDelegates();

            m_active = false;

            if (m_textInputDeactivatedDelegate != nullptr)
            {
                auto delegate = m_textInputDeactivatedDelegate;
                m_textInputDeactivatedDelegate = nullptr;
                delegate();
            }
		}

		//----------------------------------------------------------------------------------
        const std::string& TextEntry::GetTextBuffer() const noexcept
        {
            CS_ASSERT(ChilliSource::Application::Get()->GetTaskScheduler()->IsMainThread(), "Cannot get system text entry buffer outside of main thread.");
            return m_text;
        }

		//----------------------------------------------------------------------------------
        void TextEntry::SetTextBuffer(const std::string& text) noexcept
        {
            CS_ASSERT(ChilliSource::Application::Get()->GetTaskScheduler()->IsMainThread(), "Cannot set system text entry buffer outside of main thread.");
            m_text = text;
        }

		//----------------------------------------------------------------------------------
        void TextEntry::OnTextEntered(ChilliSource::UTF8Char character) noexcept
        {
            ChilliSource::Application::Get()->GetTaskScheduler()->ScheduleTask(ChilliSource::TaskType::k_mainThread, [=](const ChilliSource::TaskContext& taskContext)
            {
                std::unique_lock<std::mutex> lock(m_mutex);

                std::string text;

				const ChilliSource::UTF8Char k_backspace = 8;
                if (character != k_backspace)
                {
                    text = ChilliSource::UTF8StringUtils::AppendCopy(character, m_text);
                }
                else
                {
                    s32 length = (s32)ChilliSource::UTF8StringUtils::CalcLength(m_text.begin(), m_text.end());
                    length = std::max(length - 1, 0);
                    text = ChilliSource::UTF8StringUtils::SubString(m_text, 0, (u32)length);
                }

                bool acceptText = true;

                if (m_textBufferChangedDelegate != nullptr)
                {
                    acceptText = m_textBufferChangedDelegate(text);
                }

                if (acceptText == true)
                {
                    m_text = std::move(text);
                }
            });
        }
	}
}

#endif
