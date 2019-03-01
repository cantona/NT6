// Last Modified by winder on May. 29 2001
// xiangmo-whip 降魔鞭

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action": "$N躍起三丈，身在半空，招式陡變，$w如驚濤駭浪，向$n電擎而落",
        "lvl" : 0,
        "skill_name" : "驚濤拍岸",
]),
([        "action": "$N鞭式一變，手中的$w宛如一條怪蟒，上下翻騰的襲向$n的$l",
        "lvl" : 20,
        "skill_name" : "萬裡騰雲",
]),
([        "action": "$N手中$w前後舞動，一招「靈鷲展翅」，鞭鞭皆打向$n的$l！",
        "lvl" : 60,
        "skill_name" : "靈鷲展翅",
]),
([        "action": "$N手中$w掄動，鞭風洶湧，去式似遊龍，或橫掃直擊，或盤旋翻卷，傾刻間已將$n全身裹住",
        "lvl" : 90,
        "skill_name" : "漫天飛雪",
]),
([        "action": "$N手中$w圈圈點點，鞭式連綿，忽地使出一招「降魔式」，$w上風聲大作，漫天鞭影從四面八方向$n周身要害擊到",
        "lvl" : 120,
        "skill_name" : "降魔式",
]),
});

int valid_enable(string usage) { return (usage=="whip") || (usage=="parry"); }
int valid_learn(object me)
{
        object weapon;

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("zhanzhuang-gong", 1) < 50)
                return notify_fail("你的站樁功火候太淺。\n");
        if ((int)me->query_skill("jiujie-whip",1) < 20)
                return notify_fail("你的九節鞭修為不足，沒有辦法練降魔鞭。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<30 || query("neili", me)<30 )
                return notify_fail("你的體力不夠練九節鞭法。\n");
        me->receive_damage("qi", 25);
        addn("neili", -25, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        int d_e1 = -50;
        int d_e2 = -40;
        int p_e1 = 0;
        int p_e2 = 10;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 250;
        int m_e2 = 400;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("xiangmo-whip", 1);
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
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "淤傷" : "刺傷",
        ]);
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point() { return 1.0; }
 
int help(object me)
{
        write(HIC"\n降魔鞭："NOR"\n");
        write(@HELP

    降魔鞭是南少林高級鞭法。

        學習要求：
                站樁功50級
                九節鞭20級
                內力修為500
HELP
        );
        return 1;
}
