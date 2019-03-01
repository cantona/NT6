#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xixing-xiaofa", 1);
        return lvl * lvl * 15 * 2 / 100 / 200;
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 80)
                return notify_fail("你的基本內功火候不足，不能學吸功入地小法。\n");

        if( query("gender", me) == "無性" && me->query_skill("xixing-xiaofa",1)>99 )
                return notify_fail("你無根無性陰陽不調，難以領會高深的吸功入地小法。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("xixing-xiaofa", 1))
                return notify_fail("你的基本內功水平有限，不能領會更高深的吸功入地小法。\n");

        return ::valid_learn(me);
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int jiali;

        if ((int) me->query_skill("xixing-xiaofa", 1) < 80 ||
            ! living(me))
                return;

        if( (jiali=query("jiali", ob))<1 )
                return;

        ap = ob->query_skill("force");
        dp = me->query_skill("force");
        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage" : -damage ]);

                switch (random(3))
                {
                case 0:
                        result += ([ "msg" : HIM "$N" HIM "只覺得內力源源而瀉"
                                             "，轉如地下，不由得大吃一驚。\n" NOR ]);
                        break;
                case 1:
                        result += ([ "msg" : HIM "$N" HIM "只覺得發出的內力猶"
                                             "如石沉大海，被$n盡數轉如地下。\n" NOR ]);
                        break;

                default:
                        result += ([ "msg" : HIM "$N" HIM "不住催動內力，但是"
                                             "只覺得$n竟似毫不費力。\n" NOR ]);
                        break;
                }
                return result;
        }
}

int practice_skill(object me)
{
        return notify_fail("吸功入地小法只能用學(learn)或練毒的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        // 為了NPC向問天能夠施展天寰神訣的POWERUP，故意設定為這樣。
        return __DIR__"tianhuan-shenjue/" + func;
}