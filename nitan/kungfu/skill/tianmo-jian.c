//tianmo-jian.c 天魔劍法
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"$N手中$w一抖，幻化出滿天劍影，一招「日月輝煌」恰似滿天風雪罩向$n。",
        "force" :210,
        "attack":160,
        "dodge" :80,
        "parry" :110,
        "damage":150,
        "lvl"   :0,
        "skill_name" :"日月輝煌",
        "damage_type":"刺傷"
]),
([      "action":"$N悄然一笑，身形急旋，仿佛飛蝶戲花一般，繞著$n遊走，手中$w使出一招「碧苔芳暉」接連向$n刺出五劍。",
        "force" :230,
        "attack":175,
        "dodge" :90,
        "parry" :150,
        "damage":190,
        "lvl"   :30,
        "skill_name" :"碧苔芳暉",
        "damage_type":"刺傷"
]),
([      "action":"$N大步向前，姿勢飄逸，如飛燕掠過長空，一招「海天一線」手中的$w電光一閃，刺向$n。",
        "force" :250,
        "attack":190,
        "dodge" :110,
        "parry" :160,
        "damage":190,
        "lvl"   :80,
        "skill_name" :"海天一線",
        "damage_type":"刺傷"
]),
([      "action":"$N一挽手中$w，使出一招「鳳舞九天」只見$N吐聲發力，$w向$n點去，一股勁氣夾著「啪、啪」的聲音向$n卷去。",
        "force" :280,
        "attack":210,
        "dodge" :120,
        "parry" :180,
        "damage":220,
        "lvl"   :110,
        "skill_name" :"鳳舞九天",
        "damage_type":"刺傷"
]),
([      "action":"$N腳步遊移不定，倒轉手中$w，身行如燕直沖而起，一式「微雨燕雙飛」自上而下直向$n撲來。",
        "force" :320,
        "attack":230,
        "dodge" :150,
        "parry" :200,
        "damage":190,
        "lvl"   :150,
        "skill_name" :"微雨燕雙飛",
        "damage_type":"刺傷"
]),
([      "action":"$N心底空明，劍隨心意，身行傲然拔起，正是「空翠落庭陰」。$n為$N氣勢所逼，不住倒退。",
        "force" :330,
        "attack":220,
        "dodge" :180,
        "parry" :220,
        "damage":210,
        "lvl"   :180,
        "skill_name" :"空翠落庭陰",
        "damage_type":"割傷"
]),
([      "action":"只見$N手中$w發出龍吟之聲，陰陽相和，高聲琨，正聲緩，一招「壯氣蒿萊」，劍鋒直向$n左肩刺過去。",
        "force" :340,
        "attack":250,
        "dodge" :200,
        "parry" :210,
        "damage":220,
        "lvl"   :210,
        "skill_name" :"壯氣蒿萊",
        "damage_type":"刺傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
     object weapon;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "sword" )
         return notify_fail("你必須裝備劍才能學習劍法。\n");

     if ((int)me->query_skill("xixing-dafa", 1) < 150)
         return notify_fail("你的吸星大法還未大成，不能學習天魔劍法。\n");

     if ((int)me->query_skill("sword", 1) < 130)
         return notify_fail("你的基本劍法火候不夠。\n");

     if ((int)me->query_skill("sword", 1) < (int)me->query_skill("tianmo-jian", 1))
         return notify_fail("你的基本劍法水平有限，無法領會更高深的天魔劍法。\n");

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
     level = (int) me->query_skill("tianmo-jian", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     object weapon;
     int cost;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "sword" )
         return notify_fail("你必須裝備劍才能練劍法。\n");

     if( query("qi", me)<160 )
         return notify_fail("你的體力太低了。\n");

     cost = me->query_skill("tianmo-jian", 1) / 2 + 100;
     if( query("neili", me)<cost )
         return notify_fail("你的內力不夠練「天魔劍法」。\n");

     me->receive_damage("qi", 130);
     addn("neili", -cost, me);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"tianmo-jian/" + action;
}
