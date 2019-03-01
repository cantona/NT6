// luohan-quan.c 羅漢拳

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N連續上步，一式"HIY"「黃鶯落架」"NOR"，左右手分靠，變拳為掌，擊向$n的
$l",
        "lvl" : 0,
        "skill_name" : "黃鶯落架"
]),
([        "action" : "$N左腳虛踏，全身右轉，一招"HIM"「丹鳳朝陽」"NOR"，右掌猛地插向$n的$l",
        "lvl" : 8,
        "skill_name" : "丹鳳朝陽"
]),
([        "action" : "$N雙手大開大闔，寬打高舉，使一招"HIB"「洛鐘東應」"NOR"，雙拳向$n的$l打
去",
        "lvl" : 15,
        "skill_name" : "洛鐘東應"
]),
([        "action" : "$N左掌圈花揚起，屈肘當胸，虎口朝上，一招"HIC"「偏花七星」"NOR"打向$n的
$l",
        "lvl" : 24,
        "skill_name" : "偏花七星"
]),
([        "action" : "$N使一招"HIM"「苦海回頭」"NOR"，上身前探，雙手劃了個半圈，擊向$n的$l",
        "lvl" : 33,
        "skill_name" : "苦海回頭"
]),
([        "action" : "$N雙掌劃弧，一記"HIY"「挾山超海」"NOR"，掌出如電，一下子切到$n的手上",
        "lvl" : 42,
        "skill_name" : "挾山超海"
]),
([        "action" : "$N施出"HIG"「懾服外道」"NOR"，雙拳拳出如風，同時打向$n頭，胸，腹三處要
害",
        "lvl" : 50,
        "skill_name" : "懾服外道"
]),
([        "action" : "$N左腳內扣，右腿曲坐，一式"BLU"「三入地獄」"NOR"，雙手齊齊按向$n的胸口
",
        "lvl" : 58,
        "skill_name" : "三入地獄"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_combine(string combo) { return combo=="fengyun-shou";}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練羅漢拳必須空手。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候不夠，無法學羅漢拳。\n");

        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練羅漢拳。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("luohan-quan", 1))
                return notify_fail("你的基本拳法水平有限，無法領會更高深的羅漢拳。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練羅漢拳。\n");
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
        int d_e1 = 30;
        int d_e2 = 50;
        int p_e1 = -30;
        int p_e2 = -10;
        int f_e1 = 110;
        int f_e2 = 260;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("luohan-quan", 1);
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
int practice_bonus() { return 20; }
int success() { return 15; }

int power_point(object me) { return 1.0; }
void skill_improved(object me)
{
        int level = (int)me->query_skill("luohan-quan", 1);

        if( !(level % 10) && level >= (int)me->query_skill("force", 1) ) {
                me->improve_skill("force", 2 * (level - 5) * (level - 5), 1);
                tell_object(me, "你在羅漢拳方面的造詣增進了你的基本內功修為。\n");
        }
}

string perform_action_file(string action)
{
        return __DIR__ "luohan-quan/" + action;
}

int help(object me)
{
        write(HIC"\n羅漢拳："NOR"\n");
        write(@HELP

    羅漢拳為少林七十二絕技之一。
    可與互備。

        學習要求：
                混元一氣功10級
                內力50
HELP
        );
        return 1;
}
