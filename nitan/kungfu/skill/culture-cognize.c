// 文學修養

inherit SKILL;
string type() { return "knowledge"; }

int valid_learn(object me)
{
        return notify_fail("文學修養是你文化方面的體會，無法"
                           "通過簡單學習獲得提升。\n");
}

int valid_research(object me)
{
        return notify_fail("文學修養來自你對文化精髓的汲取吸"
                           "收，無法通過研究提升。\n");
}