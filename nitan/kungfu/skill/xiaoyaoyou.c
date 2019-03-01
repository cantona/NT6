// xiaoyaoyou.c 逍遙遊拳法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$n一個"RED"「蜻蜓點水」"NOR"，躲過了$N這一招。\n",
        "$n身形向後一縱，使出一招"HIW"「細胸巧翻雲」"NOR"，避過了$N的攻擊。\n",
        "$n使出"BLU"「虛懷若谷」"NOR"，恰好躲過了$N的攻勢。\n"
        "但是$n一招"HIY"「蜻蜓點水」"NOR"身形飄忽，輕輕一縱，早已避開。\n",
        "$n身隨意轉，一招"MAG"「細胸巧翻雲」"NOR"倏地往一旁挪開了三尺，避過了這一招。\n",
        "可是$n側身一讓，一招"HIY"「虛懷若谷」"NOR"$N這一招撲了個空。\n",
        "卻見$n足不點地，一招"GRN"「蜻蜓點水」"NOR"往旁竄開數尺，躲了開去。\n",
        "$n身形微晃，一招"HIB"「虛懷若谷」"NOR"有驚無險地避開了$N這一招。\n"
});
mapping *action = ({
([      "action" : "$N一掌輕出，一招「清風斜雨」直襲$n的$l，了無半點痕跡",
        "force"  : 30,
        "dodge"  : 30,
        "damage" : 2,
        "lvl"    : 0,
        "skill_name"  : "清風斜雨",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N轉過身來，一招「垂釣江畔」，左腳輕點，右掌揮向$n的臉部",
        "force"  : 50,
        "dodge"  : 40,
        "damage" : 5,
        "lvl"    : 10,
        "skill_name"  : "垂釣江畔",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N虛步側身，一招「落葉雅意」，手腕一轉，劈向$n",
        "force"  : 60,
        "dodge"  : 45,
        "damage" : 10,
        "lvl"    : 20,
        "skill_name"  : "落葉雅意",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一招「歸路未曉」，雙掌化作無數掌影，輕飄飄的拍向$n",
        "force"  : 70,
        "dodge"  : 55,
        "damage" : 15,
        "lvl"    : 34,
        "skill_name"  : "歸路未曉",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一招「春風拂柳」，左掌手指微微張開，拂向n的手腕",
        "force"  : 90,
        "dodge"  : 70,
        "damage" : 20,
        "lvl"    : 45,
        "skill_name"  : "春風拂柳",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N使出一招「逍遙世間」，一掌拍出，仿佛不食半點人間煙火",
        "force"  : 110,
        "dodge"  : 75,
        "damage" : 25,
        "lvl"    : 59,
        "skill_name"  : "逍遙世間",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身形飄忽，一招「我心猶憐」，雙掌軟綿綿的拍向$n",
        "force"  : 120,
        "dodge"  : 80,
        "damage" : 30,
        "lvl"    : 80,
        "skill_name"  : "我心猶憐",
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage)
{
        return usage == "dodge"
            || usage == "parry"
            || usage == "strike";
}

int valid_combine(string combo)
{
        return combo == "jueming-tui";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("學習逍遙遊掌法必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學逍遙遊掌法。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為太弱，無法練逍遙遊掌法。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("xiaoyaoyou", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的逍遙遊掌法。\n");

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("xiaoyaoyou", 1))
                return notify_fail("你的基本輕功水平有限，無法領會更高深的逍遙遊掌法。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<6 )
                return notify_fail("你的體力太差了，無法練習逍遙遊。\n");
        me->receive_damage("qi", 30);
        addn("neili", -6, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action) - 1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;

        level = (int)me->query_skill("xiaoyaoyou", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}
int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.3; }

string perform_action_file(string action)
{
        return __DIR__"xiaoyaoyou/" + action;
}

int help(object me)
{
        write(HIC"\n逍遙遊："NOR"\n");
        write(@HELP

    逍遙遊是丐幫本門輕功身法。

        學習要求：

           混天氣功10級或有洪七公指點
HELP
        );
        return 1;
}
