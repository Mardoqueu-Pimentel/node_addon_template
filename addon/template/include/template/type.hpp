//
// Created by mard on 10/7/19.
//

#pragma once

#include <napi.h>
#include <template/util.hpp>
#include <mardcpp/mardcpp.hpp>

namespace tmplt {

	namespace node {

		struct Number {
			using Type = Napi::Number;
		};

		struct Int32 : Number {
			static constexpr auto cast = &Type::Int32Value;
		};

		struct Int64 : Number {
			static constexpr auto cast = &Type::Int64Value;
		};

		struct UInt32 : Number {
			static constexpr auto cast = [](const Type &number) {
				int64_t n = number.Int64Value();
				if (n < 0) {
					throw makeError(number.Env(), "assertion %ld >= 0", n);
				}
				return static_cast<uint32_t>(n);
			};
		};

		struct UInt64 : Number {
			static constexpr auto cast = [](const Type &number) {
				int64_t n = number.Int64Value();
				if (n < 0) {
					throw makeError(number.Env(), "assertion %ld >= 0", n);
				}
				return static_cast<uint64_t>(n);
			};
		};

		struct String {
			using Type = Napi::String;
		};

		struct Utf8 : String {
			static constexpr auto cast = &Type::Utf8Value;
		};

		struct Utf16 : String {
			static constexpr auto cast = &Type::Utf16Value;
		};

		struct Function {
			using Type = Napi::Function;
			static constexpr auto cast = [](const Type &function) {
				return function;
			};
		};

		struct Obj {
			using Type = Napi::Object;
			static constexpr auto cast = [](const Type &obj) {
				return obj;
			};
		};
	}

	template<typename T>
	auto getArgsImplHelper(const Napi::CallbackInfo &info, size_t i) {
		try {
			return std::bind(T::cast, info[i].As<typename T::Type>())();
		} catch (const Napi::Error &error) {
			const char *m = info[i].ToString().Utf8Value().c_str();
			throw makeError(info.Env(), "%s (%zuº arg = %s)", error.what(), i + 1, m);
		}
	}

	template<typename ... Ts, size_t ... N>
	auto getArgsImpl(
		const Napi::CallbackInfo& info, std::index_sequence <N...>
	) {
		const size_t ax = sizeof ... (N), ay = info.Length();
		if (ax != ay) {
			throw makeError(info.Env(), "Invalid number of arguments (%zu). Accepts only %zu.", ay, ax);
		}
		return std::tuple(getArgsImplHelper<Ts>(info, N)...);
	}

	template<typename ... Ts, typename Indices = std::make_index_sequence<sizeof...(Ts)>>
	auto getArgs(const Napi::CallbackInfo& info) {
		return getArgsImpl<Ts...>(info, Indices());
	}

	template<typename T1, typename T2>
	T2 getArg(const Napi::CallbackInfo& info, size_t i) {
		try {
			return info[i].As<T1>();
		} catch (const Napi::Error &error) {
			auto m = info[i].ToString().Utf8Value().c_str();
			throw makeError(info.Env(), "%s (%zuº arg = %s)", error.what(), i + 1, m);
		}
	}
}