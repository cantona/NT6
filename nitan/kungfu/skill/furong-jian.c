#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
        "action" : "$N手中$w“嗖”地遞出，突然間半空挽出一個劍花，正是一招「芙蓉花開」\n"
                   "不知不覺間，$w已經向$n的$l刺去",
        "force"  : 45,
        "dodge"  : 18,
        "parry"  : 20,
        "attack" : 10,
        "damage" : 20,
        "lvl"    : 0,
        "damage_type" : "刺傷",
        "skill_name"  : "芙蓉花開"
]),
([      "action" :  "$N手中$w一抖，發出嗡嗡之聲，向$n眼睛刺去，但是$w在半路忽地一轉\n"
                    "竟向$n$l刺去，正是芙蓉劍法中的「花開花謝」",
        "force"  :  90,
        "dodge"  :  28,
        "parry"  :  40,
        "attack" :  24,
        "damage" :  35,
        "lvl"    :  25,
        "damage_type" : "刺傷",
        "skill_name"  : "花開花謝"
]),
([
        "action" : "$N不理會對方攻勢來路，手中$w刷的一劍「泉鳴芙蓉」，向$n$l刺去",
        "force"  : 110,
        "dodge"  : 32,
        "parry"  : 40,
        "attack" : 30,
        "damage" : 40,
        "lvl"    : 50,
        "damage_type" : "刺傷",
        "skill_name"  : "泉鳴芙蓉"
]),
([
        "action" : "$N手中$w倏地刺出，劍勢穿插迂迴，如夢如幻，正是一招「花香四溢」，向\n"
                   "$n$l刺去",
        "force"  : 120, 
        "dodge"  : 50,
        "parry"  : 42,
        "attack" : 35,
        "damage" : 48,
        "lvl"    : 75,
        "damage_type" : "刺傷",
        "skill_name"  : "花香四溢"
]),
([
        "action" : "$N手中$w倏地刺出，極盡詭奇之能事，動向無定，不可捉摸。正是一招\n"
                   "「借花獻佛」指向$n$l",
        "force"  : 150,
        "dodge"  : 75,
        "parry"  : 60,
        "attack" : 55,
        "damage" : 60,
        "lvl"    : 100,
        "damage_type" : "刺傷",
        "skill_name"  : "借花獻佛"
]),
([
        "action" : "$N飛身躍起，一式「芙蓉出水」$w發出一聲龍吟從半空中刺向$n的$l",
        "force"  : 180,
        "dodge"  : 85,
        "parry"  : 68,
        "attack" : 65,
        "damage" : 70,
        "lvl"    : 120,
        "damage_type" : "刺傷",
        "skill_name"  : "芙蓉出水"
]),
});

string main_skill()
{
        return "wushen-jian";
}

int valid_learn(object me)
{
            object ob; 

        if (me->query_skill("wushen-jian", 1) > 0)
                return notify_fail("你已演練合成了衡山五神劍，不必再單獨學習。\n");

            if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力不夠，沒有辦法練芙蓉劍法。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 60)
                   return notify_fail("你的基本劍法火候不夠，無法學習芙蓉劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("furong-jian", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的芙蓉劍法。\n");

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

        level = (int) me->query_skill("furong-jian", 1);
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
                   return notify_fail("你的內力不足，沒有辦法練習芙蓉劍法。\n");

       if( query("qi", me)<65 )
                   return notify_fail("你的體力不夠練芙蓉劍法。\n");

       me->receive_damage("qi", 40);
       addn("neili", -50, me);
       return 1;
}

string perform_action_file(string action)
{
        return __DIR__"furong-jian/" + action;
}


void skill_improved(object me)
{
        int lvl;

        lvl = me->query_skill("furong-jian", 1);
   

        if( lvl > 100 &&
            !query("can_perform/furong-jian/luan", me) ) 
        {
                tell_object(me, WHT "你通曉了芙蓉劍法「" HIC "亂劍覆花" WHT "」的奧祕。\n" NOR);    
                set("can_perform/furong-jian/luan", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
}

