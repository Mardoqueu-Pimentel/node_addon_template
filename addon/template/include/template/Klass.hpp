//
// Created by mard on 10/8/19.
//

#pragma once

#include <napi.h>
#include <mardcpp/mardcpp.hpp>

namespace tmplt {

	class Klass : public Napi::ObjectWrap<Klass> {

		std::string mGreeterName;

	public:
		static inline constexpr mc::StringView CLASS_NAME = "Klass"sv;
		static inline constexpr mc::StringView METHOD_NAME_GREET = "greet"sv;

		Klass(const Napi::CallbackInfo &info);

		Napi::Value greet(const Napi::CallbackInfo &info);

		static Napi::Function getClass(Napi::Env env);
	};

}




