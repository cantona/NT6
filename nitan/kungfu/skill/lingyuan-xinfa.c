// lingyuan-xinfa.c 靈元心法
// written by deaner
// Modified by Venus Oct.1997

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
    return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("靈元心法只能用學習的來增加熟練度。\n");
}

string exert_function_file(string func)
{
    return SKILL_D("lingyuan-xinfa/") + func;
}