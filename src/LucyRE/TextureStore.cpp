#include "TextureStore.h"
#include <assert.h>

bool lre::TextureStore::slotavaliable() {
	return (next_unit <= 8);
}

uint32_t lre::TextureStore::operator[](lgl::Texture* texture) {
	return operator[](texture->id);
}

void lre::TextureStore::bind() {
	for (auto& pair: texture_unit_map) {
		lgl::BindTextureUnit(pair.first, pair.second);
	}
}

void lre::TextureStore::clear() {
	texture_unit_map.clear();
	next_unit = 0;
}

int lre::TextureStore::size() {
	return texture_unit_map.size();
}

uint32_t lre::TextureStore::operator[](lgl::TextureId texture) {
	if (texture_unit_map.find(texture) == texture_unit_map.end()) {
		assert(slotavaliable());
		texture_unit_map[texture] = next_unit++;
	}

	return texture_unit_map[texture];
}