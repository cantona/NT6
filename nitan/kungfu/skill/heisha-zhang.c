// heisha-zhang.c 黑砂掌
// Last Modified by winder on Aug. 25 2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一式"HIB"「無常抖索」"NOR"，雙手陡地一揮，已到$n的$l邊上",
        "lvl"    : 0,
        "skill_name"  : "無常抖索"
]),
([        "action" : "$N身形一轉，一式"BLU"「小鬼扶腰」"NOR"，左掌斜側，右掌虛託，封向$n的腰部",
        "lvl"    : 20,
        "skill_name"  : "小鬼扶腰"
]),
([        "action" : "$N使一式"HIB"「夜叉破浪」"NOR"，身形前衝，雙掌向前帶着風聲，盡力拍出，直取$n的$l",
        "lvl"    : 40,
        "skill_name"  : "夜叉破浪"
]),
([        "action" : "$N一式"BLU"「酆都衝沙」"NOR"，左右兩掌往$n周身不絕連拍，虛實不定",
        "lvl"    : 60,
        "skill_name"  : "酆都衝沙"
]),
([        "action" : "$N左掌作勢側過，右掌順勢拍下，一式"BLU"「油錘灌頂」"NOR"，猛劈$n的頭部",
        "lvl"    : 80,
        "skill_name"  : "油錘灌頂"
]),
([        "action" : "$N突然身形一頓，掌為腿先，掌腿相扣，正是"HIB"「沸鼎熬渣」"NOR"",
        "lvl"    : 100,
        "skill_name"  : "沸鼎熬渣"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry" ; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練黑砂掌必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法練習黑砂掌。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力太弱，無法練習黑砂掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("heisha-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的黑砂掌。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練黑砂掌。\n");
        me->receive_damage("qi", 25);
        addn("neili", -10, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("heisha-zhang", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
           victim->affect_by("sha_poison",
                ([ "level" : flvl + random(flvl),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 20) ])))
        {
                return WHT "$n" WHT "忽然感到一股莫名的噁心，全身癱軟，嘴皮烏紫。\n" NOR;
        }
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
        int d_e1 = -15;
        int d_e2 = 10;
        int p_e1 = 30;
        int p_e2 = 55;
        int f_e1 = 110;
        int f_e2 = 210;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("heisha-zhang", 1);
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
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n黑砂掌："NOR"\n");
        write(@HELP

    黑砂掌是川西黑白無常常氏二傑的獨門掌法。掌中藴毒，無常奪命。

        學習要求：
                紅花神功10級
                內力修為20
HELP
        );
        return 1;
}
