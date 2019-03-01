// baicao-jue.c 百草訣
// Edit By Vin On 26/2/2001
// 很難學的知識技能，達到二百五十級可以栽培七星海棠。

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "medical"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("medical", 1) < 150)
                return notify_fail("你的基本醫術造詣太淺，無"
                                   "法領會深奧的百草訣。\n");

        if ((int)me->query_skill("yaowang-miaoshu", 1) < 150)
                return notify_fail("你的藥王妙術造詣太淺，無"
                                   "法領會深奧的百草訣。\n");

        if ((int)me->query_skill("medical", 1) < (int)me->query_skill("baicao-jue", 1))
                return notify_fail("你的基本醫術水平有限，無"
                                   "法掌握更深奧的百草訣。\n");

        if ((int)me->query_skill("yaowang-miaoshu", 1) < (int)me->query_skill("baicao-jue", 1))
                return notify_fail("你的藥王妙術水平有限，無"
                                   "法掌握更深奧的百草訣。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("百草訣只能通過學習獲得長進。\n");
}