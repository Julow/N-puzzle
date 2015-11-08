-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   start_activity.lua                                 :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/07 13:47:07 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/08 15:57:56 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local puzzleFrame = puzzleFrame;
assert(puzzleFrame ~= nil)

function puzzleFrame:onDraw(canvas)
   print("puzzleFrame:onDraw: ", x, y, a);
   ft.ptab(self);
   canvas:drawRect(0, 0, 102, 120, 0xFF000000, 0xFFEE6000, 3);
   canvas:drawText();
   if self.curPuzzle ~= nil then
	  assert(self.w ~= nil and self.w > 0);
	  assert(self.wpx ~= nil and self.wpx > 0);

	  local dt = self.wpx / self.w;
	  local ypx = 0.;
	  local xpx = 0.;
	  local last = self.w - 1;

	  for y = 0, last do
		 xpx = 0.;
		 for x = 0, last do
			canvas:drawRect(xpx, ypx, xpx + dt, ypx + dt
							, 0xFF000000, 0xFFEE6000, 3);
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


puzzleFrame.curPuzzle = {};
puzzleFrame.w = 3;
-- ft.ptab(puzzleFrame);
-- ft.ptab(AView);
-- ft.ptab(Canvas);
