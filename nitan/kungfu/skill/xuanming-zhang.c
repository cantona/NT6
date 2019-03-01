// create by rcwiz 2003 for yanhuang online 

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action" : "$N使出一招「雪海茫茫」，雙掌陡然攻出，帶著絲絲陰風擊向$n的$l",
        "force" : 100,
        "attack": 25,
        "dodge" : 15,
        "parry" : 20,
        "damage": 10,
        "lvl"   : 0,
        "skill_name" : "雪海茫茫",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N使出一招「幽冥寒山」，左掌護胸，右掌掌心帶著極寒之氣拍向$n的$l",
        "force" : 130,
        "attack": 30,
        "dodge" : 10,
        "parry" : 15,
        "damage": 20,
        "lvl"   : 30,
        "skill_name" : "幽冥寒山",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N怪叫一聲，一招「陰風怒號」，雙掌舖天蓋地般拍向$n的$l",
        "force" : 160,
        "attack": 45,
        "dodge" : 20,
        "parry" : 20,
        "damage": 25,
        "lvl"   : 60,
        "skill_name" : "陰風怒號",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一照「凄雨冷風」，雙掌拍出滿天陰風，忽然右掌悄無聲息的拍向$n的$l",
        "force" : 180,
        "attack": 50,
        "dodge" : 20,
        "parry" : 30,
        "damage": 30,
        "lvl"   : 80,
        "skill_name" : "凄雨冷風",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身形一躍，一招「亡命冰原」，左掌快若疾電般擊向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 35,
        "lvl"   : 100,
        "skill_name" : "亡命冰原",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N陰笑一聲，一招「孤山絕寒」，雙掌一錯，右掌忽然暴長數尺擊向$n的$l",
        "force" : 280,
        "attack": 95,
        "dodge" : 25,
        "parry" : 25,
        "damage": 55,
        "lvl"   : 120,
        "skill_name" : "孤山絕寒",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一招「雪原孤月」，身形急晃，一躍而至$n跟前，右掌帶著沖天寒氣擊向$n的$l",
        "force" : 320,
        "attack": 110,
        "dodge" : 30,
        "parry" : 30,
        "damage": 70,
        "lvl"   : 140,
        "skill_name" : "雪原孤月",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N仰天長嘯，一招「魂葬玄冥」，雙掌掌風似千古不化的寒冰般撲向$n的$l",
        "force" : 360,
        "attack": 135,
        "dodge" : 30,
        "parry" : 35,
        "damage": 95,
        "lvl"   : 150,
        "skill_name" : "魂葬玄冥",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身法陡然一變，使出一式「幽玄冥冥」，掌影千變萬幻，令$n無法躲閃",
        "force" : 420,
        "attack": 150,
        "dodge" : 30,
        "parry" : 75,
        "damage": 110,
        "lvl"   : 160,
        "skill_name" : "幽玄冥冥",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N仰天一聲狂嘯，一式「冰堅地獄」，雙掌攜帶著萬古冰堅直直貫向$n",
        "force" : 450,
        "attack": 185,
        "dodge" : 40,
        "parry" : 80,
        "damage": 160,
        "lvl"   : 180,
        "skill_name" : "冰堅地獄",
        "damage_type" : "內傷"
])
});

int valid_enable(string usage)
{
        return usage=="strike" || usage=="parry";
}

int valid_learn(object me)
{
        if( query("character", me) == "光明磊落" )
                return notify_fail("你心中暗想：我為人光明磊落，豈能學習這種陰毒武功？\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練玄冥神掌必須空手。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，無法練習玄冥神掌。\n");

       if( query("con", me)<30 )
                return notify_fail("你先天根骨不足，無法修煉玄冥神掌。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力太弱，無法練習玄冥神掌。\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("你的基本掌法火候不夠，無法練玄冥神掌。\n");

        if ((int)me->query_skill("xuanming-shengong", 1) < (int)me->query_skill("xuanming-zhang", 1))
                return notify_fail("你的玄冥神功水平有限，無法領會更高深的玄冥神掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("xuanming-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的玄冥神掌。\n");

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
        int i, level;
        level   = (int) me->query_skill("xuanming-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("con", me)<30 )
                return notify_fail("你先天根骨不足，無法修煉玄冥神掌。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練玄冥神掌。\n");

        me->receive_damage("qi", 80);
        addn("neili", -80, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("xuanming-zhang", 1);
        flvl=query("jiali", me);
        if (lvl < 240 || ! damage_bonus ||
            me->query_skill_mapped("force") != "xuanming-shengong" ||
            query("neili", me)<300 )
                return;

        if (flvl * 5 / 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("xuanming_poison",
                              ([ "level" : flvl * 3,
                                 "id":query("id", me),
                                 "duration" : lvl / 40 + random(lvl / 20) ])))
        {
                addn("neili", -100, me);
                return HIW "$n" HIW "忽然感到一股莫名的惡心，陰寒的冷氣攻心，全身癱軟，嘴皮烏紫。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"xuanming-zhang/" + action;
}
