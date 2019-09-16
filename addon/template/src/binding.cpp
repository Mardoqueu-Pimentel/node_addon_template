#include <napi.h>
#include <array>
#include <template/type.hpp>
#include <charconv>
#include <template/Klass.hpp>

namespace tmplt {

	struct MethodWorker : public Napi::AsyncWorker {

		std::string seed;
		std::size_t size;
		std::string result;

		MethodWorker(Napi::Function& callback, const std::string &seed, size_t size)
		: AsyncWorker(callback), seed(seed), size(size) {}

		void Execute() override {
			for (size_t i = 0; i < size; ++i) {
				try {
					result += seed;
				} catch (const std::bad_alloc &e) {
					break;
				}
			}
		}

		void OnOK() override {
			Napi::HandleScope scope(Env());
			Callback().Call({Env().Null(), Napi::Number::New(Env(), result.size())});
		}

		void OnError(const Napi::Error &e) override {
			Napi::HandleScope scope(Env());
			Callback().Call({e.Value(), Env().Null()});
		}
	};

	Napi::Value method(const Napi::CallbackInfo& info) {
		auto[str, n, callback] = getArgs<node::Utf8, node::UInt64, node::Function>(info);

		Napi::AsyncWorker *worker = new MethodWorker(callback, str, n);
		worker->Queue();

		return info.Env().Undefined();
	}

}

Napi::Object init(Napi::Env env, Napi::Object exports) {
	exports["method"] = Napi::Function::New(env, tmplt::method);
	exports[tmplt::Klass::CLASS_NAME.data()] = tmplt::Klass::getClass(env);
	return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, init)