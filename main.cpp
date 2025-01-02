#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fftw3.h>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <memory>
#include <iostream>

int main(int argc, char** argv) {
    auto window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(1024, 720),
        "Audio Spectrum",
        sf::Style::Titlebar | sf::Style::Close
    );

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " file.[wav]\n";
        return EXIT_FAILURE;
    }

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(argv[1])) {
        std::cerr << "Failed to load audio file: " << argv[1] << "\n";
        return EXIT_FAILURE;
    }

    sf::Sound sound(buffer);
    sound.play();

    const int sample_size = 1024;
    fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * sample_size);
    fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * sample_size);
    fftw_plan plan = fftw_plan_dft_1d(sample_size, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    std::vector<float> spectrum(sample_size / 2);
    const sf::Int16* samples = buffer.getSamples();
    std::size_t sample_count = buffer.getSampleCount();
    std::size_t channels = buffer.getChannelCount();
    std::size_t current_sample = {};

    sf::Texture texture;
    texture.loadFromFile("./img.jpg");
    sf::Sprite sprite(texture);

    sf::Font font;
    font.loadFromFile("./andarilho-font.ttf");
    std::string music = argv[1];
    music = music.substr(0, music.length() - 4);
    sf::Text text(music, font, 18);
    text.setPosition(20.f, 10.f);

    float totalDuration = buffer.getDuration().asSeconds();

    float barVisualizerWidth = 50 * 6.f; 
    float xOffset = (window->getSize().x - barVisualizerWidth) / 2.f;

    sf::RectangleShape progressBar;
    progressBar.setFillColor(sf::Color::White);  
    progressBar.setSize(sf::Vector2f(0.f, 5.f)); 
    progressBar.setPosition(xOffset, window->getSize().y / 2.f + 120.f);

    sf::RectangleShape progressBarBackground;
    progressBarBackground.setFillColor(sf::Color(100, 100, 100));
    progressBarBackground.setSize(sf::Vector2f(barVisualizerWidth, 5.f));
    progressBarBackground.setPosition(xOffset, window->getSize().y / 2.f + 120.f);

    sf::Text timeText("", font, 18);
    timeText.setPosition(xOffset, window->getSize().y / 2.f + 140.f);

    while (window->isOpen()) {
        auto event = std::make_unique<sf::Event>();
        while (window->pollEvent(*event)) {
            if (event->type == sf::Event::Closed) {
                window->close();
            }
        }

        if (sound.getStatus() == sf::Sound::Stopped) {
            break;
        }

        for (int i = 0; i < sample_size; ++i) {
            std::size_t index = (current_sample + i) % (sample_count / channels);
            in[i][0] = static_cast<double>(samples[index * channels]) / 32768.0;
            in[i][1] = 0.0;
        }

        fftw_execute(plan);

        for (int i = 0; i < sample_size / 2; ++i) {
            spectrum[i] = std::sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        }

        current_sample += sample_size;

        float currentTime = sound.getPlayingOffset().asSeconds();
        float progress = currentTime / totalDuration;

        progressBar.setSize(sf::Vector2f(progress * progressBarBackground.getSize().x, 5.f));

        std::ostringstream timeStream;
        timeStream << std::fixed << std::setprecision(0)
                   << currentTime << "s / " << totalDuration << "s";
        timeText.setString(timeStream.str());

        window->clear();
        window->draw(sprite);
        window->draw(text);

        for (int i = 0; i < 50; i++) {
            sf::RectangleShape bar;
            float barWidth = 2.f;
            float spacing = 6.f;
            float totalWidth = 50 * spacing;
            float xOffset = (window->getSize().x - totalWidth) / 2.f;

            bar.setSize(sf::Vector2f(barWidth, spectrum[i] * 1.f));
            bar.setPosition(i * spacing + xOffset, window->getSize().y / 2.f);
            bar.setRotation(180);
            window->draw(bar);

            bar.setSize(sf::Vector2f(barWidth, -(spectrum[i] * 1.f)));
            window->draw(bar);
        }

        window->draw(progressBarBackground);
        window->draw(progressBar);
        window->draw(timeText);

        window->display();
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    return EXIT_SUCCESS;
}
