-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   puzzle_pane.lua                                    :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/17 18:42:10 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/25 19:10:20 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local pane = {};
local frame = _G['bookmark-holder'];
assert(frame ~= nil);

function frame:onPuzzlesLoaded(puzzles)
  local bm;

  ft.ptab(puzzles);
  frame:unregisterEvent('onPuzzlesLoaded');
  pane.puzzles = puzzles;
  pane.count = #puzzles + (puzzles[0] == nil and 0 or 1);
  frame.refreshAllBookmarks(puzzles, pane.count);
end
frame:registerEvent("onPuzzlesLoaded");
