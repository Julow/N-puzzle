-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   start_activity.lua                                 :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/07 13:47:07 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/08 17:24:20 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local puzzleFrame = puzzleFrame;
assert(puzzleFrame ~= nil)

function puzzleFrame:onDraw(canvas)
   print("puzzleFrame:onDraw: ", x, y, a);
   ft.ptab(self);
   -- canvas:drawText();
   if self.curPuzzle ~= nil then

	  assert(self.w ~= nil and self.w > 0);
	  assert(self.wpx ~= nil and self.wpx > 0);

	  local insets = 5.; -- INSET BORDER OF THE VIEW
	  local spacing = 2.; -- SPACING BETWEEN TILES

	  local last = self.w - 1;
	  local tile_w = (self.wpx - insets * 2 - spacing * last
					 ) / self.w;

	  local dt = tile_w + spacing;
	  local ypx = insets;
	  local xpx = 0.;
	  local i = 0;

	  for y = 0, last do
		 xpx = insets;
		 for x = 0, last do
			i = y * self.w + x;
			-- if self.curPuzzle[i] ~= nil then
			   canvas:drawRect(xpx, ypx, xpx + tile_w, ypx + tile_w
							   , 0xB0FF0000, 0xA5FF0000, 8);
			-- end
			xpx = xpx + dt;
		 end
		 ypx = ypx + dt;
	  end

   end
end

function puzzleFrame:onSizeChange(x, _)
   print("puzzleFrame:onSizeChange: ", x, y, a);
   self.wpx, _ = x;
   puzzleFrame:queryRedraw();
end

puzzleFrame:setCallback('onDraw', puzzleFrame.onDraw);
puzzleFrame:setCallback('onSizeChange', puzzleFrame.onSizeChange);
puzzleFrame:setCallback('onMouseMove', function(self, x, y, _)
						   print("bordel", x, y);
									 end
);
puzzleFrame:hookMouseMove(1);

puzzleFrame.curPuzzle = {};
puzzleFrame.w = 5;
-- ft.ptab(puzzleFrame);
-- ft.ptab(AView);
-- ft.ptab(Canvas);
