-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   bookmark_holder.lua                                :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/16 15:14:38 by ngoguey           #+#    #+#             --
--   Updated: 2015/12/05 17:21:05 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local f_frame = _G['bookmark-holder'];
assert(f_frame ~= nil);
local f_names, f_curHighlight, f_count;

-- DRAW ------------------------------------------------------------------------
function f_frame.refreshOneBookmark(i)
  local bm = f_frame:at(i);
  local b1;

  bm:setText(f_names[i]);
  bm:setVisibility(true);
  if f_curHighlight ~= nil then
	b1 = bm:at(0);
	if f_curHighlight == i then
	  b1:lockHighlight(true);
	else
	  b1:lockHighlight(false);
	end
  end
end

function f_frame.refreshAllBookmarks()
  local i = 0;
  local nbm = f_frame:size();

  while (i < f_count) do
	f_frame.refreshOneBookmark(i);
	i = i + 1;
  end
  while (i < nbm) do
	local v = f_frame:rawat(i);
	v:setVisibility(false);
	i = i + 1;
  end
end

-- BOOKMARK HANDLING -----------------------------------------------------------
function f_frame.createbookmark(i)
  local v, b1, b2;
  v = createView('Bookmark');
  v:setId('Bookmark' .. tostring(i));
  v.i = i;
  b1 = v:at(0);
  b2 = v:at(1);
  f_frame:addView(v);
  v:setVisibility(false);
  b1:setCallback("onClick",
				 function ()
				   PickState:selectGrid(v.i);
				 end
  );
  b2:setCallback("onClick",
				 function ()
				   PickState:deleteGrid(v.i);
				 end
  );
  return v;
end

function f_frame:at(i)
  local sz = f_frame:size();

  if i < sz then
	return f_frame:rawat(i);
  end
  while (sz < i + 1) do
	v = f_frame.createbookmark(sz)
	sz = sz + 1;
  end
  return v;
end

f_frame.rawat = getmetatable(f_frame).at;

-- EVENT HANDLING --------------------------------------------------------------
function f_frame:GRID_LIST_UPDATE(names, n)
  print('f_frame:GRID_LIST_UPDATE');
  f_names = names;
  f_count = n;
  f_curHighlight = PickState:getMainGridId();
  f_frame.refreshAllBookmarks();
end

function f_frame:SELECTED_GRID_CHANGED(i)
  print('f_frame:SELECTED_GRID_CHANGED');
  local iPrev = f_curHighlight;

  f_curHighlight = i;
  if iPrev < f_count then
	f_frame.refreshOneBookmark(iPrev);
  end
  f_frame.refreshOneBookmark(i);
end

f_frame:registerEvent("GRID_LIST_UPDATE");
f_frame:registerEvent("SELECTED_GRID_CHANGED");
