// fengmo-zhang.c 瘋魔杖法

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N斜舉$w, 一招"HIB"「秦王鞭石」"NOR"，斜肩鏟背砸向$n的$l",
        "lvl"    : 0,
        "skill_name" : "秦王鞭石"
]),
([        "action" : "$N一聲大喝，使出一招"GRN"「魯達拔柳」"NOR", 手中$w自下而上掃向$n的$l",
        "lvl"    : 39,
        "skill_name" : "魯達拔柳"
]),
([        "action" : "$N使出一招"BLU"「霸王扛鼎」"NOR"，將$w從肩頭甩出砸嚮往$n的$l",
        "lvl"    : 69,
        "skill_name" : "霸王扛鼎"
]),
([        "action" : "$N身子一晃，一招"RED"「八仙醉打」"NOR"，手中$w如狂風暴雨般向$n打出",
        "lvl"    : 79,
        "skill_name" : "八仙醉打"
]),
([        "action" : "$N一聲咆哮，一招"HIW"「長虹經天」"NOR", $w從手中擲出，飛向$n的$l",
        "lvl"    : 89,
        "skill_name" : "長虹經天"
]),
([      "action" : RED "$N臉上突現煞氣，舉起$w，猛向$n後腦擊落。這一杖出手又快又狠，竟是「瘋魔杖法」中的毒招"NOR,
        "lvl"    : 99,
        "skill_name" : "瘋魔杖法"
]),
});

int valid_enable(string usage)
{
        return usage == "staff" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不足，無法學習瘋魔杖法。\n");

        if ((int)me->query_skill("force") < 90)
                return notify_fail("你的內功火候太淺，無法學習瘋魔杖法。\n");

        if ((int)me->query_skill("staff", 1) < 30)
                return notify_fail("你的基本杖法太淺，無法學習瘋魔杖法。\n");

        if ((int)me->query_skill("staff", 1) < (int)(int)me->query_skill("fengmo-zhang", 1))
                return notify_fail("你的基本杖法水平有限，無法領會更高深的瘋魔杖法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -45;
        int d_e2 = -15;
        int p_e1 = 10;
        int p_e2 = 45;
        int f_e1 = 250;
        int f_e2 = 300;
        int m_e1 = 200;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("fengmo-zhang", 1);
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

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練瘋魔杖法。\n");

        if( query("neili", me)<75 )
                return notify_fail("你的內力不夠練瘋魔杖法。\n");

        me->receive_damage("qi", 70);
        addn("neili", -69, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"fengmo-zhang/" + action;
}

int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n瘋魔杖法："NOR"\n");
        write(@HELP

    瘋魔杖法為丐幫的武技。

        學習要求：
                混天氣功20級
                內力200
HELP
        );
        return 1;
}