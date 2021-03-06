// dragon-strike.c 降龍十八掌之損則有孚
// Last Modified by sega on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});
int d_e1 = -60;
int d_e2 = -40;
int p_e1 = -20;
int p_e2 = 10;
int f_e1 = 350;
int f_e2 = 550;
int ttl = 17;
int seq = 13;
mapping *action = ({
        ([
                "action"      : "$N使出"+(order[random(13)])+"「損則有孚」"NOR"，雙掌軟綿綿地拍向$n的$l",
                "skill_name" : "損則有孚",
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]),
});


string main_skill() { return "dragon-strike"; }
int valid_enable(string usage) { return usage=="strike" ; }

int valid_learn(object me)
{
        if (me->query_skill("dragon-strike", 1) > 0)
                return notify_fail("你已經學全十八掌了，不必再單獨學習。\n");

        if( query("str", me)<31 )
                return notify_fail("你的先天膂力孱弱，難以修煉降龍十八掌。\n");

        if( query("con", me)<24 )
                return notify_fail("你的先天根骨孱弱，難以修煉降龍十八掌。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功火候不夠，難以修煉降龍十八掌。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不足，難以修煉降龍十八掌。\n");

        if ((int)me->query_skill("strike", 1) < 180)
                return notify_fail("你的基本掌法火候不夠，難以修煉降龍十八掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("sunze-youfu", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的降龍十八掌。\n");

        return 1;
}


int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練降龍十八掌。\n");
        me->receive_damage("qi", 100);
        addn("neili", -40, me);
        return 1;
}
string query_skill_name(int level)
{
                        return action[0]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        return action[0];
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) {
        if (userp(me)) return 0.5; //因為是半成品 不允許高
  return 1;
}

int help(object me)
{
        write(HIC"\n降龍十八掌之損則有孚："NOR"\n");
        write(@HELP

    降龍十八掌是丐幫鎮幫之寶，是天下最剛猛的武功。

        學習要求：
                得到洪七公親自指點
                內力1000
                先天臂力25
                先天根骨20
                基本掌法180
HELP
        );
        return 1;
}