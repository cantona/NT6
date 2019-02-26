#include <ansi.h>
inherit SKILL;

mapping *action = ({
([        "action" : "$N一招「赤色落陽」，掌力化成弧形，罩向$n的$l",
        "force" : 60,
        "attack": 2,
        "parry" : 1,
        "damage": 2,
        "lvl"   : 0,
        "skill_name" : "赤色落陽",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一招「七彩流金」，身體高高躍起，撲向$n的$l就"
                   "是一記重掌",
        "force" : 80,
        "attack": 8,
        "parry" : 3,
        "damage": 4,
        "lvl"   : 20,
        "skill_name" : "七彩流金",
        "damage_type" : "內傷"
]),
([        "action" : "$N一招「赤蝶迎晚霞」，忽然袖中雙掌咋現，分別從"
                   "左右兩邊齊齊攻向$n",
        "force" : 100,
        "attack": 12,
        "dodge" : 43,
        "damage": 6,
        "lvl"   : 30,
        "skill_name" : "赤蝶迎晚霞",
        "damage_type" : "瘀傷"
]),

([        "action" : "$N一招「羣山遮落日」,頭緩緩低下，似乎顯得沒精打"
                   "採，一記雲掌軟綿綿的拍向$n",
        "force" : 130,
        "attack": 15,
        "dodge" : 55,
        "damage": 8,
        "lvl"   : 40,
        "skill_name" : "羣山遮落日",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一招「幽幽谷中敍」，突然縱起丈餘，猶如一隻在空"
                   "中盤旋的飛龍，一掌拍向$n",
        "force" : 150,
        "attack": 22,
        "dodge" : 52,
        "damage": 14,
        "lvl"   : 60,
        "skill_name" : "幽幽谷中敍",
        "damage_type" : "瘀傷"
]),

([        "action" : "$N雙掌平揮，一招「冥冥道中聚」身如陀螺急轉，忽然"
                   "飛身而起，一掌拍向$n的$l",
        "force" : 180,
        "attack": 23,
        "dodge" : 65,
        "damage": 25,
        "lvl"   : 80,
        "skill_name" : "冥冥道中聚",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一招「高堂明鏡」，猶如一隻展翅翱翔的大鵬，運掌"
                   "如風般襲向$n",
        "force" : 210,
        "attack": 20,
        "dodge" : 63,
        "damage": 40,
        "lvl"   : 100,
        "skill_name" : "高堂明鏡",
        "damage_type" : "內傷"
]),

([        "action" : "$N左掌虛晃，右掌一記「天上人間」猛地插往$n的$l",
        "force" : 240,
        "attack": 18,
        "dodge" : 77,
        "damage": 50,
        "lvl"   : 120,
        "skill_name" : "天上人間",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N施出「金石為開」，雙掌不斷反轉，忽地併攏，筆直"
                   "地向$n的$l襲去",
        "force" : 260,
        "attack": 21,
        "dodge" : 80,
        "damage": 60,
        "lvl"   : 140,
        "skill_name" : "金石為開",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N施出「萬眾歸心」，雙掌翻騰不息，龍吟般的卷向$n",
        "force" : 280,
        "attack": 25,
        "dodge" : 81,
        "damage": 80,
        "lvl"   : 160,
        "skill_name" : "萬眾歸心",
        "damage_type" : "瘀傷"
])
});

int valid_enable(string usage)
{
        return usage == "parry" || usage == "strike";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練赤練神掌必須空手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，無法練赤練神掌。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力太弱，無法練赤練神掌。\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("你的基本掌法火候不夠，無法練赤練神掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("chilian-shenzhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的赤練神掌。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("chilian-shenzhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練赤練神掌。\n");

        me->receive_damage("qi", 61);
        addn("neili", -53, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chilian-shenzhang/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("chilian-shenzhang", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("poison",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "name"  : "赤練神掌毒",
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIW "$n" HIW "猛然覺得一陣寒氣襲來，身子一晃，頭腦微微有些發昏。\n" NOR;
        }
}