// luoyan-hand.c 大落雁手
// Last Modified by sir 10.23.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一式"HIC"「江邊斜雁」"NOR"，以掌化爪，五指如鈎，直逼$n的膻中要穴",
        "lvl" : 0,
        "skill_name" : "江邊斜雁"
]),
([        "action" : "$N左手虛晃，一式"CYN"「雁過無痕」"NOR"，右手上下直擊，反扣$n的肩井大穴
",
        "lvl" : 10,
        "skill_name" : "雁過無痕"
]),
([        "action" : "$N使一式"BLU"「鐵雁霜翎」"NOR"，掌指齊出，拍拿並施，拿向$n的三路要害",
        "lvl" : 20,
        "skill_name" : "鐵雁霜翎"
]),
([        "action" : "$N左手鷹抓，右手蛇舉，一式"MAG"「雁過留聲」"NOR"疾扣$n的中節大脈",        
        "lvl" : 30,
        "skill_name" : "雁過留聲"
]),
([        "action" : "$N使一式"YEL"「秋飛雁舞」"NOR"，四面八方出現無數掌影，一爪突出，抓向$n
的胸口",
        "lvl" : 50,
        "skill_name" : "秋飛雁舞"
]),
([        "action" : "$N兩手環扣，全身關節啪啪作響，一式"HIM"「雁字回時」"NOR"，擊向$n的$l",
        "lvl" : 80,
        "skill_name" : "雁字回時"
]),
([        "action" : "$N一式"HIB"「斷鴻零雁」"NOR"，十指齊伸，遮天蔽日般地籠罩$n的全身要穴",
        "lvl" : 100,
        "skill_name" : "斷鴻零雁"
]),
([        "action" : "$N嶽立霆峙，一式"HIG"「雁回蘭舟」"NOR"，在一陣暴雷聲中，雙手同時拍中$n
的七道死穴",
        "lvl" : 150,
        "skill_name" : "雁回蘭舟"
])
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo) { return combo=="biluo-zhang"; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練大落雁手必須空手。\n");
        if ((int)me->query_skill("huiyan-xinfa", 1) < 20)
                return notify_fail("你的回雁心法火候不夠，無法學大落雁手。\n");
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練大落雁手。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練大落雁手。\n");
        me->receive_damage("qi", 25);
        addn("neili", -15, me);
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
        int d_e1 = -40;
        int d_e2 = -10;
        int p_e1 = 20;
        int p_e2 = 50;
        int f_e1 = 110;
        int f_e2 = 210;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("luoyan-hand", 1);
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
int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"luoyan-hand/" + action;
}

int help(object me)
{
        write(HIC"\n大落雁手："NOR"\n");
        write(@HELP

    大落雁手為衡山派絕技之一。
    可與碧羅掌互備。
    
        學習要求：
                回雁心法20級
HELP
        );
        return 1;
}
