-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   puzzleFrame.lua                                    :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/11 13:01:05 by ngoguey           #+#    #+#             --
--   Updated: 2015/12/08 15:03:25 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local INSETS = 5.; -- INSET BORDER OF THE VIEW
local SPACING = 1.; -- SPACING BETWEEN TILES
-- local PUZZLEFRAME_TEXT_SIZE = 20;

local f_frame = puzzleFrame;
assert(f_frame ~= nil)
local f_transpTables, f_curPuzzle, f_w;

-- DRAW ------------------------------------------------------------------------
local function gridFontSize(w)
  return math.max(20 + 9 - w, 9);
end

local function drawTextCenter(canvas, text, x, y)
  local fontSize = gridFontSize(f_w);
  local text_w, text_h = canvas:measureText(text, fontSize);

  canvas:drawText(text, x - (text_w / 2)
				  , y - (text_h / 2), 0xFF555555, fontSize);
end

function f_frame.reloadGrid()
  f_curPuzzle = Main:getGrid();
  f_w = getPuzzleW(f_curPuzzle);
  f_frame:queryRedraw();
  return ;
end

function f_frame.setGrid(gr, w)
  f_curPuzzle = gr;
  f_w = w;
  f_frame:queryRedraw();
  return ;
end

function f_frame:onDraw(canvas)
  if f_curPuzzle == nil then
	f_curPuzzle = Main:getGrid();
	f_w = getPuzzleW(f_curPuzzle);
  end
  assert(f_curPuzzle ~= nil);
  assert(f_w ~= nil and f_w > 0);
  assert(f_wpx ~= nil and f_wpx > 0);

  local f_color = GridColor + 0xA5000000
  local f_borderColor = GridColor + 0xB0000000

  local last = f_w - 1;
  local tile_w = (f_wpx - INSETS * 2 - SPACING * last) / f_w;
  local transpTable = f_transpTables[f_w];
  local realNbr;

  local dt = tile_w + SPACING;
  local ypx = INSETS;
  local xpx = 0.;
  local i = 0;

  for y = 0, last do
	xpx = INSETS;
	for x = 0, last do
	  i = y * f_w + x;
	  realNbr = transpTable[f_curPuzzle[i]];
	  if realNbr ~= 0 then
		canvas:drawRect(xpx, ypx, xpx + tile_w, ypx + tile_w
						, f_color, f_borderColor, 8);
		drawTextCenter(canvas, tostring(realNbr)
					   , xpx + (tile_w / 2), ypx + (tile_w / 2));
	  end
	  xpx = xpx + dt;
	end
	ypx = ypx + dt;
  end

end

-- OTHER CALLBACKS -------------------------------------------------------------
function f_frame:onSizeChange(x, _)
  f_wpx, _ = x;
  f_frame:queryRedraw();
end

function f_frame:onEvent(e, ...)
  if (e == "SELECTED_GRID_CHANGED") then
	f_frame.reloadGrid();
  end
end

f_frame:setCallback('onDraw', f_frame.onDraw);
f_frame:setCallback('onSizeChange', f_frame.onSizeChange);

f_frame:registerEvent('SELECTED_GRID_CHANGED');

-- TRANSPOSITION TABLES --------------------------------------------------------
f_transpTables = {
  __index = function(t, key)
	local ttab = rawget(t, key);
	key = math.tointeger(key);

	if ttab ~= nil then
	  return ttab;
	end
	ttab = Main:getTableToReal(key);
	rawset(t, key, ttab);
	return ttab;
end}
setmetatable(f_transpTables, f_transpTables);
