// shenlong-sword.c 神龍劍法

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action":"$N使一式「"+BLK+"潮泛銀海"+NOR+"」，手中$w疾挽，漫天寒光，隱夾風雷之聲，閃電般狂湧向$n的$l",
        "force" : 120,
        "lvl" : 0,
        "skill_name" : BLK "潮泛銀海" NOR,
        "damage_type":  "割傷"
]),
([      "action":"$N錯步上前，使出「"+RED+"銀雨飛花"+NOR+"」，手中$w登時劍芒暴射，宛如漫天瑞雪飛灑向$n的$l",
        "force" : 140,
        "lvl" : 20,
        "skill_name" : RED "銀雨飛花" NOR,
        "damage_type":  "割傷"
]),
([      "action":"$N手中$w一抖，一招「"+GRN+"花影濱飛"+NOR+"」，$w猶如狂風掃落葉般急攻向$n的$l",
        "force" : 160,
        "lvl" : 34,
        "skill_name" : GRN "花影濱飛" NOR,
        "damage_type":  "割傷"
]),
([      "action":"$N手中$w鏘啷啷長吟一聲，一式「"+BLU+"神龍尋食"+NOR+"」，$w頭上腳下灑攻而下，攻勢之疾，無以倫比向$n的$l",
        "force" : 180,
        "lvl" : 47,
        "skill_name" : BLU "神龍尋食" NOR,
        "damage_type":  "刺傷"
]),
([      "action":"$N一式「"+MAG+"西風倒卷"+NOR+"」，手中$w將劍自下拖上，端的無比毒辣使$n難斷虛實，無可躲避",
        "force" : 220,
        "lvl" : 60,
        "skill_name" : MAG "西風倒卷" NOR,
        "damage_type":  "刺傷"
]),
([      "action":"$N手中$w,一式「"+BLU+"天羅地網"+NOR+"」，彷彿一面無形的黑網向$n的$l斜斜擊出",
        "force" : 260,
        "lvl" : 80,
        "skill_name" : BLU "天羅地網" NOR,
        "damage_type":  "刺傷"
]),
([      "action":"$N一式「"+HIR+"日月失色"+NOR+"」，$w銀光萬道，如江河倒瀉，劍芒綿綿無盡向$n的胸口遞去",
        "force" : 380,
        "lvl" : 110,
        "skill_name" : HIR "日月失色" NOR,
        "damage_type":  "刺傷"
]),
([      "action":"$N一式「"+YEL+"金針渡劫"+NOR+"」，$w形神合一，把全部真氣貫注劍身之上，快如天光乍閃向$n刺去",
        "force" : 380,
        "lvl" : 150,
        "skill_name" : HIY "金針渡劫" NOR,
        "damage_type":  "刺傷"
])
});
int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int practice_level(){   return 150;  }
int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
        || query("skill_type", weapon) != "sword" )
                if( !objectp(weapon=query_temp("secondary_weapon", me) )
                || query("skill_type", weapon) != "sword" )
                        return notify_fail("你必須先弄把劍才能學神龍劍法。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force", 1) < 40)
                return notify_fail("你的基本內功火候太淺。\n");

        if (me->query_skill("sword", 1) <= me->query_skill("shenlong-jian",1))
                return notify_fail("你的基礎不夠，無法領會更高深的技巧。\n");

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
        level   = (int) me->query_skill("shenlong-jian",1);


        for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
                  return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
        || query("skill_type", weapon) != "sword" )
                if( !objectp(weapon=query_temp("secondary_weapon", me) )
                || query("skill_type", weapon) != "sword" )
                        return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練神龍劍。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不足以練神龍劍。\n");

        me->receive_damage("qi", 25);
        addn("neili", -20, me);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"shenlong-jian/" + action;
}


