// sonfeng-jian.c 鬆風劍法
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N虛步提腰，一招"MAG"「彩蝶穿花」"NOR"，手中$w輕輕顫動，一劍劍點向$n的$l",
        "lvl" : 0,
        "skill_name" : "彩蝶穿花"
]),
([        "action" : "$N向前跨上一步，左手劍訣，右手$w使出一式"HIM"「鳳凰奪窩」"NOR"直刺$n的$l",
        "lvl" : 10,
        "skill_name" : "鳳凰奪窩"
]),
([        "action" : "$N身形往右一挫，左手劍訣，右手$w使出一式"GRN"「分花拂柳」"NOR"刺向$n的$l",
        "lvl" : 20,
        "skill_name" : "分花拂柳"
]),
([        "action" : "$N雙膝下沉，右手$w使出一式"RED"「力劃鴻溝」"NOR"，由下而上疾刺$n的$l",
        "lvl" : 50,
        "skill_name" : "力劃鴻溝"
]),
([        "action" : "$N一招"HIB"「顛倒陰陽」"NOR"，$w自上而下劃出一個大弧，平平地向$n的$l揮去",
        "lvl" : 60,
        "skill_name" : "顛倒陰陽"
]),
([        "action" : "$N上身往左側一擰，一招"HIW"「玉女投梭」"NOR"，右手$w反手向$n的$l揮去",
        "lvl" : 80,
        "skill_name" : "玉女投梭"
]),
([        "action" : "$N一招"BLU"「八方風雨」"NOR"，劍鋒平指，一氣呵成橫掃$n的$l",
        "lvl" : 100,
        "skill_name" : "八方風雨"
]),
([        "action" : "$N左腿提膝，手中$w斜指，一招"HIY"「平沙落雁」"NOR"刺向$n的$l",
        "lvl" : 120,
        "skill_name" : "平沙落雁"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不夠，無法修習鬆風劍法。\n");

        if ((int)me->query_skill("dodge") < 60)
                return notify_fail("你的輕功火候太淺，無法修習鬆風劍法。\n");

        if ((int)me->query_dex() < 25)
                return notify_fail("你的身法還不夠靈活，無法修習鬆風劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("songfeng-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的鬆風劍法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<40 || query("neili", me)<30 )
                return notify_fail("你的內力或氣不夠練鬆風劍法。\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
        return 1;
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
        int d_e1 = 10;
        int d_e2 = 35;
        int p_e1 = -20;
        int p_e2 = 0;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 100;
        int m_e2 = 190;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("songfeng-jian", 1);
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
                "damage_type" : random(2) ? "割傷" : "刺傷",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"songfeng-jian/" + action;

}
int help(object me)
{
        write(HIC"\n鬆風劍法："NOR"\n");
        write(@HELP

    鬆風劍法是青城派劍法。

        學習要求：
                青冥神功20級
                內力10
HELP
        );
        return 1;
}
