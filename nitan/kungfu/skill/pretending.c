// yirong.c 易容術

inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("易容術只能靠學(learn)來提高。\n");
}

