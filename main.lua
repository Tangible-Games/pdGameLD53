import "CoreLibs/object"
import "CoreLibs/graphics"
import "CoreLibs/sprites"
import "CoreLibs/timer"

print("Start game.")

local gfx = playdate.graphics
local display = playdate.display
local centerX = display.getWidth() / 2
local centerY = display.getHeight() / 2
local length = 100

function playdate.update()
  local crankAngle = math.rad(playdate.getCrankPosition())
  local dx = math.cos(crankAngle) * length
  local dy = math.sin(crankAngle) * length
  gfx.clear()
  gfx.drawLine(centerX, centerY, centerX + dx, centerY + dy)
end
