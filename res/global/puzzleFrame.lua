-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   puzzleFrame.lua                                    :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/11 13:01:05 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/28 11:47:42 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local INSETS = 5.; -- INSET BORDER OF THE VIEW
local SPACING = 1.; -- SPACING BETWEEN TILES
local PUZZLEFRAME_TEXT_SIZE = 16;

local frame = puzzleFrame;
local transpTables;
assert(puzzleFrame ~= nil)


function drawTextCenter(canvas, text, x, y)
  text_w, text_h = canvas:measureText(text, PUZZLEFRAME_TEXT_SIZE);
  canvas:drawText(text, x - (text_w / 2)
				  , y - (text_h / 2), 0xFF555555, PUZZLEFRAME_TEXT_SIZE);
end

function frame:reloadGrid()
  frame.curPuzzle = Main:getGrid();
  frame.w = getPuzzleW(frame.curPuzzle);
  frame:queryRedraw();
  return ;
end

function frame:onDraw(canvas)
  if frame.curPuzzle == nil then
	frame.curPuzzle = Main:getGrid();
	frame.w = getPuzzleW(frame.curPuzzle);
  end
  assert(frame.curPuzzle ~= nil);
  assert(frame.w ~= nil and frame.w > 0);
  assert(frame.wpx ~= nil and frame.wpx > 0);

  local last = frame.w - 1;
  local tile_w = (frame.wpx - INSETS * 2 - SPACING * last) / frame.w;
  local transpTable = transpTables[frame.w];
  local realNbr;

  local dt = tile_w + SPACING;
  local ypx = INSETS;
  local xpx = 0.;
  local i = 0;

  for y = 0, last do
	xpx = INSETS;
	for x = 0, last do
	  i = y * frame.w + x;
	  realNbr = transpTable[frame.curPuzzle[i]];
	  if realNbr ~= 0 then
		canvas:drawRect(xpx, ypx, xpx + tile_w, ypx + tile_w
						, 0xB0FF0000, 0xA5FF0000, 8);
		drawTextCenter(canvas, tostring(realNbr)
					   , xpx + (tile_w / 2), ypx + (tile_w / 2));
	  end
	  xpx = xpx + dt;
	end
	ypx = ypx + dt;
  end

end

function frame:onSizeChange(x, _)
  frame.wpx, _ = x;
  frame:queryRedraw();
end

function frame:onEvent(e, ...)
  if (e == "SELECTED_GRID_CHANGED") then
	frame:reloadGrid();
  end
end

frame:setCallback('onDraw', frame.onDraw);
frame:setCallback('onSizeChange', frame.onSizeChange);

frame:registerEvent('SELECTED_GRID_CHANGED');

transpTables = {
  __index = function(t, key)
	local ttab = rawget(t, key);

	if ttab ~= nil then
	  return ttab;
	end
	ttab = Main:getTableToReal(key);
	rawset(t, key, ttab);
	return ttab;
end}
setmetatable(transpTables, transpTables);
