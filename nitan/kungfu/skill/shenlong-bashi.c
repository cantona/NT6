// shenlong-bashi 神龍八式

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N使一招"GRN"「疏影橫斜」"NOR"，左手輕輕一抹，向$n的$l拍去",
        "lvl"    : 0,
        "skill_name" : "疏影橫斜"
]),
([        "action" : "$N鼓氣大喝，雙掌使一招"HIY"「五丁開山」"NOR"，推向$n的$l",
        "lvl"    : 10,
        "skill_name" : "五丁開山"
]),
([        "action" : "$N順勢使一招"GRN"「風行草偃」"NOR"，移肩轉身，左掌護面，右掌直擊$n",
        "lvl"    : 20,
        "skill_name" : "風行草偃"
]),
([        "action" : "$N退後幾步，突然反手一掌，一招"RED"「神龍擺尾」"NOR"，無比怪異地擊向$n",
        "lvl"    : 30,
        "skill_name" : "神龍擺尾"
]),
([        "action" : "$N使一式"CYN"「風捲殘雲」"NOR"，全身飛速旋轉，雙掌一前一後，猛地拍向$n的胸口",
        "lvl"    : 40,
        "skill_name" : "風捲殘雲"
]),
([        "action" : "$N忽的使出"HIW"「乾坤倒旋」"NOR"，以手支地，雙腿翻飛踢向$n",
        "lvl"    : 50,
        "skill_name" : "乾坤倒旋"
]),
([        "action" : "$N大吼一聲，使出"BLU"「同歸於盡」"NOR"，不顧一切般撲向$n",
        "lvl"    : 60,
        "skill_name" : "同歸於盡"
]),
([        "action" : "$N深吸一口氣，使出"HIW"「流星趕月」"NOR"身體漲成球狀，猛然流星趕月般直撞向$n",
        "lvl"    : 70,
        "skill_name" : "流星趕月"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo) { return combo=="huagu-mianzhang" || combo=="yingxiong-sanzhao";}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練神龍八式必須空手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，無法學神龍八式.\n");

        if( query("max_neili", me)<750 )
                return notify_fail("你的內力太弱，無法練神龍八式。\n");

        if ((int)me->query_skill("hand", 1) < 80)
                return notify_fail("你的基本手法火候不夠，無法學習神龍八式。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("shenlong-bashi", 1))
                return notify_fail("你的基本手法水平有限，無法學習更高深的神龍八式。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練神龍八式。\n");
        me->receive_damage("qi", 40);
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
        int d_e1 = -55;
        int d_e2 = -25;
        int p_e1 = 5;
        int p_e2 = 35;
        int f_e1 = 200;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("shenlong-bashi", 1);
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
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"shenlong-bashi/" + action;
}

int help(object me)
{
        write(HIC"\n神龍八式："NOR"\n");
        write(@HELP

    神龍八式為神龍教武功。可與英雄三招互備。

        學習要求：
                基本內功25級
                毒龍大法25級
                內力150
HELP
        );
        return 1;
}
