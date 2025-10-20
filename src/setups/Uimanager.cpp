#include "UiManager.hpp"

UiManager::UiManager(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");
}

UiManager::~UiManager() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UiManager::setCar(Car* carPtr) { car = carPtr; }

void UiManager::beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UiManager::renderUI() {
    ImGui::Begin("Car Controls");

    if (car) {
        if (ImGui::Button("Reset Car Position")) {
            car->resetPosition();
        }

        ImGui::Separator();

        auto pos = car->getPosition();
        ImGui::Text("Current Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
    }

    if (showDemoWindow) {
        ImGui::ShowDemoWindow(&showDemoWindow);
    }

    ImGui::End();
}

void UiManager::endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
