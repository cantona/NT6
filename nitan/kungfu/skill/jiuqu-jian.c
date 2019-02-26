#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" :  "$N左晃右躥，手中$w突然刺向$n$l，正是一招「千溝萬壑」",
        "force"  :  45,
        "dodge"  :  20,
        "parry"  :  20,
        "attack" :  10,
        "damage" :  20,
        "lvl"    :  0,
        "damage_type" :  "刺傷",
        "skill_name"  :  "千溝萬壑",
]),
([      "action" :  "$N越攻越猛，突然間手中$w劍光暴漲，一招「峯迴路轉」已然使出\n"
                    "$n只覺眼前劍光耀眼，不由得心中一驚",
        "force"  :  90,
        "dodge"  :  26,
        "parry"  :  40,
        "attack" :  24,
        "damage" :  35,
        "lvl"    :  25,
        "damage_type" :  "刺傷",
        "skill_name"  :  "峯迴路轉",
]),
([     
        "action" :  "$N以攻為守，以進為退，手中$w刷的一劍「天外飛鳳」，向$n$l刺去",
        "force"  :  110,
        "dodge"  :  35,
        "parry"  :  40,
        "attack" :  30,
        "damage" :  40,
        "lvl"    :  50,
        "damage_type":  "刺傷",
        "skill_name":   "天外飛鳳",
]),
([      
        "action" :  "$N輕嘯一聲，$w徑直向$n$w，這一劍雖無任何招式，但是$N卻使得不\n"
                    "卑不亢，毫無滯帶，將「千山暮雪」這一招發揮到了及至",
        "force"  :  120, 
        "dodge"  :  48,
        "parry"  :  45,
        "attack" :  35,
        "damage" :  48,
        "lvl"    :  75,
        "damage_type" :  "刺傷",
        "skill_name"  :  "千山暮雪",
]),
([      
        "action" : "$N將$w一揮，長嘯一聲，騰空而起，使出一式「神風式」！這一招來得又\n"
                   "快又準，$w直指$n$l,",
        "force"  :  130,
        "dodge"  :  56,
        "parry"  :  66,
        "attack" :  55,
        "damage" :  60,
        "lvl"    :  100,
        "damage_type" :  "刺傷",
        "skill_name"  :  "神風式",
]),
});

int valid_learn(object me)
{
            object ob; 

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");

            if( query("max_neili", me)<300 )
                return notify_fail("你的內力不夠，沒有辦法練九曲劍法。\n");

            if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候太淺。\n");

            if ((int)me->query_skill("sword", 1) < 60)
                   return notify_fail("你的基本劍法火候不夠，無法學習九曲劍法。\n");

            if (me->query_skill("sword", 1) < me->query_skill("jiuqu-jian", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的九曲劍法。\n");

        return 1;
}

int valid_enable(string usage)
{
            return usage == "sword" || usage == "parry";
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

        level = (int) me->query_skill("jiuqu-jian", 1);
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

       if( query("neili", me)<60 )
                   return notify_fail("你的內力不足，沒有辦法練習九曲劍法。\n");

       if( query("qi", me)<65 )
                   return notify_fail("你的體力不夠練九曲劍法。\n");

       me->receive_damage("qi", 40);
       addn("neili", -50, me);
       return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jiuqu-jian/" + action;
}
