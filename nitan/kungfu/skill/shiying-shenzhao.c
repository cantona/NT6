//shiying-shenzhao.c 弒鷹神爪
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"$N右手在$n$l劃過，隨後一招「鷹爪捉食」左爪又向同一方位抓到。",
        "force" :100,
        "attack":12,
        "dodge" :40,
        "damage":15,
        "lvl"   :0,
        "skill_name" :"鷹爪捉食",
        "damage_type":"抓傷"
]),
([      "action":"$N吐氣揚聲，一招「心隨鷹飛滅」雙手奔$n的頭頸搶去。",
        "force" :120,
        "attack":20,
        "dodge" :60,
        "damage":26,
        "lvl"   :20,
        "skill_name" :"心隨鷹飛滅",
        "damage_type":"抓傷"
]),
([      "action":"$N運起內功，一招「千瘡百孔」，身子騰空而起，雙爪齊向$n面門抓去。",
        "force" :150,
        "attack":35,
        "dodge" :70,
        "damage":40,
        "lvl"   :50,
        "skill_name" :"千瘡百孔",
        "damage_type":"抓傷"
]),
([      "action":"$N一招「翼若搏鷹」，屈腿越起，斜飛向右，左手力貫五指，飛快地抓向$n頭頂。",
        "force" :180,
        "attack":50,
        "dodge" :85,
        "damage":45,
        "lvl"   :80,
        "skill_name" :"翼若搏鷹",
        "damage_type":"抓傷"
]),
([      "action":"忽聽$N一聲輕叱，一招「穿針引線」，左手劃了個半弧，右手閃電般抓向$n的$l。",
        "force" :200,
        "attack":75,
        "dodge" :100,
        "damage":60,
        "lvl"   :150,
        "skill_name" :"穿針引線",
        "damage_type":"抓傷"
]),
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_learn(object me)
{
     if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
         return notify_fail("練弒鷹神爪必須空手。\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 100)
         return notify_fail("你的內功心法火候太淺，不能學弒鷹神爪。\n");

     if ((int)me->query_skill("claw", 1) < 100)
         return notify_fail("你的基本爪法火候不夠。\n");

     if( query("max_neili", me)<350 )
         return notify_fail("你的內力太低，無法學弒鷹神爪。\n");

     if ((int)me->query_skill("claw", 1) < (int)me->query_skill("shiying-shenzhao", 1))
         return notify_fail("你的基本爪法水平有限，無法領會更高深的弒鷹神爪。\n");

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
     level = (int) me->query_skill("shiying-shenzhao", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     object weapon;

     if( query_temp("weapon", me) || 
         query_temp("secondary_weapon", me) )
            return notify_fail("練弒鷹神爪必須空手。\n");

     if( query("qi", me)<70 )
            return notify_fail("你的體力不夠練弒鷹神爪。\n");

     if( query("neili", me)<80 )
            return notify_fail("你的內力不夠練弒鷹神爪。\n");

     me->receive_damage("qi", 65);
     addn("neili", -68, me);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"shiying-shenzhao/" + action;
}
