#include "liquid.hpp"

#include "libs/router.hpp"
#include "pages/MainPage.hpp"
#include "pages/PlayPage.hpp"

using namespace Liquid;

auto main() -> int {
    auto element = Group({
        Route("/", MainPage),
        Route("/play", PlayPage),
    });

    return render(element);
}
