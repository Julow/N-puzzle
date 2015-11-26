-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   utils.lua                                          :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/12 21:02:12 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/26 15:15:55 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

ft = {};

ft.tostring = function(v)
	if type(v) == 'function' then
		return string.gsub(tostring(v), 'function: ', 'FN');
	elseif type(v) == 'table' then
		return string.gsub(tostring(v), 'table: ', 'TA');
	elseif type(v) == 'userdata' then
		return string.gsub(tostring(v), 'userdata: ', 'UD');
	end
	return tostring(v);
end

ft.ptab = function(t, p1, p2, p3, p4)
	local maxDepth = p1 or -1;
	local curDepth = p2 or 0;
	local excludedK = p3 or {[os] = true, [package] = true
		, [math] = true, [string] = true, [debug] = true
		, [io] = true, [bit32] = true, [table] = true
		, [coroutine] = true, [utf8] = true};
	local curTab = p4 or '';
	local header = string.format('%1.1d*%s', curDepth, curTab);
	local curCol = '\27[4'..tostring(1 + (curDepth) % 5)..'m'
	local nextTab = curTab..curCol..'**'..'\27[0m';
	local empty = true

	excludedK[t] = true;
	if curDepth == 0 then
		print(string.format('******%s (#%d) metatab:%s ***************'
			, tostring(t), tostring(#t), tostring(getmetatable(t))));
	end
	for k,v in pairs(t) do
		local expand = maxDepth ~= curDepth and type(v) == 'table'
			and excludedK[v] == nil;
		local mt = '';
		local lcol = '';
		local rcol = '';
		local kstr = string.sub(ft.tostring(k), -30 + 2 * curDepth);

		empty = false
		if type(v) == 'table' then
			mt = string.format(' mt{%s}', ft.tostring(getmetatable(v)))
		end
		if expand then
			lcol = curCol
			rcol = '\27[0m'
		end
		kstr = string.format('[%s]', kstr);
		kstr = string.format('%32s', kstr);
		kstr = string.sub(kstr, -32 + 2 * curDepth);
		print(string.format('%s%s%s%3.3s/%3.3s{%s}%s%s'
		, header, lcol, kstr, type(k), type(v), ft.tostring(v), rcol, mt));
		if expand then
			mt = ft.ptab(v, maxDepth, curDepth + 1, excludedK, nextTab);
		end
	end;
	if empty then
		print(string.format('%s', header));
	end
end

ft.pchildren = function(t, tab)
	tab = tab or '**';

	if t == nil or t[0] == nil or type(t[0]) ~= 'userdata' then
		print('wrong ft.pchildren Argument:', t);
		return ;
	end
	n = t.size and t:size() or 0;
	print(string.format('%s %s(%s) %dchildren'
		, tab, ft.tostring(t:getId()), ft.tostring(t), n));
	tab = tab..'**';
	for _, v in ipairs(t) do
		ft.pchildren(v, tab);
	end
end

ft.pparents = function(t)
	if t == nil or t[0] == nil or type(t[0]) ~= 'userdata' then
		print('wrong ft.pparents Argument:', t);
		return ;
	end
	p = t:getParent()
	n = t.size and t:size() or 0;
	if p == nil then
		print(string.format('** %s(%s) %dchildren'
			, ft.tostring(t:getId()), ft.tostring(t), n));
		return 2;
	else
		i = ft.pparents(p);
		tab = string.rep('**', i);
		print(string.format('%s %s(%s) %dchildren'
			,tab , ft.tostring(t:getId()), ft.tostring(t), n));
		return i + 1;
	end
end

print('loaded ftlua/res/utils.lua');
