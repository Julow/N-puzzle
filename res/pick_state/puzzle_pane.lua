-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   puzzle_pane.lua                                    :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/17 18:42:10 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/28 11:47:28 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local pane = {};
local frame = _G['bookmark-holder'];
assert(frame ~= nil);

function frame:GRID_LIST_UPDATE(names, n)
  local bm;

  pane.names = names;
  pane.count = n;
  frame.curHighlight = PickState:getMainGridId();
  frame.refreshAllBookmarks(names, n);
end

function frame:SELECTED_GRID_CHANGED(i)
  local iPrev = frame.curHighlight;

  frame.curHighlight = i;
  if iPrev < pane.count then
	frame.refreshOneBookmark(pane.names[iPrev], iPrev);
  end
  frame.refreshOneBookmark(pane.names[i], i);
end

frame:registerEvent("GRID_LIST_UPDATE");
frame:registerEvent("SELECTED_GRID_CHANGED");
