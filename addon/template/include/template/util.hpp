//
// Created by mard on 10/7/19.
//

#pragma once

#include <napi.h>
#include <array>

namespace tmplt {

	struct gb {

		static inline std::array<char, 4096> BUFFER;

	};

	Napi::Error __attribute__ ((__format__ (__printf__, 2, 3)))
	makeError (Napi::Env env, const char *__restrict format, ...) noexcept;
}
