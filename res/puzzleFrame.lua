-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   puzzleFrame.lua                                    :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/11 13:01:05 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/11 16:39:16 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local puzzleFrame = puzzleFrame;
assert(puzzleFrame ~= nil)

PUZZLEFRAME_TEXT_SIZE = 16;

function drawTextCenter(canvas, text, x, y)
   text_w, text_h = canvas:measureText(text, PUZZLEFRAME_TEXT_SIZE);
   canvas:drawText(text, x - (text_w / 2), y - (text_h / 2), 0xFF555555, PUZZLEFRAME_TEXT_SIZE);
end

function puzzleFrame:reloadGrid()
   puzzleFrame.curPuzzle = getGrid();
   puzzleFrame.w = getPuzzleW(puzzleFrame.curPuzzle);
   puzzleFrame:queryRedraw();
   return ;
end

function puzzleFrame:onDraw(canvas)
   if self.curPuzzle == nil then
	  puzzleFrame:reloadGrid()
	  -- TODO: relou de pas pouvoir acceder a un onLoad
   end
   assert(self.curPuzzle ~= nil);
   assert(self.w ~= nil and self.w > 0);
   assert(self.wpx ~= nil and self.wpx > 0);

   canvas:setFont("/Library/Fonts/Arial Black.ttf");

   local insets = 5.; -- INSET BORDER OF THE VIEW
   local spacing = 1.; -- SPACING BETWEEN TILES

   local last = self.w - 1;
   local tile_w = (self.wpx - insets * 2 - spacing * last) / self.w;

   local dt = tile_w + spacing;
   local ypx = insets;
   local xpx = 0.;
   local i = 0;

   for y = 0, last do
	  xpx = insets;
	  for x = 0, last do
		 i = y * self.w + x;
		 if self.curPuzzle[i] ~= 0 then
			canvas:drawRect(xpx, ypx, xpx + tile_w, ypx + tile_w
							, 0xB0FF0000, 0xA5FF0000, 8);
			drawTextCenter(canvas, tostring(self.curPuzzle[i])
						   , xpx + (tile_w / 2), ypx + (tile_w / 2));
		 end
		 xpx = xpx + dt;
	  end
	  ypx = ypx + dt;
   end

end

function puzzleFrame:onSizeChange(x, _)
   print("puzzleFrame:onSizeChange: ", x, y, a);
   self.wpx, _ = x;
   puzzleFrame:queryRedraw();
end

puzzleFrame:setCallback('onDraw', puzzleFrame.onDraw);
puzzleFrame:setCallback('onSizeChange', puzzleFrame.onSizeChange);

-- ft.ptab(puzzleFrame);
-- ft.ptab(AView);
-- ft.ptab(Canvas);
