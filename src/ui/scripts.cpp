#include <ui/scripts.hpp>
#include <ui/menu.hpp>

void ui::scripts::render() {
  if (!ui::menu::opened)
    return;

  std::unique_lock guard{ ui::scripts::windows_mutex };

  for (const auto window : ui::scripts::windows) {
    ImGui::Begin(window->title.c_str());
    {
      for (const auto object : window->objects) {
        switch (object->type) {
          case ui::scripts::window_object_type::button: {
            const auto button = (ui::scripts::button_t*)(object);

            if (ImGui::Button(button->text.c_str()))
              button->flag->b = true;

            break;
          }
        }
      }
    }
    ImGui::End();
  }
}
