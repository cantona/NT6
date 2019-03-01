#include <ansi.h>
#include <skill.h>

inherit SKILL;

string *xue_name = ({ 
"勞宮穴", "膻中穴", "曲池穴", "關元穴", "曲骨穴", "中極穴", "承漿穴", "天突穴", "百會穴",
"幽門穴", "章門穴", "大橫穴", "紫宮穴", "冷淵穴", "天井穴", "極泉穴", "清靈穴", "至陽穴", }); 

mapping *action_unarmed = ({
([      "action": "$N使一招「弦外有音」，雙手猛然擊出，空氣中暴響出“嗚”的一聲，一股氣流如風一般卷向$n的$l",
        "force" : 350,
        "attack": 80,
        "dodge" : 75,
        "parry" : 55,
        "damage": 70,
        "lvl" : 0,
        "weapon" : HIW "無形劍氣" NOR,
        "skill_name" : "弦外有音",
        "damage_type" : "刺傷"
]),
([      "action": "$N使出一招「吳陽琴音」，彈指向上一刺，接著再向下直劃而出，頓時兩股劍氣如利刀般砍向$n",
        "force" : 370,
        "attack": 81,
        "dodge" : 65,
        "parry" : 65,
        "damage": 72,
        "lvl" : 40,
        "weapon" : HIW "無形劍氣" NOR,
        "skill_name" : "吳陽琴音",
        "damage_type" : "刺傷"
]),
([      "action": "$N一聲暴喝，陡然一招「天河紫氣」，單手向$n凌空一劈，頓時一股勁氣伴隨著破空之聲襲向$p$l",
        "force" : 410,
        "attack": 85,
        "dodge" : 55,
        "parry" : 55,
        "damage": 88,
        "lvl" : 80,
        "weapon" : HIW "無形劍氣" NOR,
        "skill_name" : "天河紫氣",
        "damage_type" : "刺傷"
]),
([      "action": "$N雙掌繽紛拍出，勁氣縱橫，正是一式「七盤絕剎」，剎時“颼颼”破空聲悠然而響，擊向$n$l",
        "force" : 430,
        "attack": 79,
        "dodge" : 65,
        "parry" : 35,
        "damage": 83,
        "lvl" : 120,
        "weapon" : HIW "破體無形劍氣" NOR,
        "skill_name" : "七盤絕剎",
        "damage_type" : "刺傷"
]),
([      "action": "$N憑空一指，一招「黃龍吐珠」斜斜襲出，手掌陡然生出半寸吞吐不定的青芒刺向$n的$l",
        "force" : 460,
        "attack": 75,
        "dodge" : 91,
        "parry" : 85,
        "damage": 78,
        "lvl" : 160,
        "weapon" : HIW "破體無形劍氣" NOR,
        "skill_name" : "黃龍吐珠",
        "damage_type" : "刺傷"
]),
([      "action": "$N雙手向外一分，使一招「清心普善」，手若撥琴弄蕭，彈射出一股破體劍氣，直湧$n$l而去",
        "force" : 490,
        "attack": 105,
        "dodge" : 35,
        "parry" : 24,
        "damage": 98,
        "lvl" : 200,
        "weapon" : HIW "破體無形劍氣" NOR,
        "skill_name" : "清心普善",
        "damage_type" : "刺傷"
]),
([      "action": "$N忽然眼中精光四射，一招「星河氣旋」使出，頓時數股淳厚無比的劍氣從指尖激射而出，直逼$n",
        "force" : 480,
        "attack": 95,
        "dodge" : 75,
        "parry" : 75,
        "damage": 93,
        "lvl" : 240,
        "weapon" : HIW "破體無形劍氣" NOR,
        "skill_name" : "星河氣旋",
        "damage_type" : "刺傷"
]),
});


