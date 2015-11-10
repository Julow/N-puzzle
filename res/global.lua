-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   global.lua                                         :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/09 18:00:27 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/10 18:45:36 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

function drawTextCenter(canvas, text, x, y)
	local text_w, text_h = canvas:measureText(text, PUZZLEFRAME_TEXT_SIZE);
	canvas:drawText(text, x - (text_w / 2), y - (text_h / 2)
					, 0xFFFFFFFF, PUZZLEFRAME_TEXT_SIZE);
end

function getPuzzleW(gr)
   local n = #gr + 1;
   local squared = math.sqrt(n);

   assert(n > 0);
   assert(squared * squared == n);
   return squared;
end

function enableTestOnView(v)
   v:hookMouseMove(1);
   v:setCallback('onMouseEnter',
				 function(self)
					print(self:getId(), 'onEnter');
   end);
   v:setCallback('onMouseLeave',
				 function(self)
					print(self:getId(), 'onLeave');
   end);
end

-- enableTestOnView(yellowL);
enableTestOnView(blue);
enableTestOnView(dbgbutton);
-- enableTestOnView(cyanL);
