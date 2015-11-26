-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   puzzle_pane.lua                                    :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/17 18:42:10 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/26 16:33:08 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local pane = {};
local frame = _G['bookmark-holder'];
assert(frame ~= nil);

function frame:onPuzzlesLoaded(names)
  local bm;

  print('frame:onPuzzlesLoaded(names)', names);
  ft.ptab(names);
  frame:unregisterEvent('onPuzzlesLoaded');
  pane.names = names;
  pane.count = #names + (names[0] == nil and 0 or 1);
  frame.refreshAllBookmarks(names, pane.count);
end
frame:registerEvent("onPuzzlesLoaded");
