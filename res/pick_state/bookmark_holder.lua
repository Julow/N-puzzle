-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   bookmark_holder.lua                                :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/16 15:14:38 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/26 18:41:58 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local frame = _G['bookmark-holder']
assert(frame ~= nil)

function frame.refreshOneBookmark(name, i)
  local bm = frame:at(i);
  local b1;

  bm:setText(name);
  bm:setVisibility(1);
  if frame.curHighlight ~= nil then
	b1 = bm:at(0);
	if frame.curHighlight == i then
	  b1:lockHighlight(1);
	else
	  b1:lockHighlight(0);
	end
  end
end

function frame.refreshAllBookmarks(names, count)
  local i = 0;
  local nbm = frame:size();

  while (i < count) do
	frame.refreshOneBookmark(names[i], i);
	i = i + 1;
  end
  while (i < nbm) do
	frame.rawat(i):setVisibility(0);
	i = i + 1;
  end
end

function bookmarkOnClick1(self)
  local p = self:getParent();

  PickState:selectGrid(p.i);
end

function frame:at(i)
  local sz = frame:size();
  local v, b1, b2;

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