mapping *action_sword = ({
([      "action": "$N使一招「弦外有音」，手中$w彈出一股氣流，如風一般卷向$n的$l",
        "force" : 140,
        "attack": 60,
        "dodge" : 15,
        "parry" : 25,
        "damage" : 50,
        "lvl" : 0,
        "damage_type" : "刺傷",
]),
([      "action": "$N伸指在$w上一彈，一招「吳陽琴音」，整個劍身頓時發出一聲龍吟，呼嘯著斬向$n的$l",
        "force" : 150,
        "attack": 80,
        "dodge" : 60,
        "parry" : 5,
        "damage" : 70,
        "lvl" : 40,
        "damage_type" : "內傷",
]),
([      "action": "$N一招「天河紫氣」，手中$w劍芒頓時暴長數尺，光華四射，直直削向$n的$l",
        "force" : 200,
        "attack": 80,
        "dodge" : 0,
        "parry" : 10,
        "damage" : 90,
        "lvl" : 80,
        "damage_type" : "割傷",
]),
([      "action": "$N手中$w一式「七盤絕剎」對準$n的$l一連刺出數劍，剎時劍氣縱橫，勢不可擋",
        "force" : 250,
        "attack": 80,
        "dodge" : 10,
        "parry" : 15,
        "damage" : 92,
        "lvl" : 120,
        "damage_type" : "刺傷",
]),
([      "action": "$N的$w憑空一指，一招「黃龍吐珠」直直刺出，劍尖陡然生出半寸吞吐不定的青芒刺向$n的$l",
        "force" : 225,
        "attack": 63,
        "dodge" : 5,
        "parry" : 5,
        "damage" : 103,
        "lvl" : 160,
        "damage_type" : "刺傷",
]),
([      "action": "$N手中$w向外一分，使一招「清心普善」，單手在劍身輕輕彈撥，頓時一股劍氣直湧$n$l而去",
        "force" : 250,
        "attack": 80,
        "dodge" : 10,
        "parry" : 5,
        "damage" : 120,
        "lvl" : 200,
        "damage_type" : "刺傷",
]),
([      "action": "$N忽然眼中精光四射，一招「星河氣旋」，一股淳厚無比的劍氣從$w上激射而出，直逼$n",
        "force" : 300,
        "attack": 100,
        "dodge" : -15,
        "parry" : -15,
        "damage" : 140,
        "lvl" : 240,
        "damage_type" : "刺傷",
]),
});

