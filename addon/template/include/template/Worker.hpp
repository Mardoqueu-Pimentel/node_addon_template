//
// Created by mard on 10/7/19.
//

#pragma once

#include <napi.h>
#include <utility>

template<typename Signature>
struct Worker;

template<typename RetType, typename ... Types>
struct Worker<RetType(Types...)>: public Napi::AsyncWorker {

	using Function = std::function<RetType(Types...)>;

	std::tuple<Types...> tuple;
	const Function &mFunction;
	RetType mRetType;

	Worker(const Napi::Function &callback, const Function &function, const Types &...types)
	: AsyncWorker(callback), tuple(types...), mFunction(function) {}

	template<size_t ... N>
	void exec(std::index_sequence<N...>) {
		mRetType = mFunction(std::get<N>(tuple)...);
	}

	void Execute() override {
		exec(std::make_index_sequence<sizeof...(Types)>());
	}

	void OnOK() override {
		Napi::HandleScope scope(Env());
		Callback().Call({
			mRetType
		});
	}
};
