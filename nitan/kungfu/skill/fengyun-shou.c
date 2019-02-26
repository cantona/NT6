// This program is a part of NT MudLIB
// fengyun-hand.c 風雲手 和羅漢拳互備

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一式"HIC"「風滿長空」"NOR"，以掌化爪，五指如鈎，直逼$n的膻中要穴",
        "lvl" : 0,
        "skill_name" : "風滿長空"
]),
([        "action" : "$N左手虛晃，一式"HIR"「烈火騰雲」"NOR"，右手上下直擊，反扣$n的肩井大穴
",
        "lvl" : 8,
        "skill_name" : "烈火騰雲"
]),
([        "action" : "$N使一式"HIG"「草深霧澤」"NOR"，掌指齊出，拍拿並施，拿向$n的三路要害",
        "lvl" : 16,
        "skill_name" : "草深霧澤"
]),
([        "action" : "$N左手鷹抓，右手蛇舉，一式"HIW"「天目昭輝」"NOR"疾扣$n的中節大脈",
        "lvl" : 24,
        "skill_name" : "天目昭輝"
]),
([        "action" : "$N使一式"HIM"「雷震四方」"NOR"，四面八方出現無數掌影，一爪突出，抓向$n的胸口",
        "lvl" : 40,
        "skill_name" : "雷震四方"
]),
([        "action" : "$N兩手環扣，全身關節啪啪作響，一式"HIC"「水到渠成」"NOR"，擊向$n的$l",
        "lvl" : 48,
        "skill_name" : "水到渠成"
]),
([        "action" : "$N一式"HIB"「山高林密」"NOR"，十指齊伸，遮天蔽日般地籠罩$n的全身要穴",
        "lvl" : 54,
        "skill_name" : "山高林密"
]),
([        "action" : "$N嶽立霆峙，一式"HIY"「地老天荒」"NOR"，在一陣暴雷聲中，雙手同時拍中$n的七道死穴",
        "lvl" : 60,
        "skill_name" : "地老天荒"
])
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo) { return combo=="yingzhua-gong" || combo == "luohan-quan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練風雲手必須空手。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的內功火候不夠，無法學風雲手。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力太弱，無法練風雲手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("fengyun-shou", 1))
                return notify_fail("你的基本手法水平有限，無法領會更高深的風雲手。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練風雲手。\n");
        me->receive_damage("qi", 20);
        addn("neili", -10, me);
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
        int d_e1 = -35;
        int d_e2 = 0;
        int p_e1 = 30;
        int p_e2 = 55;
        int f_e1 = 70;
        int f_e2 = 170;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("fengyun-shou", 1);
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
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n風雲手："NOR"\n");
        write(@HELP

    風雲手為少林七十二絕技之一。
    可與鷹爪功互備。

        學習要求：
                混元一氣功20級
HELP
        );
        return 1;
}
