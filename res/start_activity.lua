-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   start_activity.lua                                 :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/07 13:47:07 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/08 13:36:27 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local puzzleFrame = puzzleFrame;
assert(puzzleFrame ~= nil)

function puzzleFrame:onDraw(canvas)
   print('from lua:', 'puzzleFrame:onDraw()', self);
   canvas:drawRect();
   canvas:drawText();
end

puzzleFrame:queryRedraw();
puzzleFrame:setCallback('onDraw', puzzleFrame.onDraw);
ft.ptab(puzzleFrame);
ft.ptab(AView);
ft.ptab(Canvas);
puzzleFrame:queryRedraw();
