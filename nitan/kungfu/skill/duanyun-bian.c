// duanyun-bian.c 斷雲鞭法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N中規中距，一招"HIR"「聚火」"NOR"，手中$w輕輕顫動，一點鞭尖點向$n的$l",
        "lvl" :        0,
        "skill_name" : "聚火",
]),
([        "action" : "$N向前跨上一步，左手迴環，右手$w使出一式"HIW"「起光」"NOR"自斜下掃向$n的$l",
        "lvl" :        15,
        "skill_name" : "起光",
]),
([        "action" : "$N身形一挫，鞭交左手，右手劈空一掌，$w隨即向上揮出，使出"HIG"「招雨」"NOR"抽向$n的$l",
        "lvl" :        30,
        "skill_name" : "招雨",
]),
([        "action" : "$N身形一展，右手$w使出一式"HIC"「動雷」"NOR"，由上而下疾劈$n的$l",
        "lvl" :        45,
        "skill_name" : "動雷",
]),
([        "action" : "$N一招"HIM"「移電」"NOR"，$w自左上而右下劃出一個大弧，平平地向$n的$l揮去",
        "lvl" :        60,
        "skill_name" : "移電",
]),
([        "action" : "$N上身往左側一擰，一招"HIM"「剪虹」"NOR"，右手$w反手抖動，向$n的$l鉸去",
        "lvl" :        75,
        "skill_name" : "剪虹",
]),
([        "action" : "$N左腿提膝，手中$w斜指，一招"HIC"「止風」"NOR"橫向$n的$l",
        "lvl" :        90,
        "skill_name" : "止風",
]),
([        "action" : "$N猛的加速，$w時快時慢，當$n準備擋時，$w一招"HIW"「斷雲」"NOR"，橫掃$n的$l",
        "lvl" :        105,
        "skill_name" : "斷雲",
]),
([        "action" : "$N輕輕躍起，一招"HIB"「遮月」"NOR"，$w在半空中化為一圈銀芒，落向$n的$l",
        "lvl" :        110,
        "skill_name" : "遮月",
]),
([        "action" : "$N使出"HIY"「掩日」"NOR"，$w劃出無數個圓圈，鞭緣直出，貫注內力，綿綿不斷划向$n的$l",
        "lvl" :        120,
        "skill_name" : "掩日",
])
});

int valid_enable(string usage) { return (usage=="whip") || (usage=="parry"); }

int valid_learn(object me)
{
        object weapon;

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不足，沒有辦法練斷雲鞭法。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
                query("skill_type", weapon) != "whip" )
                return notify_fail("你必須先找一條鞭子才能練鞭法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");
        if( query("jing", me)<50 )
                return notify_fail("你的精氣不夠練斷雲鞭法。\n");
           if( query("neili", me)<50 )
                   return notify_fail("你的內力不夠練斷雲鞭法。\n");
        me->receive_damage("jing", 10 );
        addn("neili", -20, me);

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
        int d_e1 = -55;
        int d_e2 = -45;
        int p_e1 = -20;
        int p_e2 = 0;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 350;
        int m_e2 = 500;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("duanyun-bian", 1);
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
                "damage_type" : random(2) ? "瘀傷" : "刺傷",
        ]);
}
int learn_bonus() { return 10; }
int practice_bonus() { return 15; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        if ( this_player()->query_skill("duanyun-bian", 1) >= 50 )
                return __DIR__"duanyun-bian/" + action;
}

int help(object me)
{
        write(HIC"\n斷雲鞭法："NOR"\n");
        write(@HELP

    斷雲鞭法為全真掌教馬鈺的獨門武功。

        學習要求：
                先天氣功40級
                內力200
HELP
        );
        return 1;
}
