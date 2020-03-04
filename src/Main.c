#include <string.h>

#include "log.h"
#include "registers.h"
#include "memory.h"
#include "cpu.h"

#include <SDL.h>

const uint8_t NINTENDO_MAGIC[] = {
    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
    0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
    0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,
};

enum {
    OFF_BEGIN_CODE = 0x0100,
    OFF_MAGIC_START = 0x0104,
    OFF_MAGIC_END = 0x0133,
    OFF_TITLE_START = 0x0134,
    OFF_TITLE_END = 0x0142,
    OFF_COLOR_ENABLE = 0x0143,
    OFF_LICENSE = 0x0144,
    OFF_SUPER_ENABLE = 0x0146,
    OFF_CARTRIDGE_TYPE = 0x0147,
    OFF_ROM_SIZE = 0x0148,
    OFF_RAM_SIZE = 0x0149,
    OFF_REGION = 0x014A,
    OFF_LICENSE_OLD = 0x014B,
    OFF_ROM_MASK = 0x014C,
    OFF_COMPLEMENT_CHECK = 0x014D,
    OFF_CHECKSUM = 0x014E,
    OFF_HEADER_END = 0x0150,
};

//void PrintFileHex(const std::vector<uint8_t>& buffer)
//{
//    // Print the file as hexadecimal numbers
//    LogInfo("File as Hexadecimal:");
//    for (unsigned i = 0; i < buffer.size(); ++i)
//    {
//        if (i % 32 == 0)
//        {
//            LogInfo("\n");
//        }
//        LogInfo("%02X ", buffer[i]);
//    }
//
//    LogInfo("\n\n\n");
//}

// argc = number of arguments, argv = the arguments
int main(int argc, char* argv[])
{

    // Error check for too many arguments or too few
    if (argc < 2)
    {
        LogError("No filename specified.\n");
        return 1;
    }
    else if (argc > 2)
    {
        LogError("Too many arguments.\n");
        return 1;
    }
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window;
    int SCALE = 3;

    window = SDL_CreateWindow(
        "GBxyz",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        160 * SCALE,
        144 * SCALE,
        0);

    loadROM(argv[1]);

    R.SP = 0xFFFE;
    R.PC = 0;

    SDL_Renderer* r = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    if (!r)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Renderer not created.", window);
        exit(1);
    }

    SDL_Texture* tex = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 256, 256);

    
    uint8_t* pixels = NULL;
    int pitch = 0;
    SDL_LockTexture(tex, NULL, (void**)&pixels, &pitch);

    for (unsigned y = 0; y < 144; ++y) {
        for (unsigned x = 0; x < 160; ++x) {
            unsigned off = (y * 256 * 3) + (x * 3);
            pixels[off + 0] = 0xFF; // R
            pixels[off + 1] = 0x00; // G
            pixels[off + 2] = 0x00; // B
        }
    }

    SDL_UnlockTexture(tex);



    // Rect
    
    SDL_Rect src = { .x = 0, .y = 0, .w = 160, .h = 144 };
    SDL_Rect dst = { .x = 0, .y = 0, .w = 160 * SCALE, .h = 144 * SCALE, };

    SDL_Event ev;

    for (;;)
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                exit(0);
            }
        }
        
        //SDL_RenderClear(r);
        SDL_RenderCopy(r, tex, &src, &dst);
        SDL_RenderPresent(r);
        //uint8_t op = fetch();
        //execute(op);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}