// xuantian-zhi.c 玄天無情指
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N左指揮出，一式"BLU"「黯然消魂」"NOR"，削向$n的掌緣",
        "lvl" : 0,
        "skill_name" : "黯然消魂"
]),
([        "action" : "$N全身之力聚於一指，一式"HIC"「天似無情」"NOR"，指向$n的胸前",
        "lvl" : 15,
        "skill_name" : "天似無情"
]),
([        "action" : "$N左掌貼於神道穴，右手一式"MAG"「情根深種」"NOR"，向$n的$l劃過",
        "lvl" : 25,
        "skill_name" : "情根深種"
]),
([        "action" : "$N雙目怒視，一式"CYN"「情在天涯」"NOR"，雙指拂向$n的額、頸、肩、臂、胸
、背",
        "lvl" : 45,
        "skill_name" : "情在天涯"
]),
([        "action" : "$N一式"HIR"「獨飲情傷」"NOR"，左掌掌心向外，右指蓄勢點向$n的$l",
        "lvl" : 60,
        "skill_name" : "獨飲情傷"
]),
([        "action" : "$N右手伸出，十指叉開，一式"HIW"「無訴別情」"NOR"，小指拂向$n的太淵穴",
        "lvl" : 70,
        "skill_name" : "無訴別情"
]),
([        "action" : "$N雙迸出無數道勁氣，一式"HIG"「情意綿綿」"NOR"射向$n的全身",
        "lvl" : 80,
        "skill_name" : "情意綿綿"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練玄天指必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學玄天指。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力太弱，無法練玄天指。\n");

        if ((int)me->query_skill("finger", 1) < 80)
                return notify_fail("你的基本指法火候不夠，無法練玄天指。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("xuantian-zhi", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的玄天指。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("jing", me)<40 )
                return notify_fail("你的精太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練玄天無情指。\n");
        me->receive_damage("jing", 35);
        addn("neili", -15, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("xuantian-zhi", 1);
        flvl=query("jiali", me);
        if (lvl < 100 || flvl < 20 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("xuantian_zhi",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 50 + random(lvl / 20) ])))
        {
                return HIW "$n" HIW "只感覺陰寒之氣攻心，全身癱軟，嘴皮烏紫，面龐竟籠罩了一層寒霜。\n" NOR;
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
        int d_e1 = 35;
        int d_e2 = 55;
        int p_e1 = -25;
        int p_e2 = -5;
        int f_e1 = 240;
        int f_e2 = 340;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("xuantian-zhi", 1);
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
                "damage_type" : random(2) ? "刺傷" : "瘀傷",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"xuantian-zhi/" + action;
}

int help(object me)
{
        write(HIC"\n玄天無情指："NOR"\n");
        write(@HELP

    日月神教黑木崖武功。梅莊二莊主黑白子的凌厲指法，招數中
帶有陰寒內勁，可傷人於無形之中。

        學習要求：
                葵花心法80級
                內力150
HELP
        );
        return 1;
}

