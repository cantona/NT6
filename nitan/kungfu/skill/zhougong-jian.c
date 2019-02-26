// zhougong-jian.c 周公劍

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N縱步上前，手中$w斜斜刺出，不知其來路如何，也不知其刺向何方，$n完全無法招架",
        "force" : 120,
        "attack": 41,
        "parry" : 40,
        "dodge" : 31,
        "damage": 10,
        "lvl"   : 0,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中$w猛的反身遞出，制敵機先，疾刺$n的$l",
        "force" : 140,
        "attack": 52,
        "parry" : 41,
        "dodge" : 42,
        "damage": 12,
        "lvl"   : 10,
        "damage_type" : "刺傷"
]),
([      "action": "$N面不露色，手中的$w向$n直直刺去, 這看似很平凡的一招竟然含着巨大的殺着",
        "force" : 150,
        "attack": 58,
        "parry" : 45,
        "dodge" : 43,
        "damage": 20,
        "lvl"   : 20,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中$w隨意揮灑，幻出許許劍芒, 逼得$n連連後退",
        "force" : 170,
        "attack": 61,
        "parry" : 48,
        "dodge" : 48,
        "damage": 25,
        "lvl"   : 40,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中$w光芒閃爍，在許許劍芒中遞出殺着，完全出自$n意料之外",
        "force" : 190,
        "attack": 68,
        "parry" : 51,
        "dodge" : 50,
        "damage": 30,
        "lvl"   : 60,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中$w斜斜刺出，虛虛實實，籠罩$n四周，完全封所了$n的退路",
        "force" : 200,
        "attack": 71,
        "parry" : 55,
        "dodge" : 55,
        "damage": 35,
        "lvl"   : 80,
        "damage_type" : "刺傷"
]),
([      "action": "$N足尖在地上一點而起，半空中點出千萬寒星，分刺$n各處要害",
        "force" : 230,
        "attack": 78,
        "parry" : 60,
        "dodge" : 62,
        "damage": 40,
        "lvl"   : 100,
        "damage_type" : "刺傷"
]),
([      "action": "$N飛身躍起，手中$w舞出無數個閃爍的劍花，滿天閃落而下，制$n於其中",
        "force" : 250,
        "attack": 81,
        "parry" : 64,
        "dodge" : 65,
        "damage": 70,
        "lvl"   : 110,
        "damage_type" : "刺傷"
]),
([      "action": "$N身行晃動不定，手中$w揮灑而出，劃出萬點迅捷無比的寒星灑向$n",
        "force" : 280,
        "attack": 84,
        "parry" : 68,
        "dodge" : 75,
        "damage": 69,
        "lvl"   : 120,
        "damage_type" : "刺傷"
]),
([      "action": "$N隨意揮灑手中$w，頓時幻出萬般劍芒, 數股劍氣從劍芒中遞出，直知貫向$n",
        "force" : 300,
        "attack": 88,
        "parry" : 70,
        "dodge" : 78,
        "damage": 80,
        "lvl"   : 130,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中$w遙指蒼天，劍芒吞吐不定，一式「玉帶圍腰」，對準$n的$l直貫而去",
        "force" : 330,
        "attack": 91,
        "parry" : 72,
        "dodge" : 85,
        "damage": 88,
        "lvl"   : 140,
        "damage_type" : "刺傷"
]),
([      "action": "$N一式「天如穹廬」，只見$w突然從天而降，一股強大的劍氣席捲$n全身",
        "force" : 350,
        "attack": 94,
        "parry" : 72,
        "dodge" : 85,
        "damage": 100,
        "lvl"   : 150,
        "damage_type" : "割傷"
]),
([      "action": HIW "$N" HIW "一聲爆喝，身法陡然加快，手中劍芒吞吐不定，身外化身，劍外"
                  "化劍，手中$w" HIW "如飛龍一般遞出！\n" NOR "$n眼見這突如其來的一劍，面"
                  "如死灰，完全不知道該如何抵擋，想抽身後退，身後一股強大的劍氣\n又云湧而至",
        "force" : 470,
        "attack": 138,
        "dodge" : -167,
        "parry" : -135,
        "damage": 280,
        "lvl"   : 250,
        "damage_type": "刺傷"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力不夠，無法學習周公劍。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的內功火候不夠，無法學習周公劍。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候不夠，無法學習周公劍。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("zhougong-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的周公劍。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("zhougong-jian", 1))
                return notify_fail("你的基本內功水平有限，無法領會更高深的周公劍。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("zhougong-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練周公劍。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練周公劍。\n");

        me->receive_damage("qi", 50);
        addn("neili", -100, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zhougong-jian/" + action;
}
int query_effect_parry(object attacker, object me)
{
        int lvl;
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) )
                return 0;

        if( query("skill_type", weapon) != "sword" )
                return 0;

        lvl = me->query_skill("zhougong-jian", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}