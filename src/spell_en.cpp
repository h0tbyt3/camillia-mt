// The compiled-in English word list. Kept out of spell.cpp so the host tests
// can link the engine without the generated header.
#include "spell.h"
#include "spell_dict_en.h"

namespace spell {

const Dict &english() {
    static const Dict d = {
        kSpellEnData, kSpellEnSize, kSpellEnBlocks,
        (uint32_t)(sizeof(kSpellEnBlocks) / sizeof(kSpellEnBlocks[0])), kSpellEnWords,
    };
    return d;
}

}  // namespace spell
