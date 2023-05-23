#pragma once

#include <string>
#include "esphome/components/homeThing/homeThingMenuDisplayState.h"
#include "esphome/components/homeThing/homeThingMenuTextHelpers.h"
#include "esphome/components/homeThing/homeThingMenuTitle.h"

#ifdef USE_LIGHT_GROUP
#include "esphome/components/homeassistant_light_group/HomeAssistantLightGroup.h"
#endif

#ifdef USE_MEDIA_PLAYER_GROUP
#include "esphome/components/homeThing/homeThingOptionMenu.h"
#include "esphome/components/homeassistant_media_player/HomeAssistantMediaPlayerGroup.h"
#endif

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace homething_menu_base {

class HomeThingMenuHeader {
 public:
  HomeThingMenuHeader(display::DisplayBuffer* new_display_buffer,
                      HomeThingMenuDisplayState* new_display_state,
                      HomeThingMenuTextHelpers* new_text_helpers)
      : display_buffer_(new_display_buffer),
        display_state_(new_display_state),
        text_helpers_(new_text_helpers) {}
  void drawHeader(int yPosOffset, const MenuStates activeMenuState);
  void set_battery_percent(sensor::Sensor* battery_percent) {
    battery_percent_ = battery_percent;
  }
  void set_charging(binary_sensor::BinarySensor* charging) {
    charging_ = charging;
  }

#ifdef USE_MEDIA_PLAYER_GROUP
  void set_media_player_group(
      homeassistant_media_player::HomeAssistantMediaPlayerGroup*
          media_player_group) {
    media_player_group_ = media_player_group;
  }
#endif

#ifdef USE_LIGHT_GROUP
  void set_light_group(
      homeassistant_light_group::HomeAssistantLightGroup* light_group) {
    light_group_ = light_group;
  }
#endif

 private:
  float get_battery_percent() {
    if (battery_percent_ != nullptr && battery_percent_->has_state()) {
      return battery_percent_->state;
    } else {
      return 0;
    }
  }
  bool get_charging() {
    if (charging_ != nullptr && charging_->has_state()) {
      return charging_->state;
    } else {
      return false;
    }
  }
  void drawHeaderTitleWithString(std::string title, int xPos,
                                 int yPosOffset = 0);
  void drawHeaderTitle(int yPosOffset, const MenuStates activeMenuState);
  int getHeaderTextYPos(int yPosOffset);
  int drawBattery(int oldXPos, int yPosOffset);
  int drawHeaderIcon(std::string title, int xPos, Color iconColor);
  int drawHeaderTime(int oldXPos, int yPosOffset);

#ifdef USE_MEDIA_PLAYER_GROUP
  int drawPlayPauseIcon(int oldXPos, MenuTitlePlayer menuTitle);
  int drawShuffle(int oldXPos, int yPosOffset);
  int drawRepeat(int oldXPos, int yPosOffset);
  int drawHeaderVolumeLevel(int oldXPos, int yPosOffset);
#endif

#ifdef USE_MEDIA_PLAYER_GROUP
  homeassistant_media_player::HomeAssistantMediaPlayerGroup*
      media_player_group_{nullptr};
#endif

#ifdef USE_LIGHT_GROUP
  homeassistant_light_group::HomeAssistantLightGroup* light_group_{nullptr};
#endif

  display::DisplayBuffer* display_buffer_{nullptr};
  HomeThingMenuDisplayState* display_state_{nullptr};
  HomeThingMenuTextHelpers* text_helpers_{nullptr};
  sensor::Sensor* battery_percent_{nullptr};
  binary_sensor::BinarySensor* charging_{nullptr};
  time::RealTimeClock* esp_time_{nullptr};
  const char* const TAG = "homething.menu.header";
};

}  // namespace homething_menu_base
}  // namespace esphome
