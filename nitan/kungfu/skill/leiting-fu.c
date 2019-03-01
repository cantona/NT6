#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$N立定當地，手中的$w在面前移動，突然一招「春雷炸空」向$n劈去",
        "skill_name" : "春雷炸空",
        "force" : 320,
        "attack": 27,
        "dodge" : -30,
        "parry" : -34,
        "lvl"   : 0,
        "damage": 62,
        "damage_type" : "挫傷",
]),
([      "action" : "$N淵停岳峙，身形猛的升起五丈，一招「飛驚落虹」寒光乍現般向$n劈去",
        "skill_name" : "飛驚落虹",
        "force" : 460,
        "attack": 38,
        "dodge" : -27,
        "parry" : -45,
        "lvl"   : 40,
        "damage": 66,
        "damage_type" : "挫傷",
]),
([      "action" : "$N突然暴喝一聲，手裡的$w一挫，一招「蒼穹開破」猛的劈向$n而去",
        "skill_name" : "蒼穹開破",
        "force" : 500,
        "attack": 43,
        "dodge" : -25,
        "parry" : -47,
        "lvl"   : 80,
        "damage": 70,
        "damage_type" : "挫傷",
]),
([      "action" : "$N斜移兩步，手中$w發出陣陣寒光，陡然間一招「破碎虛空」劈向$n",
        "skill_name" : "破碎虛空",
        "force" : 520,
        "attack": 51,
        "dodge" : -45,
        "parry" : -50,
        "lvl"   : 120,
        "damage": 75,
        "damage_type" : "挫傷",
]),
([      "action" : "$N雙手一頓，一招「火雨流星」，手中的$w以極快的速度向$n連劈數下",
        "skill_name" : "火雨流星",
        "force" : 530,
        "attack": 55,
        "dodge" : -20,
        "parry" : -25,
        "lvl"   : 160,
        "damage": 80,
        "damage_type" : "挫傷",
]),
([      "action" : "$N將$w舞得尤如萬條金龍，使人不敢靠近，猛的一招「魂冥千屠」向$n劈去",
        "skill_name" : "魂冥千屠",
        "force" : 550,
        "attack": 65,
        "dodge" : -40,
        "parry" : -35,
        "lvl"   : 180,
        "damage": 98,
        "damage_type" : "挫傷",
]),
([      "action" : "$N手中的$w“鐺”的一聲，斧鋒側翻，光鏵驟閃，一招「絕寰電閃」劈向$n",
        "skill_name" : "絕寰電閃",
        "force" : 570,
        "attack": 84,
        "dodge" : -62,
        "parry" : -33,
        "lvl"   : 220,
        "damage": 104,
        "damage_type" : "挫傷",
]),
([      "action" : "$N斧尖指天，斧鋒驟顫，陡然施出一招「泣血驚天」，數十道冷光劈向$n",
        "skill_name" : "泣血驚天",
        "force" : 580,
        "attack": 97,
        "dodge" : -62,
        "parry" : -33,
        "lvl"   : 260,
        "damage": 113,
        "damage_type" : "挫傷",
]),
([      "action" : "$N突然一招「創刃無還」，手中的$w像是穹蒼中的一道閃電般劈向$n",
        "skill_name" : "創刃無還",
        "force" : 610,
        "attack": 109,
        "dodge" : -62,
        "parry" : -33,
        "lvl"   : 280,
        "damage": 121,
        "damage_type" : "挫傷",
]),
([      "action" : "$N一越拔空，長嘯仿如龍吟，施一招「天外歸星」，$w猶如一個光球劈向$n",
        "skill_name" : "天外歸星",
        "force" : 640,
        "attack": 130,
        "dodge" : -62,
        "parry" : -33,
        "lvl"   : 300,
        "damage": 134,
        "damage_type" : "挫傷",
]),
});


int valid_enable(string usage)
{
        return usage == "hammer" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("str", me)<35 )
                return notify_fail("你的先天膂力孱弱，無法修煉雷霆斧法。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為太淺，無法修煉雷霆斧法。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功火候太淺，無法修煉雷霆斧法。\n");

        if ((int)me->query_skill("hammer", 1) < 180)
                return notify_fail("你的基本錘法火候太淺，無法修煉雷霆斧法。\n");

        if ((int)me->query_skill("hammer", 1) < (int)me->query_skill("leiting-fu", 1))
                return notify_fail("你的基本錘法水平有限，無法領會更高深的雷霆斧法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("leiting-fu",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if (me->query_skill("leiting-fu", 1) < 260)
                return notify_fail("你對雷霆斧法了解不夠，還不足以自行鍛煉。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "hammer" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<130 )
                return notify_fail("你的體力不夠，練不了雷霆斧法。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠，練不了雷霆斧法。\n");

        me->receive_damage("qi", 100);
        addn("neili", -150, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"leiting-fu/" + action;
}