/*
** EPITECH PROJECT, 2022
** sfml.cpp
** File description:
** TODO
*/

#include "sfml.hpp"

extern "C" Arcade::sfml *Arcade::entry_point()
{
    return new Arcade::sfml;
}

Arcade::sfml::sfml()
{
    window.create(sf::VideoMode(1920, 1080), "Arcade - SFML", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);
    font.loadFromFile("contents/FiraCode-Regular.ttf");
}

Arcade::sfml::~sfml() {
    window.close();
}

Arcade::Input Arcade::sfml::GetInput() {
    Input input = NOTHING;
    while(window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            input = EXIT;
        else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Left:
                    input = ARROW_LEFT;
                    break;
                case sf::Keyboard::Right:
                    input = ARROW_RIGHT;
                    break;
                case sf::Keyboard::Up:
                    input = ARROW_UP;
                    break;
                case sf::Keyboard::Down:
                    input = ARROW_DOWN;
                    break;
                case sf::Keyboard::N:
                    input = N;
                    break;
                case sf::Keyboard::P:
                    input = P;
                    break;
                case sf::Keyboard::F:
                    input = F;
                    break;
                case sf::Keyboard::B:
                    input = B;
                    break;
                case sf::Keyboard::M:
                    input = M;
                    break;
                case sf::Keyboard::R:
                    input = R;
                    break;
                case sf::Keyboard::Enter:
                    input = ENTER;
                    break;
                case sf::Keyboard::Space:
                    input = SPACE;
                    break;
                case sf::Keyboard::Escape:
                    input = EXIT;
                    break;
                default:
                    break;
            }
        }
    }
    return input;
}

void Arcade::sfml::ClearScreen() {
    window.clear();
}

void Arcade::sfml::RefreshScreen() {
    window.display();
}

void Arcade::sfml::DrawObject(Arcade::Object object) {
    auto Tile = dynamic_cast<Arcade::Tile *>(object.get());
    if (Tile)
        DrawTile(Tile);
    auto Text = dynamic_cast<Arcade::Text *>(object.get());
    if (Text)
        DrawText(Text);
    auto Sound = dynamic_cast<Arcade::Sound *>(object.get());
    if (Sound)
        PlaySound(Sound);
}

void Arcade::sfml::DrawTile(Arcade::Tile *tile)
{
    TexturePath path = tile->getTexturePath();
    if (!std::filesystem::exists(path))
        return;
    if (TextureMap.find(path) == TextureMap.end())
        TextureMap[path] = std::make_shared<sf::Texture>();
    TextureMap[path]->loadFromFile(path);
    std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>(*TextureMap[path]);
    sprite->setOrigin(15, 15);
    sprite->setRotation(tile->getRotation());
    sprite->setPosition((tile->getPosition().first * 30) + 15, (tile->getPosition().second * 30) + 15);

    window.draw(*sprite);
}

void Arcade::sfml::DrawText(Arcade::Text *text) {
    std::shared_ptr<sf::Text> textObj = std::make_shared<sf::Text>();
    textObj->setFont(font);
    textObj->setString(text->getText());
    textObj->setPosition(text->getPosition().first * 30, text->getPosition().second * 30);
    textObj->setCharacterSize(20);
    textObj->setFillColor(sf::Color::Blue);

    window.draw(*textObj);
}

void Arcade::sfml::PlaySound(Arcade::Sound *sound) {
    SoundPath path = sound->getSound();
    if (!std::filesystem::exists(path))
        return;
    if (SoundMap.find(path) == SoundMap.end())
        SoundMap[path].first = std::make_shared<sf::SoundBuffer>();
    SoundMap[path].first->loadFromFile(path);
    SoundMap[path].second = std::make_shared<sf::Sound>(*SoundMap[path].first);
    SoundMap[path].second->play();
}