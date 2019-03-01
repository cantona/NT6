// 

inherit SKILL;

int valid_learn(object me)
{
        return notify_fail("精意神功是你對萬物方面的領悟，無法"
                           "通過簡單學習獲得提升。\n");
}

int valid_research(object me)
{
        return notify_fail("精意神功來自你在精意山莊對萬物領會的吸"
                           "收，無法通過研究提升。\n");
}