#pragma once
#include "KonbiniUI.h"
#include <memory>

class Konbini {
public:
    Konbini(const Konbini &obj) = delete;

    Konbini &operator=(Konbini &obj) = delete;

    static Konbini &getInstance() {
        static Konbini obj;
        return obj;
    }

private:

    std::unique_ptr<KonbiniUI> ui;
    Konbini() {
        ui = std::make_unique<KonbiniUI>();
    }
};
