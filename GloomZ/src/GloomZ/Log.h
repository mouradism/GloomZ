#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include <spdlog/sinks/stdout_color_sinks.h>


namespace GloomZ {

	class GLOOMZ_API Log{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger>s_CoreLogger;
		static std::shared_ptr<spdlog::logger>s_ClientLogger;

	};

}

// core macro log
#define GL_CORE_ERROR(...)   ::GloomZ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GL_CORE_WARN(...)    ::GloomZ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GL_CORE_INFO(...)    ::GloomZ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GL_CORE_TRACE(...)   ::GloomZ::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GL_CORE_FATAL(...)   ::GloomZ::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// client macro log
#define GL_CLNT_ERROR(...) ::GloomZ::Log::GetClientLogger()->error(__VA_ARGS__)
#define GL_CLNT_WARN(...)  ::GloomZ::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GL_CLNT_INFO(...)  ::GloomZ::Log::GetClientLogger()->info(__VA_ARGS__)
#define GL_CLNT_TRACE(...) ::GloomZ::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GL_CLNT_FATAL(...) ::GloomZ::Log::GetClientLogger()->fatal(__VA_ARGS__)
