namespace sf {
    struct Texture {
        bool loadFromFile(const std::string& fname) {
            return true;
        }
    };

    struct Sprite {
        void setTexture(const Texture& texture) {}
        void setPosition(float x, float y) {}
    };
};