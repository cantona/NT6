// zhentian-cuff.c 震天拳法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N馬步一立，身子微曲，暗喝一聲，一招"HIW"「望月拜天」"NOR"，一拳直捅$n的$l",
        "lvl" : 0,
        "skill_name" : "望月拜天"
]),
([        "action" : "$N“哈哈”一笑，左拳由下至上，右拳平平擊出，一招"RED"「跨日向天」"NOR"，交替打向$n",
        "lvl" : 15,
        "skill_name" : "跨日向天"
]),
([        "action" : "$N對$n一聲大喝，使一招"HIC"「長虹經天」"NOR"，左拳擊出，隨即右拳跟上，兩重力道打向$n的$l",
        "lvl" : 30,
        "skill_name" : "長虹經天"
]),
([        "action" : "$N悶喝一聲，雙拳向上分開，一記"HIR"「舉火燒天」"NOR"，拳劃弧線，左右同時擊向$n的$l",
        "lvl" : 45,
        "skill_name" : "舉火燒天"
]),
([        "action" : "$N施出"YEL"「一臂擎天」"NOR"，一聲大吼，一拳凌空打出，拳風直逼$n的$l",
        "lvl" : 60,
        "skill_name" : "一臂擎天"
]),
([        "action" : "$N一聲長嘯，雙拳交錯擊出，一招"BLU"「石破天驚」"NOR"，拳風密布$n的前後左右",
        "lvl" : 70,
        "skill_name" : "石破天驚"
]),
([        "action" : "$N怒吼一聲，凌空飛起，一式"MAG"「天崩地裂」"NOR"，雙拳居高臨下，齊齊捶向$n",
        "lvl" : 80,
        "skill_name" : "天崩地裂"
]),
([        "action" : "$N仰天大笑，勢若瘋狂，衣袍飛舞，一招"HIW"「無法無天」"NOR"，拳風凌厲，如雨點般向$n打去",
        "lvl" : 90,
        "skill_name" : "無法無天"
]),
([        "action" : "$N手中招式突然加快，一招"MAG"「拳腿雙絕」"NOR"，隔空向$n擊出一拳，隨即雙腿連環踢出",
        "lvl" : 100,
        "skill_name" : "拳腿雙絕"
])
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_combine(string combo) { return combo=="chuanyun-leg"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練「震天拳」必須空手。\n");
        if ((int)me->query_skill("xuantian-wuji", 1) < 25)
                return notify_fail("你的「玄天無極功」火候不夠，無法學「震天拳」。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練「震天拳」。\n");
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的力氣不夠了。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的內力不夠練「震天拳」。\n");
        me->receive_damage("qi", 35);
        addn("qi", -20, me);
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
        int d_e1 = 25;
        int d_e2 = 45;
        int p_e1 = -35;
        int p_e2 = -15;
        int f_e1 = 140;
        int f_e2 = 290;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("zhentian-cuff", 1);
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
int learn_bonus() { return 20; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) {
        if( query("gender", me) == "男性" )
        return 1.2;
        else
         return 0.8; 
}

int help(object me)
{
        write(HIC"\n震天拳法："NOR"\n");
        write(@HELP

    震天拳法為昆侖派側重男弟子的武技。

        學習要求：
                玄天無極功25級
                內力50
HELP
        );
        return 1;
}
