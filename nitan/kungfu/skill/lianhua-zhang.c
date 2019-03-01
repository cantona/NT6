// lianhua-zhang.c 蓮花掌
// Last Modified by qingyun 2005.1.9

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N使出蓮花掌起手勢「小蓮初綻」，左掌護胸，右掌緩緩拍向$n的$l",
        "lvl" : 0,
        "skill_name" : "小蓮初綻"
]),
([        "action" : "$N後退一步，右手護胸，左手一記「千葉蓮花」劈出一道掌風，直奔$n的$l",
        "lvl" : 20,
        "skill_name" : "千葉蓮花"
]),
([        "action" : "$N一式「雨打蓮花」飛身躍起直撲$n，雙掌幻化出數十個掌影，快如雨點擊向$n",
        "lvl" : 40,
        "skill_name" : "雨打蓮花"
]),
([        "action" : "$N面露微笑，一招「葉底清荷」左掌一擺，右掌劃出一道美妙的弧線，直切$n的$l",
        "lvl" : 80,
        "skill_name" : "葉底清荷"
]),
([        "action" : "$N使出「雙蓮爭艷」，雙掌飛快舞動，將$n圈在掌風之內，在眼花繚亂間驟然拍出",
        "lvl" : 100,
        "skill_name" : "雙蓮爭艷"
]),
([        "action" : "$N雙手微張緩緩前探，雙臂伸直後突然變化為掌，一式「蓮池泛舟」擺向$n的$l",
        "lvl" : 120,
        "skill_name" : "蓮池泛舟"
]),
([        "action" : "$N繞著$n快速遊走，使出「遍野荷香」手掌如穿花蝴蝶般上下飛舞，罩向$n的$l",
        "lvl" : 140,
        "skill_name" : "遍野荷香"
]),
([        "action" : "剎那間$N反身錯步，突然使出一招「雨後清蓮」，猛一掌便向$n的$l劈去",
        "lvl" : 160,
        "skill_name" : "雨後清蓮"
]),
([        "action" : "$N右掌護胸，左掌在面前一晃，突地從腋下穿出，一式「舊藕新蓮」直拍$n$l",
        "lvl" : 180,
        "skill_name" : "舊藕新蓮"
]),
([        "action" : "只見$N使一招「藕斷絲連」，左掌晃動著平舉，右掌搖擺不定中畫個圓圈拍向$n",
        "lvl" : 200,
        "skill_name" : "藕斷絲連"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }        
int valid_combine(string combo) { return combo=="suohou-hand"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練蓮花掌必須空手。\n");
        if ((int)me->query_skill("huntian-qigong", 1) < 20)
                return notify_fail("你的混天氣功火候不夠，無法學蓮花掌。\n");
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練蓮花掌。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練蓮花掌。\n");
        me->receive_damage("qi", 30);
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
        int d_e1 = -25;
        int d_e2 = -5;
        int p_e1 = 15;
        int p_e2 = 45;
        int f_e1 = 210;
        int f_e2 = 310;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("lianhua-zhang", 1);
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
int power_point() { return 1.0; }

int help(object me)
{
        write(HIC"\n蓮花掌："NOR"\n");
        write(@HELP

    蓮花掌為洪七公絕技之一。
    可與鎖喉擒拿手互備。

        學習要求：
                混天氣功20級
                內力100
HELP
        );
        return 1;
}
