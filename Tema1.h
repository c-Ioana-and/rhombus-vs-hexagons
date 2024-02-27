#pragma once
#pragma once

#include "components/simple_scene.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };
        // Struct for the shooter: made of a rhombus and a square
        // In this struct we store the model matrix for each of the two meshes
        struct hexagon
        {
            glm::mat3 HexaMatrix;
            int lane;
            float translateX;
            int alive, colour;
        };
        struct Shooter
        {
            int color;
            int moveX, moveY;
            int initX, initY;
            int pressed, placed;
            glm::mat3 Matrix1, Matrix2;
            int t_star_last = 0;
            int t_star = 0;
        };

        struct star
        {
            glm::mat3 starMatrix;
            float translateX;
            float rotate;
        };
        struct pozCollectable
        {
			int x, y;
            bool collected;
		};

    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        // Sets the logic space and view space
        // logicSpace: { x, y, width, height }
        // viewSpace: { x, y, width, height }
        glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

    protected:
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 visMatrix, modelMatrix, starMatrix;
        std::vector <struct Shooter> shooters = std::vector <struct Shooter>(5);
        std::vector <struct hexagon> hexagons = std::vector <struct hexagon>(5);
        std::vector <struct pozCollectable> collect_stars = 
                                    std::vector <struct pozCollectable>(4);
        std::vector <struct star> stars;

        std::vector <std::vector <struct Shooter>> shooters_matrix;
        
        float current_time = 0;
        float last_time = 0;
        float attack_time = 1 + rand() % 3 + (rand() % 100) / 100.0f;

        float last_timeC = 0;
        float dropC;

        int index = 0, lives = 3, nr_hexa = 0;
        int nr_stars = 0;

        int length = 125;  // lenght of the basic squares used
        int length_S = 125 * 3 / 4;

        // The literal distance between the cells will be 175 - 125
        // 125 being the lenght of the cell (defined in Tema1.cpp, Init())
        int dist_between = 175;
        int dist_between_S = 125 * 3 / 4 + 100;

        // Where the first cell will be drawn
        int first_rowx = 125;
        int first_rowy = 50;

        // Where the rectangle will be drawn
        int rect_x = 25;
        int rect_y = 50;

        // Where the first cell for shooters will be drawn
        int first_rowx_S = first_rowx - length_S / 2;

        int resources = 0;
        bool change = true;
    };
}   // namespace m1
