t = 
	{
		['name'] = '新手地火术',
		['level'] = 2,
		['careerNo'] = 7,
		['desc'] = '对全体目标造成法术造成 %d 伤害。和的什么什么',
	    ['gongjili'] = {
		    [1] = 12,
		    [2] = 22,
		}
	}

s = string.format(t.desc, t.gongjili[1], t.gongjili[2])
print(s)