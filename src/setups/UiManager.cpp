#include "UiManager.hpp"
#include "models/Car.hpp"
#include "models/Human.hpp"

UiManager::UiManager(GLFWwindow *window) {
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

void UiManager::setCar(Car *carPtr) { car = carPtr; }
//void UiManager::setHuman(std::vector<std::shared_ptr<threepp::Human>>* h) { humans = h; }
void UiManager::beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UiManager::renderUI() {
    ImGui::Begin("Car Controls");
    if (controller) {
        bool enabled = controller->getCameraSteeringEnabled();
        if (ImGui::Checkbox("AI Steering", &enabled)) {
            controller->setCameraSteeringEnabled(enabled);
        }
        ImGui::Separator();
    }

    if (car) {
        if (ImGui::Button("Reset Car values")) {
            car->reset();

        }
        float speed = car->getSpeed();
        if (ImGui::SliderFloat("Speed", &speed, 0.0f, car->getMaxSpeed())) {
            car->setSpeed(speed);
        }

        float maxSpeed = car->getMaxSpeed();
        if (ImGui::SliderFloat("Max Speed", &maxSpeed, 1.0f, 500.0f)) {
            car->setMaxSpeed(maxSpeed);
        }

        float acceleration = car->getAcceleration();
        if (ImGui::SliderFloat("Acceleration", &acceleration, 0.0f, 500.0f)) {
            car->setAcceleration(acceleration);
        }

        float rotationSpeed = car->getRotationSpeed();
        if (ImGui::SliderFloat("Rotation Speed", &rotationSpeed, 0.0f, 10.0f)) {
            car->setRotationSpeed(rotationSpeed);
        }

        float drag = car->getDrag();
        if (ImGui::SliderFloat("Drag", &drag, 0.0f, 20.0f)) {
            car->setDrag(drag);
        }

        ImGui::Separator();

        auto pos = car->position;
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
