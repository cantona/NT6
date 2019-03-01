
// wushen-jian.c 衡山五神劍
// 由衡山派紫蓋劍法、芙蓉劍法、石廩劍法、祝融劍法、天柱劍
// 法合一所創，B+級器械武學。

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      
        "action" : "$N反轉手中$w，劍光奪目，將「" HIR "祝融劍法" NOR
                   "」發揮得淋漓盡致，閃電般射向$n",
        "force" : 430,
        "attack": 147,
        "dodge" : 96,
        "parry" : 128,
        "damage": 190,
        "damage_type" : "刺傷",
]),
([ 
        "action" : "$N手中劍花突現，頓時劍光暴長，已將「" HIM "芙蓉劍"
                   "法" NOR "」使出，直刺$n的$l",
        "force" : 420,
        "attack": 154,
        "dodge" : 118,
        "parry" : 120,
        "damage": 210,
        "damage_type" : "刺傷",
]),
([
        "action" : "$N將$w一揮，長嘯一聲騰空而起，一式「" HIY "鶴翔紫"
                   "蓋" NOR "」，$w已指向$n$l",
        "force" : 420,
        "attack": 156,
        "dodge" : 100,
        "parry" : 120,
        "damage": 223,
        "damage_type" : "刺傷",
]),
([
        "action" : "$N輕嘯一聲，右手$w虛刺$n左眼，突然右腕翻轉，將「" HIG 
                   "石廩劍法" NOR "」的精髓發揮到了極致",
        "force" : 430,
        "attack": 160,
        "dodge" : 120,
        "parry" : 140,
        "damage": 248,
        "damage_type" : "刺傷",
]),
([
        "action" : "$N手中$w劍路忽快忽慢，若隱若現，一劍「" HIW "天柱雲氣"
                   NOR "」猶如煙霧飄渺般使了出來",
        "force" : 480,
        "attack": 180,
        "dodge" : 140,
        "parry" : 160,
        "damage": 260,
        "damage_type" : "刺傷",
]),
});

string main_skill()
{
        return "wushen-jian";
}

