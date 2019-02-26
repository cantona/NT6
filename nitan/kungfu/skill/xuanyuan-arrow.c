// xuanyuan-arrow.c 軒轅箭
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

void throw_weapon(object,object,object,int);

mapping *action = ({
([
        "action": "$N忽然縱聲長嘯，橫躍於空，取箭上弦。\n"
"只聽弓弦響處，$w已到$n左肩，眼看就要對穿而過！\n"
"這招「李廣射石」果然有穿石之力",
        "damage":  25,
        "dodge":   -20,
        "parry":   10,
        "damage_type": "刺傷",
        "post_action": (: throw_weapon :),
        "name":      "聲東擊西",
]),
([
        "action": "$N弓交背後，俯身一招「廉頗負荊」，$w已帶呼嘯聲向$n前胸飛去",
        "damage":   35,
        "dodge":   20,
        "parry":   20,
        "damage_type":   "刺傷",
        "post_action":   (: throw_weapon :),
        "name":     "廉頗負荊",
]),
([
        "action": "突然間，$N幾個筋斗倒翻而去，已在$n數丈之外。\n"
"$n正待追擊，$N忽然轉身，好一個「百步穿楊」，\n"
"$w已帶着破空之聲，直射$n面門",
        "damage":   20,
        "dodge":       -10,
        "parry":       -10,
        "damage_type":   "刺傷",
        "post_action":   (: throw_weapon :),
        "name":     "百步穿楊",
]),
([
        "action": "$N力開長弓，瞄準$n的左臂虛晃一箭。\n"
"$n縱起閃避，突然發現並無羽箭射來。正在無處可去時，\n"
"$N彎弓搭箭，只見一支$w向$n的$l疾飛而至",
        "damage":   25,
        "dodge":       -20,
        "parry":   10,
        "damage_type":   "刺傷",
        "post_action":   (: throw_weapon :),
        "name":     "聲東擊西",
]),
([
        "action": "$N手指微動，$n只聽到「嗖」地一聲，$w已到$l前數寸。\n"
"$n沒放到這招「後翌落日」來勢如此之快，不禁手足無措",
        "damage":   35,
        "dodge":   10,
        "parry":       -10,
        "damage_type":   "刺傷",
        "post_action":   (: throw_weapon :),
        "name":     "後翌落日",
]),
([
        "action": "$N馬步站穩，勁力透背，拉的弓如滿月，$w飛一般衝向$n的$l",
        "damage":   40,
        "dodge":   20,
        "parry":   20,
        "damage_type":   "刺傷",
        "post_action":   (: throw_weapon :),
        "name":     "流星趕月",
]),
([
        "action": "$n縱身而起，正待凌空一擊。$N作勢似要逃跑，突然扭腰回身，\n"
"一招「犀牛望月」，手中$w如同長眼一般，直刺向$n的$l",
        "damage":       30,
        "dodge":       -10,
        "parry":       -10,
        "damage_type":  "刺傷",
        "post_action":  (: throw_weapon :),
        "name":       "犀牛望月",
]),
});

int valid_enable(string usage) { return (usage=="throwing"); }
int valid_learn(object me)
{
        object ob;

        if(me->query_skill("throwing",1) < 20)
                return notify_fail("如果弓箭不熟，怎能在激戰中上箭開弓射敵？\n");
        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("xuanyuan-arror", 1))
                return notify_fail("你的基本暗器水平有限，難以領會更精妙的射箭之術。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力不夠，拉不開弓！\n");
        if( !(ob=query_temp("weapon", me)) || 
                query("skill_type", ob) != "throwing" )
                return notify_fail("手中無弓箭怎能領悟師父所教？\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "throwing" )
                return notify_fail("沒有弓箭如何練準頭？\n");

        if( query("qi", me)<40 || query("force", me)<10 )
                return notify_fail("你的體力不足，拉不開弓！\n");
        me->receive_damage("qi", 30);
        addn("neili", -5, me);
        message_combatd("$N彎弓搭箭，一箭射中紅心！");
        (: throw_weapon :);
        return 1;
}
mapping query_action(object me)
{
        int max;

        if (!me) me = this_object();
        max=me->query_skill("throwing",1) / 15;
        if (max>sizeof(action)) max=sizeof(action);
        return action[random(max)];
}
string learning_message(int level)
{
        if (level / 15 >= sizeof(action) ) return "";
        else return "對「" + action[level/15]["name"] + "」這招有所領悟";
}
void throw_weapon(object me, object victim, object weapon, int damage)
{
        if( objectp(weapon) )
        {
                if( (int)weapon->query_amount()==1 )
                {
                        weapon->unequip();
                        tell_object(me,"\n你的"+query("name", weapon)+"用完了！\n");
                }
                weapon->add_amount(-1);
        }
}
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return __DIR__"xuanyuan-arrow/" + action;
}

int help(object me)
{
        write(HIC"\n軒轅箭："NOR"\n");
        write(@HELP

    軒轅箭為趙敏手下神箭八騎所具功夫。

        學習要求：
                基本暗器20級
                內力50
HELP
        );
        return 1;
}
