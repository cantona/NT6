#include <ansi.h>
inherit SKILL;

mapping *action = ({
([ "action": "$N將身一縱，躍在半空，一式「彩鳳棲梧」，手中$w盤旋而下，鞭勢靈動之至，擊向$n$l",
   "dodge": -5,
   "damage":30,
   "force": 100,
        "attack": 90,
        "parry" : 60,
   "lvl" : 0,
   "skill_name" : "彩鳳棲梧",
        "damage_type": "抽傷"
]),
([ "action": "$N沉肩滑步，手中$w一抖，一式「鳳凰展翅」，迅捷無比地分打左右兩側，$n頓時左右支絀，慌了手腳",
   "dodge": 5,
   "damage":50,
   "force": 150,
        "attack": 90,
        "parry" : 60,
   "lvl" : 20,
   "skill_name" : "鳳凰展翅",
        "damage_type": "抽傷"
]),
([ "action": "$N將內力注入$w，驀地使出一式「蛟龍戲鳳」，$w矯夭飛舞，直如神龍破空一般抽向$n",
   "dodge": 10,
   "damage":80,
   "force": 200,
        "attack": 100,
        "parry" : 80,
   "lvl" : 40,
   "skill_name" : "蛟龍戲鳳",
        "damage_type": "抽傷"
]),
([ "action": "$N一聲清嘯，手中$w一招「龍飛鳳舞」，劃出漫天鞭影舖天蓋地地向$n卷來，勢道猛烈之極",
   "dodge": -10,
   "damage":110,
   "force": 250,
        "attack": 100,
        "parry" : 80,
   "lvl" : 60,
   "skill_name" : "龍飛鳳舞",
        "damage_type": "抽傷"
]),
([ "action": "$N面露微笑跨前一步，右手$w輕揚，緩緩使出一式「龍鳳呈祥」，鞭勢平和中正，不帶絲毫霸氣",
   "dodge": 1,
   "damage":130,
   "force": 300,
        "attack": 120,
        "parry" : 90,
   "lvl" : 80,
   "skill_name" : "龍鳳呈祥",
        "damage_type": "抽傷"
]),
});
int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;
   if( query("max_neili", me)<100 )
               return notify_fail("你的內力不足，沒有辦法練習鞭法, 多練些內力再來吧。\n");

       if ((int)me->query_skill("force") < 40)
               return notify_fail("你的內功火候太淺。\n");

       if( !objectp(weapon=query_temp("weapon", me) )
        || query("skill_type", weapon) != "whip" )
               return notify_fail("你必須先找一條鞭子才能練鞭法。\n");

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
       level   = (int) me->query_skill("leiming-bian",1);

        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       object weapon;

       if( !objectp(weapon=query_temp("weapon", me) )
        || query("skill_type", weapon) != "whip" )
               return notify_fail("你使用的武器不對。\n");
       if ((int)me->query_skill("force") < 100)
               return notify_fail("你的內功火候太淺。\n");
       if( query("jingli", me)<50 )
               return notify_fail("你的體力不夠練雷鳴鞭法。\n");
       addn("jingli", -15, me);
       return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        object weap,weap1;
        weap=query_temp("weapon", victim);
                weap1=query_temp("weapon", me);

                if( (me->query_skill("leiming-bian")>60) && (query("neili", me)>100 )
                          && (query_temp("weapon", victim) )
                         && random(10)>5)
                  {
                                                 message_vision(HIY "只見$N急速揮舞" + weap1->name() + "，轉出無數個大小圈子，以陰柔之勁纏住對方的" + weap->name() +"！\n" NOR, me );        
                                //                 message_vision(HIY "聽見「鏘」地一聲，$N手中的" + weap->name()
                //               + "被"+weap1->name()+"給纏住。\n" NOR, victim );
                         victim->start_busy(1);
                                                 if (random(me->query_str()) > victim->query_str()/2 )
                        {             
                                        message_vision(HIY "$N氣運手臂用力一拽，" + weap->name()
                                + "卻無法從"+weap1->name()+"的纏繞中脫開，情急之下只好放棄了手中的兵刃。\n" NOR, victim );
                        weap->move(environment(me));
                                                victim->reset_action();
                                                } else {
                                                message_vision(HIY "$N暗運巧勁，" + weap->name()
                                + "順著方向快速旋轉數下，解開了"+weap1->name()+"的纏繞。\n" NOR, victim );
                        addn("neili", -50, victim);
                                                }
                                                addn("neili", -50, me);
                 }
                                       return 1;

      
}

string perform_action_file(string action)
{
               return __DIR__"leiming-bian/" + action;
}
