// xunlei-sword.c
// Last Modified by sir 10.22.2001

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N劍尖向右，繞身一周，一式"HIC"「仙人指路」"NOR"，$w突然向$n的$l刺去，",
        "lvl" : 0,
        "skill_name"  : "仙人指路"
]),
([        "action" : "$N使出一式"BLU"「鷂子翻身」"NOR"，身體凌空側翻，一劍從身下刺出",
        "lvl" : 5,
        "skill_name"  : "鷂子翻身"
]),
([        "action" : "$N左手劍指血指，右手$w使出一招"MAG"「海底尋針」"NOR"，由上至下猛向$n的$l劈刺",
        "lvl" : 10,
        "skill_name"  : "海底尋針"
]),
([        "action" : "$N撤步縮身，$w按藏于臂下，一招"GRN"「靈猿探洞」"NOR"，快如閃電般刺向$n的$l",
        "lvl" : 15,
        "skill_name"  :"靈猿探洞"
]),
([        "action" : "$N踏步向前，一式"HIG"「撥草尋蛇」"NOR"，手中長劍擺動，劍尖刺向$n的$l",
        "lvl" : 20,
        "skill_name"  : "撥草尋蛇"
]),
([        "action" : "$N一招"HIY"「斜插神枝」"NOR"，身體背轉，手中$w由右肩上方反手向下刺出",
        "lvl" : 25,
        "skill_name"  : "斜插神枝"
]),
([        "action" : "$N一式"HIC"「電閃雷動」"NOR"，劍走中鋒，氣勢威嚴，將$n籠罩于重重劍氣之中",
        "lvl" : 30,
        "skill_name"  : "電閃雷動"
]),
([        "action" : "$N向前彎身，一招"RED"「夫子揖手」"NOR"，$w忽然從身下刺出，快如流星閃電",
        "lvl" : 35,
        "skill_name"  : "夫子揖手"
]),
([        "action" : "$N橫握$w，左右晃動，一招"HIW"「玉帶纏腰」"NOR"，劍氣直逼$n的腰部要害",
        "lvl" : 45,
        "skill_name"  : "玉帶纏腰"
]),
([        "action" : "$N雙手持劍，將$w當做刀使，一招"HIR"「舉火燒天」"NOR"，由身後向$n的前上方劈去",
        "lvl" : 55,
        "skill_name"  : "舉火燒天"
]),
([        "action" : "$N側身向$n，使出一招"HIB"「敗馬斬蹄」"NOR"，揮動手中$w，直劈$n的下三路",
        "lvl" : 65,
        "skill_name"  : "敗馬斬蹄"
]),
([        "action" : "$N手中$w由右自左，一招"HIC"「玉女穿針」"NOR"，$w突然反手刺向$n的$l",
        "lvl" : 75,
        "skill_name"  : "玉女穿針"
]),
([        "action" : "$N跳步向前，劍尖上指，一招"HIG"「靈猿登枝」"NOR"，$w挑向$n的頭部要害",
        "lvl" : 85,
        "skill_name"  : "靈猿登枝"
]),
([        "action" : "$N一招"BLU"「蘇武揮鞭」"NOR"，$w隨身走，猶如一條白龍，將$n全身上下籠罩",
        "lvl" : 95,
        "skill_name"  : "蘇武揮鞭"
]),
([        "action" : "$N劍尖向下，一招"RED"「挑燈看劍」"NOR"，$w忽然急轉直上，劍氣將$n的上身要害團團圍住",
        "lvl" : 100,
        "skill_name"  : "挑燈看劍"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("xuantian-wuji", 1) < 10)
                return notify_fail("你的玄天無極功火候太淺。\n");
        if ((int)me->query_skill("sword", 1) < 10)
                return notify_fail("你的基本劍法火候太淺。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 || query("neili", me)<35 )
                return notify_fail("你的內力或氣不夠練迅雷十六劍。\n");
        me->receive_damage("qi", 45);
        addn("neili", -30, me);
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
        int d_e1 = -10;
        int d_e2 = 10;
        int p_e1 = -40;
        int p_e2 = -20;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 160;
        int m_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("xunlei-sword", 1);
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
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"xunlei-sword/" + action;
}

int help(object me)
{
        write(HIC"\n迅雷十六劍："NOR"\n");
        write(@HELP

    迅雷十六劍是昆侖派的劍法。

        學習要求：
                玄天無極功10級
                基本劍法10級
                內力100
HELP
        );
        return 1;
}
