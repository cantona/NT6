// zhemei-shou.c 天山折梅手

#include <ansi.h>;

inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一招"GRN"「吹梅笛怨」"NOR"，雙手橫揮，抓向$n",
        "lvl" : 0,
        "skill_name" : "吹梅笛怨"
]),
([        "action" : "$N一招"YEL"「黃昏獨自愁」"NOR"，身子躍然而起，抓向$n的頭部",
        "lvl" : 10,
        "skill_name" : "黃昏獨自愁"
]),
([        "action" : "$N一招"CYN"「寒山一帶傷心碧」"NOR"，雙手紛飛，$n只覺眼花繚亂",
        "lvl" : 30,
        "skill_name" : "寒山一帶傷心碧"
]),
([        "action" : "$N一招"MAG"「梅花雪落覆白蘋」"NOR"，雙手合擊，$n只覺無處可避",
        "lvl" : 40,
        "skill_name" : "梅花雪落覆白蘋"
]),
([        "action" : "$N一招"HIW"「砌下落梅如雪亂」"NOR"，雙手飄然抓向$n",
        "lvl" : 50,
        "skill_name" : "砌下落梅如雪亂"
]),

([        "action" : "$N雙手平舉，一招"GRN"「雲破月來花弄影」"NOR"擊向$n",
        "lvl" : 60,
        "skill_name" : "雲破月來花弄影"
]),
([        "action" : "$N一招"HIB"「花開堪折直須折」"NOR"，拿向$n，似乎$n的全身都被籠罩",
        "lvl" : 70,
        "skill_name" : "花開堪折直須折"
]),

([        "action" : "$N左手虛晃，右手一記"HIR"「紅顏未老恩先絕」"NOR"擊向$n的頭部",
        "lvl" : 80,
        "skill_name" : "紅顏未老恩先絕"
]),
([        "action" : "$N施出"HIM"「虛妄笑紅」"NOR"，右手橫掃$n的$l，左手攻向$n的胸口",
        "lvl" : 90,
        "skill_name" : "虛妄笑紅"
]),
([        "action" : "$N施出"HIR"「玉石俱焚」"NOR"，不顧一切撲向$n",
        "lvl" : 100,
        "skill_name" : "玉石俱焚"
])
});

int valid_enable(string usage) { return usage=="parry" || usage=="hand"; }
int valid_combine(string combo) { return combo=="liuyang-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練逍遙折梅手必須空手。\n");

        if( query("max_neili", me)<900 )
                return notify_fail("你的內力太弱，無法練逍遙折梅手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，無法練逍遙折梅手。\n");

        if ((int)me->query_skill("hand", 1) < 100)
                return notify_fail("你的基本手法火候不夠，無法練逍遙折梅手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("zhemei-shou", 1))
                return notify_fail("你的基本手法水平有限，無法領會更高深的逍遙折梅手。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練天山折梅手。\n");
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
        int d_e1 = -60;
        int d_e2 = -30;
        int p_e1 = 0;
        int p_e2 = 35;
        int f_e1 = 120;
        int f_e2 = 220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("zhemei-shou", 1);
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
mixed hit_ob(object me, object victim, int damage_bonus)
{
        if( query("jiali", me) <= 10) return 0;
        //if( me->query_family() != "xiaoyao") return 0;
        if( damage_bonus < 100 ) return 0;

        if( random(damage_bonus) > victim->query_str()/10 )
        {
                victim->receive_wound("qi", damage_bonus / 3, me);
                return HIC "你聽到一聲脆響，彷彿是梅枝折斷的聲音！\n" NOR;
        }
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"zhemei-shou/" + action;
}
int help(object me)
{
        write(HIC"\n天山折梅手："NOR"\n");
        write(@HELP

    天山折梅手是逍遙派手法。
    可與天山六陽掌互備。

        學習要求：
                北冥神功15級或八荒六合唯我獨尊功15級
                內力50
HELP
        );
        return 1;
}
