#include <ui/scripts.hpp>
#include <ui/menu.hpp>
#include <utils/fnv.hpp>

ui::scripts::clickable_t* ui::scripts::clickable_t::create(ui::scripts::window_t* window, const char* text, const char* flag_name, ui::scripts::window_object_type type) {
  const auto flag = new ui::scripts::flag_t();
  flag->hash = utils::fnv::hash(flag_name);
  flag->type = ui::scripts::flag_type::boolean;

  const auto clickable = new ui::scripts::clickable_t();
  clickable->text = text;
  clickable->flag = flag;
  clickable->type = type;

  flag->object = clickable;

  std::unique_lock guard{ ui::scripts::windows_mutex };

  window->objects.emplace_back(clickable);
  ui::scripts::flags.emplace_back(flag);

  return clickable;
}

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
            const auto button = (ui::scripts::clickable_t*)(object);

            if (ImGui::Button(button->text.c_str()))
              button->flag->b = true;

            break;
          }

          case ui::scripts::window_object_type::checkbox: {
            const auto checkbox = (ui::scripts::clickable_t*)(object);
            ImGui::Checkbox(checkbox->text.c_str(), &checkbox->flag->b);
            break;
          }
        }
      }
    }
    ImGui::End();
  }
}
