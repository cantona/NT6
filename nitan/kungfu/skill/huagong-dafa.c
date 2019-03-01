// huagong-dafa.c 化功大法
// Modified by rcwiz 2003

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        // return force == "guixi-gong";
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("huagong-dafa", 1);
        return lvl * lvl * 15 * 20 / 100 / 200;
}

int valid_learn(object me)
{
        if( query("character", me) == "光明磊落" )
                return notify_fail("你心中暗想：我為人光明磊落，豈能學習這種害人武功？\n");

        if( query("character", me) == "狡黠多變" )
                return notify_fail("你心中暗想：我雖然不是謙謙君子，但這種損人不利己的武功學來何用？\n");

        if( query("con", me)<30 )
                return notify_fail("你試著運轉了一下內力，登時覺得胸悶難耐！\n");

        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("你的基本內功火候不足，不能學化功大法。\n");

        if ((int)me->query_skill("poison", 1) < 120)
                return notify_fail("你的基本毒技火候不足，不能學化功大法。\n");

        if( query("gender", me) == "無性" && me->query_skill("huagong-dafa",1)>99 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的化功大法。\n");

        if ((int)me->query_skill("poison", 1) < (int)me->query_skill("huagong-dafa", 1)
        &&      (int)me->query_skill("poison", 1) < 320 )
                return notify_fail("你的基本毒技水平有限，不能領會更高深的化功大法。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("huagong-dafa", 1))
                return notify_fail("你的基本內功水平有限，不能領會更高深的化功大法。\n");

        return ::valid_learn(me);
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int jiali;

        if ((int) me->query_skill("huagong-dafa", 1) < 80 ||
            ! living(me))
                return;

        if( (jiali=query("jiali", ob))<1 )
                return;

        ap = ob->query_skill("force") + ob->query_skill("dodge");
        dp = me->query_skill("force") + me->query_skill("dodge");
        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage" : -damage ]);

                switch (random(3))
                {
                case 0:
                        result += ([ "msg" : HIM "$N" HIM "只覺得內力源源而瀉"
                                             "，不由得大吃一驚。\n" NOR ]);
                        break;
                case 1:
                        result += ([ "msg" : HIM "$N" HIM "只覺得發出的內力猶"
                                             "如石沉大海，不知所蹤。\n" NOR ]);
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
        return notify_fail("化功大法只能用學(learn)或練毒的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"huagong-dafa/" + func;
}