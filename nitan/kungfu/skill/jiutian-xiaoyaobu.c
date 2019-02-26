// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit SKILL;

string *dodge_msg = ({
        "$n身形左閃右晃，姿勢瀟灑之極，一招[飛昇九天]輕巧地躲開$N的進攻。\n",
        "$n宛如一屢青煙，飄忽不定，令人琢磨不定，一招[魔神無形]閃到了$N的身後。\n",
        "$n姿態幽雅之極，躲閃之中絲毫不顯狼狽之態，一招[上天入地]避開了$N的攻擊。\n",
        "$n身形突然連晃數下，宛如雲霧中的幻靈，一招[洞徹九幽]躲開了$N的攻擊。\n",
});

int valid_enable(string usage)
{
        return usage == "dodge";
}

int valid_learn(object me)
{
        int lvl;

        lvl = me->query_skill("jiutian-xiaoyaobu", 1);
        if (lvl > 300) lvl = 300;

        if( query("max_neili", me)<3000+lvl*20 )
                return notify_fail("你試着走了兩步，頓覺胸"
                                   "口煩惡之極，看來是內力不濟。\n");
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("jiutian-xiaoyaobu", 1) < 100 ||
            query("family/family_name", ob) == "少林派" || 
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) * 3/5 +
             me->query_skill("jiutian-xiaoyaobu", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                result += (["msg" : HIW "$n" HIW "身形如同鬼魅般地晃動了幾下，如流星一般躲開了$N"
                                    HIW "的攻擊。\n" NOR]);

                return result;
        } else
        if (mp >= 100)
        {
                result = HIY "$n" HIY "身形如同鬼魅般地晃動了幾下，可是$N"
                         HIY "反應奇快，身形一閃，攔住了$n" HIY "的去路\n" NOR;

                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("jiutian-xiaoyaobu", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 80;
        if (lvl < 250) return 100;
        if (lvl < 300) return 120;
        if (lvl < 350) return 140;
        return 150;
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太差了，難以練習九天逍遙步。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠了，無法練習九天逍遙步。\n");

        me->receive_damage("qi", 65);
        addn("neili", -65, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jiutian-xiaoyaobu/" + action;
}