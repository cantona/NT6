// jingang-quan.c -大金剛拳
// 少林的招牌空手功夫，不能差了

#include <ansi.h>;
inherit SHAOLIN_SKILL;

string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N盤膝而坐，二手合十，一式"HIC"「蓮花座」"NOR"，雙拳蓄勢而發，擊向$n的$l",
        "lvl" : 0,
        "skill_name" : "蓮花座"
]),
([      "action" : "$N一式"HIR"「烈火錐」"NOR"，雙掌輪流下擊，拳勢如燄，□啪爆響",
        "lvl" : 10,
        "skill_name" : "烈火錐"
]),
([      "action" : "$N騰空飛起，一式"HIG"「八方雨」"NOR"，雙手雙腿齊出，令$n無可躲藏",
        "lvl" : 20,
        "skill_name" : "八方雨"
]),
([      "action" : "$N雙掌虛含，掌緣下沉，一式"HIM"「掌心雷」"NOR"，緩緩向$n推出",
        "lvl" : 30,
        "skill_name" : "掌心雷"
]),
([      "action" : "$N一臂前伸，一臂後指，一式"HIB"「五指山」"NOR"，攻向$n的身前身後",
        "lvl" : 40,
        "skill_name" : "五指山"
]),
([      "action" : "$N一式"HIW"「觀音渡」"NOR"，兩手十指虛點$n的全身三十六道要穴",
        "lvl" : 48,
        "skill_name" : "觀音渡"
]),
([      "action" : "$N兩目內視，雙手內籠，一式"HIY"「天龍唱」"NOR"，四面八方響起震人心魄的
龍吟",
        "lvl" : 54,
        "skill_name" : "天龍唱"
]),
([      "action" : "$N似笑非笑，雙拳無形無定，一式「如來笑」，驟然擊向$n的前胸",
        "lvl" : 60,
        "skill_name" : "如來笑"
])
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練大金剛拳必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學大金剛拳。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練大金剛拳。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("jingang-quan", 1))
                return notify_fail("你的基本拳法水平有限，無法領會更高深的大金剛拳。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練大金剛拳。\n");
        me->receive_damage("qi", 30);
        addn("neili", -20, me);
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
        int d_e1 = 15;
        int d_e2 = 40;
        int p_e1 = -40;
        int p_e2 = -15;
        int f_e1 = 200;
        int f_e2 = 450;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jingang-quan", 1);
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

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"jingang-quan/" + action;
}

void skill_improved(object me)
{
        if( me->query_skill("jingang-quan",1) == 150 && !query("sl_gift/str", me) )
        {
                addn("str", 1, me);
                set("sl_gift/str", 1, me);
                tell_object(me, "你的大金剛拳學有所成，提高了你的臂力。\n");
        }
}

int help(object me)
{
        write(HIC"\n大金剛拳："NOR"\n");
        write(@HELP

    大金剛拳為少林七十二絕技之一。
    大金剛拳以天資所限，大多少林和尚均無法練成。少林派往往
要隔上百余年，才有一個特出的奇才能練成這門拳法。只是練功的
訣竅等等，上代高僧詳記在武經之中，有時全寺數百僧眾竟無一人
練成，卻也不致失傳。

        學習要求：
                混元一氣功50級
                內力200
HELP
        );
        return 1;
}
