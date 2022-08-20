#pragma once

#include <LucyGL/LucyGL.h>
#include <unordered_map>

namespace lre {
	struct TextureStore {
	private:
		unsigned int next_unit = 0;
		std::unordered_map<lgl::TextureId, uint32_t> texture_unit_map;

	public:
		void bind();
		void clear();
		int size();
		bool slotavaliable();

		uint32_t operator[](lgl::Texture* texture);
		uint32_t operator[](lgl::TextureId texture);
	};
}