// yaowang-shenxin.c 藥王神辛
// Edit By Vin On 26/2/2001
// 很難學的知識技能，達到二百五十級可以栽培七星海棠。

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "poison"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("poison", 1) < 150)
                return notify_fail("你的基本毒技造詣太淺，無"
                                   "法領會深奧的藥王神辛。\n");

        if ((int)me->query_skill("dispel-poison", 1) < 150)
                return notify_fail("你的妙手驅毒造詣太淺，無"
                                   "法領會深奧的藥王神辛。\n");

        if ((int)me->query_skill("poison", 1) < (int)me->query_skill("yaowang-shenxin", 1))
                return notify_fail("你的基本毒技水平有限，無"
                                   "法掌握更深奧的藥王神辛。\n");

        if ((int)me->query_skill("dispel-poison", 1) < (int)me->query_skill("yaowang-shenxin", 1))
                return notify_fail("你的妙手驅毒水平有限，無"
                                   "法掌握更深奧的藥王神辛。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("藥王神辛只能通過學習獲得長進。\n");
}