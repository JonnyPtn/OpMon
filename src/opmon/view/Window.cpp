#include "Window.hpp"
#include "../../utils/StringKeys.hpp"
#include "../../utils/log.hpp"
#include "../model/save/OptionsSave.hpp"
#include "../model/storage/ResourceLoader.hpp"
#include "../start/Core.hpp"

#include <SFML/Graphics.hpp>

using Utils::Log::oplog;

namespace OpMon {
    namespace View {
        void Window::open() {
            sf::ContextSettings settings;
            //settings.antialiasingLevel = 8;
            if(!Model::OptionsSave::checkParam("fullscreen")) {
                Model::OptionsSave::addOrModifParam("fullscreen", "false");
            }
            if(Model::OptionsSave::getParam("fullscreen").getValue() == "true") {
                fullScreen = true;
                window.create(sf::VideoMode::getFullscreenModes().at(0), "OpMon Lazuli", sf::Style::Fullscreen, settings);
            } else {
                window.create(sf::VideoMode(512, 512), "OpMon Lazuli", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize, settings);
            }

            sf::Image icon;
            Model::ResourceLoader::load(icon, "opmon.png");
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

            frame.create(512, 512);

            oplog("Window initialized!");
#if 0
	    window.setVerticalSyncEnabled(true);
#endif
            window.setFramerateLimit(30);
            window.setKeyRepeatEnabled(false);
            frame.clear(sf::Color::White);
            refresh();
        }

        void Window::close() {
            oplog("Closing the window...");
            window.close();
            oplog("Window closed. No error detected. Goodbye.");
        }

        void Window::refresh() {
            frame.display();
            sf::Sprite sprite(frame.getTexture());

            if(fullScreen) {
                float coef = window.getSize().y / (sprite.getGlobalBounds().height);
                sprite.setScale(coef, coef);
                sprite.setPosition(((window.getSize().x / 2) - (sprite.getGlobalBounds().width / 2)), 0);
            }

            window.clear(sf::Color::Black);
            window.draw(sprite);
            window.display();
        }

    } // namespace View
} // namespace OpMon
