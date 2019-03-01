// houquan.c 猴拳
// Last Modified by sega on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "\$N單腿微曲，忽的向前撲出，一式"HIM"「仙猴摘桃」"NOR"，二爪直出，抓向$n的雙眼",
        "lvl" : 0,
        "skill_name" : "橫空出世"
]),
([        "action" : "$N左手虛晃，一式"GRN"「靈猴攀枝」"NOR"，右手直擊，反扣$n的肩井大穴",
        "lvl" : 8,
        "skill_name" : "靈猴攀枝"
]),
([        "action" : "$N一臂前伸，一臂後指，一式"HIW"「猿臂輕舒」"NOR"，攻向$n的兩肋",
        "lvl" : 15,
        "skill_name" : "猿臂輕舒"
]),
([        "action" : "\n$N忽然縮成一團，使一式"CYN"「八方幻影」"NOR"，雙掌無形無定，一爪抓向$n的胸口",
        "lvl" : 15,
        "skill_name" : "八方幻影"
]),
([        "action" : "$N猛吸一口氣，一彎腰，使一式"HIB"「水中攬月」"NOR"，雙爪疾扣向$n的小腹",
        "lvl" : 20,
        "skill_name" : "水中攬月"
]),
([        "action" : "$N猛的向上高高躍起，一式"HIY"「落地摘星」"NOR"，居高臨下，一爪罩向$n的頭骨",
        "lvl" : 30,
        "skill_name" : "落地摘星"
]),
});

//int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry"|| usage=="hand"; }
int valid_enable(string usage)
{
        return usage=="unarmed" || usage=="parry" || usage=="cuff";
}
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練猴拳必須空手。\n");

        if ((int)me->query_skill("force", 1) < 30)
                return notify_fail("你的基本內功火候不夠，無法學猴拳。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力太弱，無法練猴拳。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<15 )
                return notify_fail("你的內力不夠練猴拳。\n");
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
        int d_e1 = 35;
        int d_e2 = 55;
        int p_e1 = -25;
        int p_e2 = -5;
        int f_e1 = 80;
        int f_e2 = 230;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("houquan", 1);
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
                "damage_type" : "瘀傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"houquan/" + action;
}
int help(object me)
{
        write(HIC"\n猴拳："NOR"\n");
        write(@HELP

    武林前輩模仿猿猴撲擊動作而創出的一套拳法，以輕靈翔動為
其主要特點。
    猴拳為天地會雲龍門武功。

        學習要求：
                雲龍神功10級
                基本內功30級
                內力200
HELP
        );
        return 1;
}
