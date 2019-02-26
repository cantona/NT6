#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N縱步上前，手中$w斜斜刺出，也不知其刺向何方，$n完全無法招架",
        "force" : 72,
        "attack": 41,
        "parry" : 40,
        "dodge" : 31,
        "damage": 14,
        "lvl"   : 0,
        "damage_type" : "刺傷"
]),
([      "action": "$N退後三尺，手中$w猛的反身遞出，制敵機先，疾刺$n的$l",
        "force" : 94,
        "attack": 52,
        "parry" : 41,
        "dodge" : 42,
        "damage": 25,
        "lvl"   : 20,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中的$w向$n直直刺去, 這看似很平凡的一招竟然含着巨大的殺着",
        "force" : 115,
        "attack": 58,
        "parry" : 45,
        "dodge" : 43,
        "damage": 36,
        "lvl"   : 40,
        "damage_type" : "刺傷"
]),
([      "action": "$N一聲大喝，手中$w隨意揮灑，幻出許許劍芒，逼得$n連連後退",
        "force" : 127,
        "attack": 61,
        "parry" : 48,
        "dodge" : 48,
        "damage": 45,
        "lvl"   : 60,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中$w光芒閃爍，在許許劍芒中遞出殺着，完全出自$n意料之外",
        "force" : 139,
        "attack": 68,
        "parry" : 51,
        "dodge" : 50,
        "damage": 52,
        "lvl"   : 80,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中$w斜斜刺出，虛虛實實，籠罩$n四周，完全封所了$n的退路",
        "force" : 152,
        "attack": 71,
        "parry" : 55,
        "dodge" : 55,
        "damage": 58,
        "lvl"   : 100,
        "damage_type" : "刺傷"
]),
([      "action": "$N足尖在地上一點而起，半空中點出千萬寒星，分刺$n各處要害",
        "force" : 173,
        "attack": 78,
        "parry" : 60,
        "dodge" : 62,
        "damage": 65,
        "lvl"   : 120,
        "damage_type" : "刺傷"
]),
([      "action": "$N飛身躍起，手中$w舞出無數個閃爍的劍花，滿天閃落而下，制$n於其中",
        "force" : 185,
        "attack": 81,
        "parry" : 64,
        "dodge" : 65,
        "damage": 78,
        "lvl"   : 140,
        "damage_type" : "刺傷"
]),
([      "action": "$N身行晃動不定，手中$w揮灑而出，劃出萬點迅捷無比的寒星灑向$n",
        "force" : 210,
        "attack": 94,
        "parry" : 68,
        "dodge" : 75,
        "damage": 91,
        "lvl"   : 160,
        "damage_type" : "刺傷"
]),
([      "action": "$N隨意揮灑手中$w，頓時幻出萬般劍芒, 數股劍氣從劍芒中遞出，直知貫向$n",
        "force" : 223,
        "attack": 104,
        "parry" : 70,
        "dodge" : 78,
        "damage": 102,
        "lvl"   : 180,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中$w遙指蒼天，劍芒吞吐不定，陡然間劍芒暴漲，對準$n的$l直貫而去",
        "force" : 238,
        "attack": 115,
        "parry" : 72,
        "dodge" : 85,
        "damage": 118,
        "lvl"   : 200,
        "damage_type" : "刺傷"
]),
([      "action": "$N一聲巨喝，體內真氣迸發，只見$w從天而降，一股強大的劍氣席捲$n全身",
        "force" : 280,
        "attack": 124,
        "parry" : 72,
        "dodge" : 85,
        "damage": 140,
        "lvl"   : 220,
        "damage_type" : "割傷"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力修為不夠，無法學習原始劍法。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的內功火候不夠，無法學習原始劍法。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候不夠，無法學習原始劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("yuanshi-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的原始劍法。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("yuanshi-jian", 1))
                return notify_fail("你的基本內功水平有限，無法領會更高深的原始劍法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yuanshi-jian", 1);
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
                return notify_fail("你的體力不夠練原始劍法。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練原始劍法。\n");

        me->receive_damage("qi", 50);
        addn("neili", -100, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yuanshi-jian/" + action;
}