int valid_enable(string usage) 
{  
        return usage == "unarmed"
            || usage == "parry"
            || usage == "sword"
            || usage == "tanqin-jifa"; 
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 270)
                return notify_fail("你的內功火候不夠，無法修煉七弦無形劍。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力太弱，無法修煉七弦無形劍。\n");

        if ((int)me->query_skill("unarmed", 1) < 180)
                return notify_fail("你的基本拳腳火候不夠，無法修煉七弦無形劍。\n");

        if ((int)me->query_skill("sword", 1) < 180)
                return notify_fail("你的基本劍法火候不夠，無法修煉七弦無形劍。\n");

        if ((int)me->query_skill("tanqin-jifa", 1) < 100)
                return notify_fail("彈琴技法水平有限，無法修煉七弦無形劍。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("qixian-wuxingjian", 1))
                return notify_fail("你的內功修為有限，無法領會更高深的七弦無形劍。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("qixian-wuxingjian", 1))
                return notify_fail("你的基本拳腳水平有限，無法領會更高深的七弦無形劍。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("qixian-wuxingjian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的七弦無形劍。\n");

        if ((int)me->query_skill("tanqin-jifa", 1) < (int)me->query_skill("qixian-wuxingjian", 1) / 2)
                return notify_fail("你對琴學的了解不夠深入，無法領會更高深的七弦無形劍。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action_unarmed)-1; i >= 0; i--)
                if(level >= action_unarmed[i]["lvl"])
                        return action_unarmed[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("qixian-wuxingjian", 1);

        if ( ! weapon)
        {                
             for(i = sizeof(action_unarmed); i > 0; i--)
                     if(level >= action_unarmed[i-1]["lvl"])
                             return action_unarmed[NewRandom(i, 20, level/5)];
        }        
        else
             for(i = sizeof(action_sword); i > 0; i--)
                     if(level > action_sword[i-1]["lvl"])
                             return action_sword[NewRandom(i, 20, level/5)];        
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練七弦無形劍！\n");

        if( query("neili", me)<120 )
                return notify_fail("你的內力不夠練七弦無形劍！\n");

        me->receive_damage("qi", 60);
        addn("neili", -100, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name, weapon;
        name = xue_name[random(sizeof(xue_name))];
    
        if (me->query_skill("qixian-wuxingjian", 1) < 180
            || query("max_neili", me)<2500
            || query("neili", me)<500
            || query("max_neili", me)<query("max_neili", victim )
            || query("max_neili", victim)<10 )
                return 0;

        if (victim->is_busy())
                return 0;

        if (damage_bonus < 150)
                return 0;

        victim->start_busy(1);
        addn("neili", -100, me);
        victim->receive_damage("qi", me->query_skill("qixian-wuxingjian", 1) / 5 + damage_bonus / 3);
        victim->receive_wound("qi", me->query_skill("qixian-wuxingjian", 1) / 8 + damage_bonus / 5);
                return HIW "只聽一陣淳厚的弦音從$N" HIW "處傳來，$n" HIY "『" + name + "』"
                       NOR + HIW "頓時受震，兩耳轟鳴，全身真氣亂竄不止！\n" NOR;
}

void do_effect(object me)
{
        object *obs;
        int lvl;
        int i;
        int damage;

        lvl = me->query_skill("tanqin-jifa", 1) / 2 +
              me->query_skill("qixian-wuxingjian", 1);

        if( query("no_fight", environment(me) )
            || query("skybook", environment(me) )
           || lvl < 150)
                return;

        lvl = lvl / 5 + me->query_skill("force");
        lvl /= 2;

        obs = all_inventory(environment(me));
        for (i = 0; i < sizeof(obs); i++)
        {
                if (! obs[i]->is_character() || obs[i] == me || ! living(obs[i]))
                        continue;

                if (me->query_skill("qixian-wuxingjian") * 2 / 3 <
                    obs[i]->query_skill("qixian-wuxingjian"))
                        continue;

                // 被死亡保護的玩家不受傷害
                if ((int)obs[i]->query_condition("die_guard"))
                        continue;

                if( query("max_neili", obs[i])<10 )
                {
                        tell_object(obs[i], HIM "你聽後只覺得這首曲子平平常常，沒半點特殊之處。\n" NOR);
                        continue;
                }

                if( query("max_neili", obs[i])+500>query("max_neili", me) )
                {
                        tell_object(obs[i], HIM "你聽後只覺心頭一緊，可是自己內力深厚，絲毫不受影響。\n" NOR);
                        continue;
                }

                if (lvl + random(lvl) < obs[i]->query_skill("force"))
                {
                        tell_object(obs[i], HIM "你聽了心中不禁微微一動，發現這曲子頗有奧妙之處。\n" NOR);
                        continue;
                }

                damage=query("max_neili", me)-query("max_neili", obs[i]);
                if (damage < 500)
                {
                        tell_object(obs[i], HIM "你忽然覺得一陣迷亂，連忙運了一口氣，才清醒過來。\n" NOR);
                        continue;
                }

                damage /= 10;
                me->want_kill(obs[i]);
                me->fight_ob(obs[i]);
                obs[i]->kill_ob(me);
                obs[i]->receive_damage("jing", damage / 2, me);
                obs[i]->receive_wound("jing", damage / 2, me);
                obs[i]->receive_damage("qi", damage * 2, me);
                obs[i]->receive_wound("qi", damage * 2, me);
                
                tell_object(obs[i], HIR "你聽得心神不定，只感呼吸不暢，鼓膜轟鳴，目不視物，幾欲暈倒。\n" NOR);
        }
}

string perform_action_file(string action)
{
      return __DIR__"qixian-wuxingjian/" + action;
}