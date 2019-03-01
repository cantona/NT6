// 技能修養

inherit SKILL;
string type() { return "technic"; }

int valid_learn(object me)
{
        return notify_fail("技能修養是你工藝技能方面的體會，無法"
                           "通過簡單學習獲得提升。\n");
}

int valid_research(object me)
{
        return notify_fail("技能修養來自你對工藝技術精髓的熟悉"
                           "運用，無法通過研究提升。\n");
}