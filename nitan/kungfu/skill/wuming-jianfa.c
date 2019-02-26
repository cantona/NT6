// 無名劍法

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action":HIB"\n$N默唸 ≈幽≈,劍氣縱橫直直指向$n的$l"NOR,
        "force" : 160,
        "lvl" : 0,
"skill_name" : "★幽★字訣",
        "damage_type":        "刺傷"
]),
([      "action":HIR"\n$N默唸 ≈恨≈,劍氣縱橫直直指向$n的$l"NOR,
        "force" : 240,
        "lvl" : 50,
"skill_name" : "★恨★字訣",
        "damage_type":        "刺傷"
]),
([      "action":HIY"\n$N默唸 ≈怨≈,劍氣縱橫直直指向$n的$l"NOR,
        "force" : 280,
        "lvl" : 75,
"skill_name" : "★怨★字訣",
        "damage_type":        "刺傷"
]),
([      "action":HIM"\n$N默唸 ≈愛≈,劍氣縱橫直直指向$n的$l"NOR,
        "force" : 320,
        "lvl" : 120,
"skill_name" : "★愛★字訣",
        "damage_type":        "刺傷"
]),
([      "action":HIC"\n$N默唸 ≈思≈,劍氣縱橫直直指向$n的$l"NOR,
        "force" : 380,
        "lvl" : 230,
"skill_name" : "★思★字訣",
        "damage_type":        "刺傷"
]),
([      "action":HIG"\n$N默唸 ≈情≈,劍氣縱橫直直指向$n的$l"NOR,
        "force" : 420,
        "lvl" : 250,
"skill_name" : "★情★字訣",
        "damage_type":        "刺傷"
]),
([      "action":CYN"\n$N默唸 ≈恩≈,劍氣縱橫直直指向$n的$l"NOR,
        "force" : 450,
        "lvl" : 330,
"skill_name" : "★恩★字訣",
        "damage_type":        "刺傷"
]),
([      "action":HIR"\n$N默唸 ≈仇≈,劍氣縱橫直直指向$n的$l"NOR,
        "force" : 480,
        "lvl" : 380,
"skill_name" : "★仇★字訣",
        "damage_type":        "內傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
//           if ((int)me->query_skill("wudu-shengong", 1) < 20)
//                  return notify_fail("你的五毒神功火候太淺。\n");
        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("你的基本內功火候太淺。\n");
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
        mapping a_action;
        int i, level;
level   = (int) me->query_skill("wuming-jianfa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]){
                        a_action=action[NewRandom(i, 20, level/5)];
                       break;
                 }
    a_action["dodge"]  = 0-level/2;
    a_action["parry"]  = 0-level/2;
    a_action["damage"] = level/2;
    return a_action;
}


int practice_skill(object me)
{
        object weapon;

        return notify_fail("無名劍法博大精深，無法靠着普通的練習提升。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if((int)me->query_skill("wuming-jianfa",1) < 300)
                return notify_fail("你試着練習無名劍法,但是沒有任何進步。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的體力不夠練無名劍法。\n");
        me->receive_damage("qi", 20);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
  if( random(damage_bonus/2) > victim->query_con() ) {
                victim->receive_wound("qi", damage_bonus/ 3 );
        }
/*
  if( query("family/family_name", victim) != "五毒教" && me->query_skill("wudu-shengong",1)>80){
         switch( random(5) ) {
                case 0:
            victim->apply_condition("snake_poison", (me->query_skill("wudu-shengong"))/10 +
                        victim->query_condition("snake_poison"));
                        break;
                case 1:
            victim->apply_condition("zhizhu_poison", (me->query_skill("wudu-shengong"))/10 +
                        victim->query_condition("zhizhu_poison"));
                        break;
                case 2:
            victim->apply_condition("wugong_poison", (me->query_skill("wudu-shengong"))/10 +
                        victim->query_condition("wugong_poison"));
                        break;
                case 3:
            victim->apply_condition("xiezi_poison", (me->query_skill("wudu-shengong"))/10 +
                        victim->query_condition("xiezi_poison"));
                        break;
                case 4:
            victim->apply_condition("chanchu_poison", (me->query_skill("wudu-shengong"))/10 +
                        victim->query_condition("chanchu_poison"));
                        break;
        }
        return HIR "$n只覺得傷處一陣發麻，似乎中毒了。\n" NOR;
*/
   }
string perform_action_file(string action)
{
        return __DIR__"wuming-jianfa/" + action;
}

void skill_improved(object me)
{
        int lvl, i;

        i=query("int", me)/3;
        lvl = me->query_skill("wuming-jianfa", 1);

        if (lvl > 200
        &&  query("can_perform/wuming-jianfa/moming", me) <= 100 )
        {
                if( me->add("can_perform/wuming-jianfa/moming",random(i))<100 )
                {
                        tell_object(me, HIC "你對無名劍法「" HIW "劍動莫名"
                                        HIC "」有了新的領悟。\n" NOR);
                } else
                {
                        tell_object(me, HIC "你通曉了無名劍法「" HIW "劍"
                                        "動莫名" HIC "」的奧祕。\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }

}
