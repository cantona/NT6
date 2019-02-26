// shou-yin.c 手印(徐子陵)

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N使出一招「蓮花合掌印」，雙掌做錐，直直刺向$n的前胸",
        "force"    : 589,
        "attack"   : 285,
        "dodge"    : 167,
        "parry"    : 189,
        "damage"   : 303,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "刺傷",
]),
([      "action" : "$N使出一招「合掌觀音印」，飛身躍起，雙手如勾，抓向$n的$l",
        "force"    : 621,
        "attack"   : 309,
        "dodge"    : 188,
        "parry"    : 197,
        "damage"   : 326,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "刺傷",
]),
([      "action" : "$N使出一招「準提佛母印」，運力於指，直取$n的$l",
        "force"    : 642,
        "attack"   : 321,
        "dodge"    : 197,
        "parry"    : 203,
        "damage"   : 339,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "刺傷",
]),
([      "action" : "$N使出一招「紅閻婆羅印」，怒吼一聲，一掌當頭拍向$n的$l",
        "force"    : 657,
        "attack"   : 335,
        "dodge"    : 215,
        "parry"    : 227,
        "damage"   : 356,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "內傷",
]),
([      "action" : "$N使出一招「藥師佛根本印」，猛衝向前，掌刀如游龍般砍向$n",
        "force"    : 673,
        "attack"   : 357,
        "dodge"    : 243,
        "parry"    : 236,
        "damage"   : 367,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "割傷",
]),
([      "action" : "$N使出一招「威德金剛印」，伏身疾進，雙掌自下掃向$n的$l",
        "force"    : 672,
        "attack"   : 371,
        "dodge"    : 265,
        "parry"    : 257,
        "damage"   : 386,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "割傷",
]),
([      "action" : "$N使出一招「上樂金剛印」，飛身橫躍，雙掌前後擊出，抓向$n的咽"
                   "喉",
        "force"    : 680,
        "attack"   : 398,
        "dodge"    : 297,
        "parry"    : 271,
        "damage"   : 403,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "刺傷",
]),
([      "action" : "$N使出一招「六臂智慧印」，頓時勁氣瀰漫，天空中出現無數掌影打"
                   "向$n",
        "force"    : 720,
        "attack"   : 435,
        "dodge"    : 315,
        "parry"    : 287,
        "damage"   : 436,
        "weapon"   : HIW "手印" NOR,
        "damage_type" : "割傷",
]),
});

int double_attack() { return 1; }

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練手印必須空手。\n");

        if( query("int", me)<36 )
                return notify_fail("你覺得手印過於艱深，難以理解。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("你的武學修養太低，無法修習手印。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 350)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("hand", 1) < 200)
                return notify_fail("你的基本手法火候太淺。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("shou-yin",1))
                return notify_fail("你的基本手法水平有限，無法領會更高深的手印。\n");

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
                  level   = (int) me->query_skill("shou-yin",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練大手印法必須空手。\n");

        if( query("qi", me)<350 )
                return notify_fail("你的體力不夠，練不了手印。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠，練不了手印。\n");

        me->receive_damage("qi", 300);
        addn("neili", -300, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 100) return 0;

        if (damage_bonus / 5 > victim->query_str())
        {
                victim->receive_wound("qi", (damage_bonus - 100) / 2);
                return HIR "只聽" + victim->name() +
                       HIR "一聲悶哼，一雙" NOR + HIW "手印"
                       NOR + HIR "重重的印在胸前，“哇”"
                       "的噴出了一大口鮮血！\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"shou-yin/" + action;
}
