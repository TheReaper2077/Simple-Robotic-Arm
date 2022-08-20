#pragma once

#include <entt/entt.hpp>
#include <unordered_map>

namespace lucy {
	typedef entt::entity Entity;

	class Registry: public entt::registry {
		std::unordered_map<size_t, Entity> singleton_instances;

	public:
		template <typename T, typename ...Args>
		inline T& store(Args ...params) {
			if (singleton_instances.find(typeid(T).hash_code()) == singleton_instances.end()) {
				singleton_instances[typeid(T).hash_code()] = create();
				emplace<T>(singleton_instances[typeid(T).hash_code()], params...);
			}

			return get<T>(singleton_instances[typeid(T).hash_code()]);
		}

		template <typename T>
		bool contains(const Entity& entity) {
			return (try_get<T>(entity) != nullptr);
		}

		static Registry& Instance() {
			static Registry instance;
			return instance;
		}
	};
}

#define REGISTRY_DEF static auto& registry = lucy::Registry::Instance()
#define REGISTRY_STORE_DEF(name, type) static auto& name = registry.store<type>()