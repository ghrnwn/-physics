//#include "main.h"
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;
bool g_bRunning = false;

SDL_Texture* texureImage;
SDL_Rect rectImage;

SDL_Texture* texureText;
SDL_Rect rectText;

TTF_Font* m_pFont;
Mix_Chunk* chunk;
bool bLeftMousePressed = false;

bool init();
void handleInput();
void update();
void render();

int main(int argc, char* argv[])
{
    if (!init()) {
			return 1; // something's wrong
    }

		g_bRunning = true;

		// SDL Image
    SDL_Surface* pTempSurface = IMG_Load("./assets/animate-alpha.png");
		if (pTempSurface == 0) {
			return false;
		}
    texureImage = SDL_CreateTextureFromSurface(g_pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
		rectImage = { 0, 0, 128, 82 };

	// SDL TTF
    SDL_Color color_Blue = { 0, 0, 255 };
    SDL_Color color_White = { 255, 255, 255 };
#ifdef UNICODE
    SDL_Surface* temp_surf = TTF_RenderUNICODE_Shaded(m_pFont, (Uint16*)L"한글 텍스쳐", color_Blue, color_White);
#else
    SDL_Surface* temp_surf = TTF_RenderUTF8_Shaded(m_pFont, "한글 텍스쳐", color_Blue, color_White);
#endif
		if (temp_surf == 0) {	
				SDL_Log("%s", TTF_GetError());
        return false;
    }
	  texureText = SDL_CreateTextureFromSurface(g_pRenderer, temp_surf);
    SDL_FreeSurface(temp_surf);
    rectText = { 0, 0, temp_surf->w, temp_surf->h };

		// SDL Mixer
		// chunk에 WAV 로드, 재생은 update()에서
    // 참고: 배경음악은 Mix_Music* music = Mix_LoadMUS("FILE");
    chunk = Mix_LoadWAV("./assets/jump.wav");
		if (chunk == 0) {	
				SDL_Log("%s", Mix_GetError());
        return false;
    }

		// 볼륨 설정, -1은 모든 채널
    Mix_Volume(-1, 128);
	
	
    while (g_bRunning)
    {
        // handle input - update - render
        handleInput();
        update();
        render();
    }

    SDL_Quit();
    Mix_CloseAudio();
    Mix_Quit();

    TTF_CloseFont(m_pFont);
    TTF_Quit();

    return 0;
}

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			SDL_Log("%s", SDL_GetError());
      return false;
		}

		g_pWindow = SDL_CreateWindow( "HoseoSDL ", 
																	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			 													  640, 480, SDL_WINDOW_SHOWN);
		if (g_pWindow == 0) {
			SDL_Log("%s", SDL_GetError());
			return false;
		}

		g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		if (g_pRenderer == 0) {
			SDL_Log("%s", SDL_GetError());
			return false;
		}

		// SDL TTF 
    if (TTF_Init() < 0)
    {
        std::cout << "오류: 폰트를 초기화할 수 없음: " << TTF_GetError() << std::endl;
        return false;
    }

    m_pFont = TTF_OpenFont("./assets/NanumGothic.ttf", 20);
    if (m_pFont == 0) {	
				SDL_Log("%s", TTF_GetError());
        return false;
    }
	
    // SDL Mixer 
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)  {
				SDL_Log("%s", Mix_GetError());
        return false;
    }

    return true;
}

void handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
			switch (event.type )
			{
				case SDL_QUIT: 
					g_bRunning = false;
				break;

				case SDL_MOUSEBUTTONDOWN: 
					if (event.button.button == SDL_BUTTON_LEFT)
					{
							bLeftMousePressed = true;
					}
				break;

				case SDL_MOUSEBUTTONUP: 
					if (event.button.button == SDL_BUTTON_LEFT)
					{
							bLeftMousePressed = false;
					}
				break;
				
			}
    }
}

void update()
{
    if (bLeftMousePressed)
    {
        // chunk에 담긴 사운드 재생, -1은 가장 가까운 채널, 0은 반복 횟수
        Mix_PlayChannel(-1, chunk, 0);
        printf("왼쪽클릭 눌림 - 사운드 재생\n");
    }
}

void render()
{
    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);

    SDL_RenderClear(g_pRenderer);

    SDL_RenderCopy(g_pRenderer, texureImage, &rectImage, &rectImage);
    SDL_RenderCopy(g_pRenderer, texureText, &rectText, &rectText);

    filledCircleColor(g_pRenderer, 300, 300, 50, 0xFFFF0000);

    SDL_RenderPresent(g_pRenderer);
}