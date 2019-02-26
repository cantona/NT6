// Last Modified by winder on May. 29 2001
// one-finger.c 一指禪 不可互備 取自佛教《大般若經》。

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N雙指併攏，一式"MAG"「道行般若」"NOR"，和身緩緩而上，左右手一前一後彈向$n$l",
        "lvl"   : 0,
        "skill_name" : "道行般若"
]),
([        "action" : "$N左掌護胸，含笑一式"GRN"「小品般若」"NOR"，右手中指前後劃了個半弧，輕輕一甩，點向$n$l",
        "lvl"   : 20,
        "skill_name" : "小品般若"
]),
([        "action" : "$N身形閃動，一式"HIW"「光贊般若」"NOR"，雙手食指端部各射出一道青光，射向$n的全身要穴",
        "lvl"   : 40,
        "skill_name" : "光贊般若"
]),
([        "action" : "$N盤膝跌坐，一式"HIC"「放光般若」"NOR"，全身罡氣密佈，左手握拳託肘，右手拇指直立，遙遙對着$n一捺",
        "lvl"   : 60,
        "skill_name" : "放光般若"
]),
([        "action" : "$N面露寶相，結蘭花手，輕輕一下點出"GRN"「摩訶般若」"NOR"，憑空凝氣成線，緩緩刺向$n",
        "lvl"   : 100,
        "skill_name" : "摩訶般若"
]),
([        "action" : "$N口唸佛經，內息激發，衣衫漸漸脹鼓，身若金剛，便立指一式"HIY"「金剛般若」"NOR"，對着$n點去",
        "lvl"   : 150,
        "skill_name" : "金剛般若"
])
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練一指禪必須空手。\n");
        if ((int)me->query_skill("zhanzhuang-gong", 1) < 100)
                return notify_fail("你的站樁功火候不夠，無法學一指禪。\n");
        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力太弱，無法練習一指禪。\n");
        if ((me->query_skill("nianhua-finger", 1) < 50) ||
                (me->query_skill("boruo-strike", 1) < 50) )
                return notify_fail("你的拈花指和般若掌火候不夠，無法學一指禪。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<30 )
                return notify_fail("你的內力不夠練一指禪。\n");
        me->receive_damage("qi", 55);
        addn("neili", -25, me);
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
        int f_e1 = 330;
        int f_e2 = 430;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("one-finger", 1);
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
                "damage_type" : random(2) ? "刺傷" : "瘀傷",
        ]);
}
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"one-finger/" + action;
}

int help(object me)
{
        write(HIC"\n一指禪："NOR"\n");
        write(@HELP

    一指禪是南少林高級指法，出自佛教《大般若經》。

        學習要求：
                站樁功100級
                拈花指50級
                般若掌50級
                內力修為1200
HELP
        );
        return 1;
}
