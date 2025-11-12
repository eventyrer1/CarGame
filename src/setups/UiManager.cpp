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

void UiManager::setCarLogic(CarLogic* carLogic) {
    this->carLogic_ = carLogic;
}

void UiManager::beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UiManager::renderUI() {
    ImGui::Begin("Car Controls");

    if (carLogic_) {
        if (ImGui::Button("Reset Car values")) {
            carLogic_->reset();
        }

        float speed = carLogic_->getSpeed();
        ImGui::Text("Speed: %.2f", speed);

        ImGui::Separator();
        auto pos = carLogic_->getPosition();
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
