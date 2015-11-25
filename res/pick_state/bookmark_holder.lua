-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   bookmark_holder.lua                                :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/16 15:14:38 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/25 19:10:16 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local frame = _G['bookmark-holder']
assert(frame ~= nil)

function frame.refreshOneBookmark(puzzles, count, i)
  local bm = frame:at(i);

  if (i < count) then
	bm:setVisibility(1);
  else
	bm:setVisibility(0);
  end
end

function frame.refreshAllBookmarks(puzzles, count)
  local i = 0;

  while (i < count) do
	frame.refreshOneBookmark(puzzles, count, i);
	i = i + 1;
  end
end

function bookmarkOnClick1(self)
  local p = self:getParent();

  PickState:selectGrid(p.i);
end

function frame:at(i)
  local sz = frame:size();
  local v;
  local b1;
  local b2;

  if i < sz then
	return frame:rawat(i);
  end
  while (sz < i + 1) do
	v = createView('Bookmark', 'Bookmark' .. tostring(sz));
	b1 = v:at(0);
	b2 = v:at(1);
	frame:addView(v);
	v:setVisibility(0);
	b1:setCallback("onClick", bookmarkOnClick1);
	v.i = sz;
	sz = sz + 1;
  end
  return v;
end

frame.rawat = getmetatable(frame).at;
