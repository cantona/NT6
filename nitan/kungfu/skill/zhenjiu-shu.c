inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "medical"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("medical", 1) < 50)
                return notify_fail("你的基本醫術造詣太淺，無"
                                   "法領會針灸術。\n");

        if ((int)me->query_skill("medical", 1) < (int)me->query_skill("zhenjiu-shu", 1))
                return notify_fail("你的基本醫術水平有限，無"
                                   "法掌握更深奧的針灸術。\n");

        return 1;
}
