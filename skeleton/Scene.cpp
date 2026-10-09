#include "Scene.h"
#include <iostream>

void Scene::cleanup() {
	for (const auto& renderItem : m_renderItems) {
		if (renderItem) {
			renderItem->release();
		}
	}
	m_renderItems.clear();
}