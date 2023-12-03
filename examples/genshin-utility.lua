-- Some functionality of Genshin Utility implemented in HSRL
-- https://github.com/lanylow/genshin-utility

local function update()
  CS.UnityEngine.Application.targetFrameRate = hsrl.getflag("si_fps");
  CS.UnityEngine.QualitySettings.vSyncCount = hsrl.getflag("cb_vsync") and 1 or 0;
end

local function init()
  local window = hsrl.window.new("Genshin Utility by lanylow");
  window:checkbox("Enable V-Sync", "cb_vsync");
  window:sliderint("Frame rate limit", 10, 360, "si_fps");

  hsrl.on_update(update);
end

init();