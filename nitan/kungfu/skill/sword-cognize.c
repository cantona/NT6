// sword-cognize.c
// 劍道修養

inherit SKILL;

int valid_learn(object me)
{
        return notify_fail("劍道修養是你武學方面的領悟，無法"
                           "通過簡單學習獲得提升。\n");
}

int valid_research(object me)
{
        return notify_fail("劍道修養來自你對實戰體會的汲取吸"
                           "收，無法通過研究提升。\n");
}
