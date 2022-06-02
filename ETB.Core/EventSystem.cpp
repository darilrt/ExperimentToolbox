#include "EventSystem.h"

SDL_Event ETB::EventSystem::sdlEvent;
ETB::Event ETB::EventSystem::event;
std::map<ETB::EventType, std::vector<std::function<void(ETB::Event&)>>> ETB::EventSystem::events;

void ETB::EventSystem::DispatchEventType(EventType type) {
	for (auto& fn : events[type]) {
		fn(event);
	}
}

void ETB::EventSystem::AddEventListener(EventType type, std::function<void(Event&)> fn) {
	if (!events.count(type)) {
		events[type] = {};
	}

	events[type].push_back(fn);
}

void ETB::EventSystem::DispatchEvents() {
	EventType type;

	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			type = EventType::Quit;
			break;

		case SDL_KEYDOWN:
			type = EventType::KeyDown;
			EventSystem::event.keyCode = (KeyCode) sdlEvent.key.keysym.scancode;
			break;

		case SDL_KEYUP:
			type = EventType::KeyUp;
			EventSystem::event.keyCode = (KeyCode)sdlEvent.key.keysym.scancode;
			break;

		case SDL_MOUSEBUTTONDOWN:
			type = EventType::MouseButtonDown;
			EventSystem::event.button = sdlEvent.button.button;
			break;

		case SDL_MOUSEBUTTONUP:
			type = EventType::MouseButtonUp;
			EventSystem::event.button = sdlEvent.button.button;
			break;

		default:
			continue;
			break;
		}

		EventSystem::DispatchEventType(type);
	}
}
