//lingshe_zhangfa.c 靈蛇杖法

#include "ansi.h"
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N使出一招"HIB"「靈蛇出洞」"NOR"，手中$w大開大闔掃向$n的$l",
        "lvl"    : 0,
        "skill_name" : "靈蛇出洞"
]),
([        "action" : "$N手中$w陣陣風響，一招"BLU"「搖頭擺尾」"NOR"向$n的$l攻去",
        "lvl"    : 20,
        "skill_name" : "搖頭擺尾"
]),
([        "action" : "$N舉起$w，居高臨下使一招"MAG"「靈蛇下澗」"NOR"砸向$n的$l",
        "lvl"    : 30,
        "skill_name" : "靈蛇下澗"
]),
([        "action" : "$N一招"HIM"「靈蛇挺身」"NOR"，手中$w猛烈掃向$n的$l",
        "lvl"    : 40,
        "skill_name" : "靈蛇挺身"
]),
([        "action" : "$N使出一招"YEL"「蛇遊蟒走」"NOR"，$w左右迂迴向$n的$l掃去",
        "lvl"    : 50,
        "skill_name" : "蛇遊蟒走"
]),
([        "action" : "$N手中$w一揮，使出一招"MAG"「蛇纏左右」"NOR"，忽左忽右掃向$n的$l",
        "lvl"    : 60,
        "skill_name" : "蛇纏左右"
]),
([        "action" : "$N使出一招"RED"「巨蟒下山」"NOR"，高舉手中$w，劈頭砸向$n的$l",
        "lvl"    : 80,
        "skill_name" : "巨蟒下山"
]),
([        "action" : "$N使出一招"HIR"「靈蛇出洞」"NOR"，手中$w猛一探，直掃$n的$l",
        "lvl"    : 100,
        "skill_name" : "靈蛇出洞"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠。\n");

        if ((int)me->query_skill("staff", 1) < 100)
                return notify_fail("你的基本杖法還不到家，不能學習靈蛇杖法。\n");

        if ((int)me->query_skill("staff", 1) < me->query_skil("linshe-zhangfa", 1))
                return notify_fail("你的基本杖法水平不夠，無法領會更高深的靈蛇杖法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練靈蛇杖法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練靈蛇杖法。\n");

        me->receive_damage("qi", 60);
        addn("neili", -69, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl,flvl;
        lvl = me->query_skill("lingshe-zhangfa",1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;
        if (!query_temp("weapon", me) || !query("snake_type", (query_temp("weapon", me))))
                       return;

       if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
              victim->affect_by("snake_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
       {
                return HIR "只聽$n痛呼了一聲，卻是被蛇杖頂端的小蛇咬了個正着！\n" NOR;
       }
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -50;
        int d_e2 = -20;
        int p_e1 = 5;
        int p_e2 = 40;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 210;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("lingshe-zhangfa", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : "挫傷",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"lingshe-zhangfa/" + action;
}
int help(object me)
{
        write(HIC"\n靈蛇杖法："NOR"\n");
        write(@HELP

    靈蛇杖法是西毒歐陽鋒的歹毒武功。杖法兇狠，兼且杖頭毒蛇
乘隙傷人，甚是陰毒。

        學習要求：
                蛤蟆功20級
                內力修為70
HELP
        );
        return 1;
}
