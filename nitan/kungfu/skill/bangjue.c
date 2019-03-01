// bangjue.c 打狗棒心法

inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("staff", 1) < 30)
                return notify_fail("你的基本杖法太差, 還領會不了棒決。\n");
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("打狗棒心法只能靠學(learn)來提高。\n");
}