mapping sub_skills = ([
        "zigai-jian"   : 180,
        "furong-jian"  : 180,
        "shilin-jian"  : 180,
        "zhurong-jian" : 180,
        "tianzhu-jian" : 180,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;
        me = this_player();

        if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
        {
                tell_object(me, "你空手舞了半天，發現如果不用劍實在難以演練。\n");
                return 0;
        }

        if( query("int", me)<30 )
        {
                tell_object(me, "你演練完畢，只感五種劍法毫無牽連，看來依你的悟"
                                "性，無法將其合一。\n");
                return 0;
        }

        if( query("dex", me)<28 )
        {
                tell_object(me, "你演練完畢，只覺依自己的身法靈動性，根本無法將"
                                "五種劍法合一。\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 150)
        {
                tell_object(me, "你演練完畢，發現自己的武學修養尚待提高，暫且無"
                                "法將五種劍法合一。\n");
                return 0;
        }

        if( query("max_neili", me)<3200 )
        {
                tell_object(me, "你突然覺得真氣不繼，看來依自己的內力修為，無法"
                                "將五種劍法合一。\n");
                return 0;
        }

        if (random(20) < 17)
        {
                tell_object(me, "你覺得有所感悟，或許再演練一次就能融會貫通，將"
                                "五種劍法合一。\n");
                return 0;
        }

        tell_object(me, HIY "\n一陣凡塵往事湧上心頭，你幾欲放聲長嘆。霎那間衡山"
                        "派五種劍法不斷在\n你的腦海裡交替閃現，最後終于融會貫通"
                        "，合為一體。你終于通曉了衡山\n五神劍的訣竅。\n" NOR);
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        object ob;

        if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一柄劍才能夠練習。\n");

        if( query("int", me)<30 )
                return notify_fail("你的先天悟性不足，沒有辦法練衡山五神劍。\n");

        if( query("dex", me)<28 )
                return notify_fail("你的先天身法孱弱，沒有辦法練衡山五神劍。\n");

        if (me->query_skill("martial-cognize", 1) < 180)
                return notify_fail("你覺得衡山五神劍極其深奧，依照自己的武學修養"
                                   "難以理解。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的內力修為不夠，沒有辦法練衡山五神劍。\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("你的基本劍法太差，沒有辦法練衡山五神劍。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("wushen-jian", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的衡山五神劍。\n");

        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

int practice_skill(object me)
{
        int cost;

        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n");

        cost = me->query_skill("wushen-jian", 1) / 2 + 60;

        if( query("neili", me)<cost )
                return notify_fail("你的內力不夠練衡山五神劍。\n");

        me->receive_damage("qi", 60);
        addn("neili", -cost, me);
        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}
void skill_improved(object me)
{
        int i,lvl;
        string *sub_skillnames;

        lvl = me->query_skill("wushen-jian", 1);
           if( lvl > 180 &&
            !query("can_perform/wushen-jian/hui", me) ) 
        {
                tell_object(me, WHT "你通曉了衡山五神劍「" HIC "回峰蜿蜒勢" WHT "」的奧秘。\n" NOR);    
                set("can_perform/wushen-jian/hui", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
            if( lvl > 200 &&
            !query("can_perform/wushen-jian/qian", me) ) 
        {
                tell_object(me, WHT "你通曉了衡山五神劍「" HIC "千劍縱橫勢" WHT "」的奧秘。\n" NOR);    
                set("can_perform/wushen-jian/qian", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
            if( lvl > 240 &&
            !query("can_perform/wushen-jian/shen", me) ) 
        {
                tell_object(me, WHT "你通曉了衡山五神劍「" HIC "五神朝元勢" WHT "」的奧秘。\n" NOR);    
                set("can_perform/wushen-jian/shen", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
        sub_skillnames = keys(sub_skills);

        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames[i]);
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon;
        int i;

        lvl = me->query_skill("wushen-jian", 1);

        if (damage_bonus < 135
            || query("neili", me)<300
           || me->query_skill_mapped("sword") != "wushen-jian"
           || random(3) != 1)
                     return 0;

        if( !query_temp("weapon", me))return 0;
        switch(random(4))
        {
           case 1:
              if (damage_bonus / 5 > victim->query_con())
              {
                  addn("neili", -100, me);
                  victim->receive_wound("qi", (damage_bonus - 54) / 2, me);
                  
                  return random(2) ? HIW "$N" HIW "一劍攻出，剎那間劍氣橫飛，$n" HIW
                                     "身上頓時鮮血狂湧。\n" NOR:
                                     HIW "$N" HIW "劍鋒一轉，一劍平平刺向$n" HIW "要害"
                                     "，看似普通的一招其中卻蘊藏著極大的殺著。\n" NOR;
             }
             break;

          case 2:
             if (random(me->query_skill("sword") / 2) + me->query_skill("sword")
                 > victim->query_skill("dodge"))
             {
                  weapon=query_temp("weapon", me);
                  if (!victim->is_busy())
                  victim->start_busy(2 + random(lvl / 60));
                  return   HIC "$N" HIC "劍法陡然變快，手中" + weapon->name() + HIC "劍光奪目，"
                           "將$n" HIC "籠罩在劍光之中。\n" NOR;
             }
             break;

          case 3:
             if (lvl > 220 && random(lvl / 2) + lvl > victim->query_skill("parry", 1)
                  && random(2) == 1 && !query_temp("perform_wushenjian/qian", me) )
             {
                weapon=query_temp("weapon", me);
                message_sort(HIM "\n$N" HIM "輕嘯一聲，騰空而起，" + weapon->name() + "在"
                             "空中挽出一個劍花，頃刻間劍花四散，洋洋洒洒。猶如無"
                             "數花瓣從半空洒向$n" HIM "全身。\n" NOR, me, victim);

                for (i = 0; i < 5; i++)
                {
                    if (! me->is_fighting(victim))
                            break;
                   
                    if (! victim->is_busy() && random(2) == 1)
                            victim->start_busy(1);

                    COMBAT_D->do_attack(me, victim, weapon, 0);
                }                
                
             }
             break;                        

          default:
                return 0;
       }
}

int difficult_level()
{
        return 700;
}

string perform_action_file(string action)
{
        return __DIR__"wushen-jian/" + action; 
}
