inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "medical"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("medical", 1) < 100)
                return notify_fail("你的基本醫術造詣太淺，無"
                                   "法領會深奧的本草術理。\n");

        if ((int)me->query_skill("medical", 1) < (int)me->query_skill("xingxiu-qishu", 1))
                return notify_fail("你的基本醫術水平有限，無"
                                   "法掌握更深奧的本草術理。\n");

        if ((int)me->query_skill("bencao-changshi", 1) < (int)me->query_skill("bencao-shuli", 1))
                return notify_fail("你的本草常識水平有限，無"
                                   "法掌握更深奧的本草術理。\n");

        return 1;
}
