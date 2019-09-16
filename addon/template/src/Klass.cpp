//
// Created by mard on 10/8/19.
//

#include <template/Klass.hpp>
#include <template/type.hpp>
#include <mardcpp/utils/util.hpp>

namespace tmplt {

	Klass::Klass(const Napi::CallbackInfo &info)
	: ObjectWrap<Klass>(info), mGreeterName(getArg<Napi::String, std::string>(info, 0)) {}

	Napi::Value Klass::greet(const Napi::CallbackInfo &info) {
		auto name = getArg<Napi::String, std::string>(info, 0);
		auto m = mc::fmt("Hello %s. I am %s", name.c_str(), mGreeterName.c_str());
		return Napi::String::New(Env(), m);
	}

	Napi::Function Klass::getClass(Napi::Env env) {
		return Klass::DefineClass(env, CLASS_NAME.data(), {
			Klass::InstanceMethod(METHOD_NAME_GREET.data(), &Klass::greet)
		});
	}

}
