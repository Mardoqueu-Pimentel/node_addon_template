//
// Created by mard on 10/7/19.
//

#include <template/util.hpp>
#include <cstdarg>

namespace tmplt {

	Napi::Error makeError (Napi::Env env, const char *__restrict format, ...) noexcept {
		va_list args;
		va_start(args, format);
		vsnprintf(gb::BUFFER.data(), gb::BUFFER.size(), format, args);
		va_end(args);
		return Napi::Error::New(env, gb::BUFFER.data());
	}

}
