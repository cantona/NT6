// This program is a part of NITAN MudLIB
// liuhe-dao.c 丐幫六合刀法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action":"$N大喝一聲，手中$w大開大闔，連連揮刀使出「呵壁問天」，斬向$n的$l",
        "attack": 55,
        "dodge" : 56,
        "parry" : 54,
        "damage": 120,
        "lvl" : 0,
        "skill_name" : "呵壁問天",
        "damage_type":  "割傷"
]),
([      "action":"$N運刀如風，一招「氣蓋河山」，刀勢霸道之極，向着$n周身各處猛砍猛劈",
        "attack": 60,
        "dodge" : 60,
        "parry" : 65,
        "damage": 130,
        "lvl" : 10,
        "skill_name" : "氣蓋河山",
        "damage_type":  "割傷"
]),
([      "action":"$N一着「天地乍合」，突然搶進$n近側，迅猛地驅刀連斬，攻式頓然合成一個圓圈",
        "attack": 60,
        "dodge" : 60,
        "parry" : 55,
        "damage": 140,
        "lvl" : 25,
        "skill_name" : "天地乍合",
        "damage_type":  "割傷"
]),
([      "action":"$N仰天悲笑，隨即揮刀斬出一式「離合無常」，$w化為一絲絲寒意，裹向$n$l",
        "attack": 70,
        "dodge" : 65,
        "parry" : 70,
        "damage": 140,
        "lvl" : 35,
        "skill_name" : "離合無常",
        "damage_type":  "割傷"
]),
([      "action":"$N施展「和合六出」繞着$n飛旋，$w帶着狂野刀風，凌歷無比地劈出六刀",
        "attack": 63,
        "dodge" : 60,
        "parry" : 70,
        "damage": 145,
        "lvl" : 45,
        "skill_name" : "和合六出",
        "damage_type":  "割傷"
]),
([      "action":"$N臉色莊重，揮刀使出「陰陽隔閡」，$w由上而下向$n連劈，猶似一個個焦雷轟頂",
        "attack": 70,
        "dodge" : 70,
        "parry" : 75,
        "damage": 145,
        "lvl" : 60,
        "skill_name" : "陰陽隔閡",
        "damage_type":  "割傷"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("huntian-qigong", 1) < 20)
                return notify_fail("你的混天氣功火候太淺。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 55;
        int d_e2 = 35;
        int p_e1 = 5;
        int p_e2 = -15;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 50;
        int m_e2 = 160;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("liuhe-dao", 1);
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
                "damage_type" : "割傷",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練六合刀法。\n");
        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練六合刀法。\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liuhe-dao/" + action;
}

int learn_bonus() { return 20; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1; }

int help(object me)
{
        write(HIC"\n六合刀法："NOR"\n");
        write(@HELP

    四象六合刀為丐幫的刀法。

        學習要求：
                混天氣功30級
                內力50
HELP
        );
        return 1;
}