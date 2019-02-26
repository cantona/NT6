// yingxiong-sanzhao.c 英雄三招
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$n抓住$N的後頸，一把提起。$N左手慢慢反轉，在$n左腋底搔了一把，\n$n身子軟了下來，$N左手拿住$n腋下，右手慢慢迴轉，抓住$n領口，緩緩\n舉起$n的身子，過了自己頭頂，向外摔出",
        "lvl" : 0,
        "skill_name" : "子胥舉鼎",
]),
([        "action" : "$N俯伏地上，$n伸右足踏住$N的後腰，$N雙腿一縮，似欲跪拜，\n右臂卻慢慢橫掠而出，突然間一個筋斗，向$n的胯下鑽去，只一作勢\n左手已抓住$n右腳足踝，右手向$n小腹擊去",
        "lvl" : 10,
        "skill_name" : "魯達拔柳",
]),
([        "action" : "$N雙臂反在背後，突然雙手十指彎起，各成半球之形，身子向後一撞\n十指便抓向$n的胸部，$n向後一縮，$N突然一個倒翻筋斗，身子躍起\n雙腿一分，已跨在$n肩頭，同時雙手按指壓住$n太陽穴，食指按眉，中指按眼",
        "lvl" : 20,
        "skill_name" : "狄青降龍",
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="shenlong-bashi"; }
int valid_learn(object me)
{
        if (me->query_int() < 35)
                return notify_fail("你的悟性不夠，無法學英雄三招。\n");
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法學英雄三招。\n");

        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
int practice_skill(object me)
{
        if( query("qi", me)<55 )
                return notify_fail("你的力氣太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練英雄三招。\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
        return 1;
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 25;
        int d_e2 = 45;
        int p_e1 = -35;
        int p_e2 = -15;
        int f_e1 = 490;
        int f_e2 = 590;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("yingxiong-sanzhao",1);
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
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"yingxiong-sanzhao/" + action;
}

int help(object me)
{
        write(HIC"\n英雄三招"NOR"\n");
        write(@HELP

    英雄三招是神龍島指法，取自三個英雄名。可與神龍八式互備。

        學習要求：
                毒龍大法60級
                內力修為100
                後天悟性35
HELP
        );
        return 1;
}
