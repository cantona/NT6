// mathematics

inherit SKILL;

string type() { return "knowledge"; }

void skill_improved(object me)
{
}

int valid_learn(object me)
{
        if ((int)me->query_skill("literate", 1) < 100)
                return notify_fail("你連讀書寫字都沒學好，怎麼學習算術？\n");

        if ((int)me->query_skill("literate", 1) < (int)me->query_skill("mathematics", 1))
                return notify_fail("你的讀書寫字水平有限，無法掌握更深奧的算術。\n");

        return 1;

}
