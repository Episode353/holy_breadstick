#include <stdio.h>
#include <sdl/SDL2.dll>

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Custom Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0)); // Set background color to black

    SDL_Color textColor = {255, 255, 255}; // White text color
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Custom Text", textColor); // Replace 'font' with your custom font
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = { 100, 100, textSurface->w, textSurface->h }; // Position and size of the text
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000); // Delay for 3 seconds

    SDL_DestroyTexture(textTexture);    
    SDL_FreeSurface(textSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
