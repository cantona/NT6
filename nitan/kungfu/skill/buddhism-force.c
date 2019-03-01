// buddhism-force.c

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }
int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("buddhism-force", 1);
        return lvl * lvl * 22 * 15 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl;

        lvl = (int)me->query_skill("buddhism-force", 1);

        if( query("gender", me) == "無性" )
                return notify_fail("你無根無性，陰陽不調，難以領會金剛不壞神功。\n");

        if( query("sex/times", me) || query("gender", me) != "男性" )
                return notify_fail("學金剛不壞神功必須是童子之身。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("金剛不壞神功只能用學(learn)的來增加熟練度。\n");
}
string exert_function_file(string func)
{
        return __DIR__"buddhism-force/" + func;
}


void skill_improved(object me)
{
        if( (int)me->query_skill("buddhism-force", 1) == 120 &&
             !query("sl_gift/con", me) )
        {
                addn("con", 1, me);
                set("sl_gift/con", 1, me);
                tell_object(me, HIM "\n你的金剛不壞神功學有所成，提高了你的根骨。\n" NOR);
        }
}
