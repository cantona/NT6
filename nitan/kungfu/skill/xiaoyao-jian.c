// This program is a part of NT MudLIB
// 逍遙劍法

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N一招「落葉飄飄」，$w似幻作無數道銀索，四面八方的罩向$n",
        "force"  : 110,
        "attack" : 35,
        "dodge"  : -20,
        "parry"  : -25,
        "damage" : 43,
        "lvl"    : 0,
        "skill_name" : "落葉飄飄",
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「水中浮萍」，劍鋒亂指，攻向$n，$n根本不能分辯$w的來路",
        "force"  : 155,
        "attack" : 43,
        "dodge"  : -25,
        "parry"  : -34,
        "damage" : 51,
        "lvl"    : 20,
        "skill_name" : "中浮萍",
        "damage_type" : "刺傷"
]),
([      "action" : "$N使出「飄然直去」，$w幻一條飛練，帶著一股寒氣劃向$n的$l",
        "force"  : 178,
        "attack" : 48,
        "dodge"  : -28,
        "parry"  : -24,
        "damage" : 62,
        "lvl"    : 40,
        "skill_name" : "飄然直去",
        "damage_type" : "刺傷"
]),
([      "action" : "$N身子向上彈起，左手下指，一招「千裡不留行」，右手$w帶著一團劍花，逼向$n的$l",
        "force"  : 211,
        "attack" : 53,
        "dodge"  : -22,
        "parry"  : -24,
        "damage" : 84,
        "lvl"    : 60,
        "skill_name" : "千裡不留行",
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「拂衣抹劍」，左腳躍步落地，右手$w幻成一條雪白的瀑布，掃向$n的$l",
        "force"  : 238,
        "attack" : 69,
        "dodge"  : -28,
        "parry"  : -35,
        "damage" : 95,
        "lvl"    : 80,
        "skill_name" : "拂衣抹劍",
        "damage_type" : "刺傷"
]),
([      "action" : "$N右腿半屈般蹲，$w平指，一招「仙人何去」，劍尖無聲無色的慢慢的刺向$n的$l",
        "force"  : 268,
        "attack" : 73,
        "dodge"  : -38,
        "parry"  : -15,
        "damage" : 110,
        "lvl"    : 100,
        "skill_name" : "仙人何去",
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「夢裡看劍」，劍鋒亂指，攻向$n，$n根本不能分辯$w的來路",
        "force"  : 255,
        "attack" : 71,
        "dodge"  : -25,
        "parry"  : -24,
        "damage" : 108,
        "lvl"    : 120,
        "skill_name" : "夢裡看劍",
        "damage_type" : "刺傷"
]),
([      "action" : "$N使出「深山空谷」，$w幻一條飛練，帶著一股寒氣劃向$n的$l",
        "force"  : 270,
        "attack" : 78,
        "dodge"  : -18,
        "parry"  : -19,
        "damage" : 123,
        "lvl"    : 140,
        "skill_name" : "深山空谷",
        "damage_type" : "刺傷"
]),
([      "action" : "$N身子向上彈起，左手下指，一招「群仙聚會」，右手$w帶著一團劍花，逼向$n的$l",
        "force"  : 291,
        "attack" : 103,
        "dodge"  : -23,
        "parry"  : -28,
        "damage" : 141,
        "lvl"    : 160,
        "skill_name" : "群仙聚會",
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「飄飄不定」，左腳躍步落地，右手$w幻成一條雪白的瀑布，掃向$n的$l",
        "force"  : 283,
        "attack" : 91,
        "dodge"  : -22,
        "parry"  : -25,
        "damage" : 155,
        "lvl"    : 180,
        "skill_name" : "飄飄不定",
        "damage_type" : "刺傷"
]),
([      "action" : "$N右腿半屈般蹲，$w平指，一招「千山萬水」，劍尖無聲無色的慢慢的刺向$n的$l",
        "force"  : 300,
        "attack" : 97,
        "dodge"  : -28,
        "parry"  : -37,
        "damage" : 158,
        "lvl"    : 200,
        "skill_name" : "千山萬水",
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「去留人間」，$w在$n的周身飛舞，令$n眼花繚亂，劍身在半空中突然停住刺向$n的$l",
        "force"  : 328,
        "attack" : 118,
        "dodge"  : -25,
        "parry"  : -27,
        "damage" : 170,
        "lvl"    : 220,
        "skill_name" : "去留人間",
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) {return usage == "sword" || usage == "parry";}

int valid_learn(object me)
{
        /*
        if (query("int", me) < 30)
                return notify_fail("你先天悟性不足，無法領悟逍遙劍法。\n");
        */
        if ((int)query("max_neili", me) < 2500)
                return notify_fail("你的內力修為不夠，無法學習逍遙劍法。\n");

        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("你的基本內功火候太淺，無法學習逍遙劍法。\n");

        if ((int)me->query_skill("dodge", 1) < 120)
                return notify_fail("你的基本內功火候太淺，無法學習逍遙劍法。\n");

        if ((int)me->query_skill("sword", 1) < 120)
                return notify_fail("你的基本劍法火候不夠，無法學習逍遙劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("xiaoyao-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的逍遙劍法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon;

        int lvl = me->query_skill("xiaoyao-jian", 1);
        weapon = query_temp("weapon", me);

        if (lvl < 130 || lvl / 2 + random(lvl) < (int)victim->query_skill("dodge", 1) ||
            query("neili", me) < 150 ||
            me->query_skill("dodge", 1) < 180 ||
            me->query_skill("force", 1) < 150 ||
            victim->is_busy() )
                 return 0;

        message_vision(HIW "\n$N" HIW "右手" + weapon->name() + HIW "猛然旋轉，劍光突"
                       "現，剎那間已將$n" HIW "退路全部封死。\n" NOR, me, victim);

        addn("neili", -80, me);
        victim->start_busy(2 + random(lvl / 30));

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("xiaoyao-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的武器不對。\n");

        if ((int)query("qi", me) < 60)
                return notify_fail("你的體力目前沒有辦法練習逍遙劍法。\n");

        if ((int)query("neili", me) < 90)
                return notify_fail("你的內力不夠，無法練習逍遙劍法。\n");

        addn("qi", -50, me);
        addn("neili", -82, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xiaoyao-jian/" + action;
}