#pragma once

class Konbini {
public:
    Konbini(const Konbini &obj) = delete;

    Konbini &operator=(Konbini &obj) = delete;

    static Konbini &getInstance() {
        static Konbini obj;
        return obj;
    }

private:
    Konbini();
};
