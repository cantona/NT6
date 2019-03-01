// taohua-yaoli.c

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "medical"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("medical", 1) < 100)
                return notify_fail("你的基本醫術造詣太淺，無"
                                   "法領會深奧的桃花藥理。\n");

        if ((int)me->query_skill("medical", 1) < (int)me->query_skill("taohua-yaoli", 1))
                return notify_fail("你的基本醫術水平有限，無"
                                   "法掌握更深奧的桃花藥理。\n");

        return 1;
}
