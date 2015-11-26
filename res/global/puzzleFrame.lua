-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   puzzleFrame.lua                                    :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/11 13:01:05 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/26 18:17:01 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local INSETS = 5.; -- INSET BORDER OF THE VIEW
local SPACING = 1.; -- SPACING BETWEEN TILES

local puzzleFrame = puzzleFrame;
local transpTables;
assert(puzzleFrame ~= nil)

PUZZLEFRAME_TEXT_SIZE = 16;

function drawTextCenter(canvas, text, x, y)
  text_w, text_h = canvas:measureText(text, PUZZLEFRAME_TEXT_SIZE);
  canvas:drawText(text, x - (text_w / 2)
				  , y - (text_h / 2), 0xFF555555, PUZZLEFRAME_TEXT_SIZE);
end

function puzzleFrame:reloadGrid()
  puzzleFrame.curPuzzle = Main:getGrid();
  puzzleFrame.w = getPuzzleW(puzzleFrame.curPuzzle);
  puzzleFrame:queryRedraw();
  return ;
end

function puzzleFrame:onDraw(canvas)
  if self.curPuzzle == nil then
	puzzleFrame.curPuzzle = Main:getGrid();
	puzzleFrame.w = getPuzzleW(puzzleFrame.curPuzzle);
	-- TODO: relou de pas pouvoir acceder a un onLoad
  end
  assert(self.curPuzzle ~= nil);
  assert(self.w ~= nil and self.w > 0);
  assert(self.wpx ~= nil and self.wpx > 0);

  -- canvas:setFont("/Library/Fonts/Arial Black.ttf");

  local last = self.w - 1;
  local tile_w = (self.wpx - INSETS * 2 - SPACING * last) / self.w;
  local transpTable = transpTables[self.w];
  local realNbr;

  local dt = tile_w + SPACING;
  local ypx = INSETS;
  local xpx = 0.;
  local i = 0;

  for y = 0, last do
	xpx = INSETS;
	for x = 0, last do
	  i = y * self.w + x;
	  realNbr = transpTable[self.curPuzzle[i]];
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

function puzzleFrame:onSizeChange(x, _)
  self.wpx, _ = x;
  puzzleFrame:queryRedraw();
end

function puzzleFrame:onEvent(e, ...)
  if (e == "onDisplayedGridChanged") then
	print('puzzleFrame:onEvent('..e..', ', ..., ')');
	self:reloadGrid();
  end
end

puzzleFrame:setCallback('onDraw', puzzleFrame.onDraw);
puzzleFrame:setCallback('onSizeChange', puzzleFrame.onSizeChange);

puzzleFrame:registerEvent("onDisplayedGridChanged");

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
