// jingang-zhi.c - 少林大力金剛指
       
inherit SHAOLIN_SKILL;
        
mapping *action = ({
([     "action": "$N身體半蹲，右指中宮直進，一式「降龍伏虎」擊向$n的$l",
       "force" : 80,
       "attack": 20,
       "parry" : 20,
       "dodge" : -5,
       "damage": 20,
       "lvl"   : 0,
       "skill_name" : "降龍伏虎",
       "damage_type" : "刺傷"
]),
([     "action": "$N輕輕一縱，居高臨下，一式「普渡眾生」，點向$n的周身大穴",
       "force" : 100,
       "attack": 40,
       "parry" : 15,
       "dodge" : 0,
       "damage": 25,
       "lvl"   : 40,
       "skill_name" : "普渡眾生",
       "damage_type" : "刺傷"
]),
([     "action": "$N身形飄忽不定，一式「佛祖獻花」，右指擊向$n的$l",
       "force" : 110,
       "attack": 30,
       "parry" : 25,
       "dodge" : -5,
       "damage": 30,
       "lvl"   : 80,
       "skill_name" : "佛祖獻花",
       "damage_type" : "刺傷"
]),
([     "action": "$N不動聲色，突然一招「斬妖除魔」，左右雙指分別指向$n的各大要穴",
       "force" : 150,
       "attack": 40,
       "parry" : 25,
       "dodge" : -10,
       "damage": 120,
       "lvl"   : 60,
       "skill_name" : "斬妖除魔",
       "damage_type" : "刺傷"
]),
([     "action": "$N摒指如刀，一招「五丁開山」，雙指呈刀勢從意想不到的角度劈向$n",
       "force" : 180,
       "attack": 50,
       "parry" : 30,
       "dodge" : -15,
       "damage": 160,
       "lvl"   : 80,
       "skill_name" : "五丁開山",
       "damage_type" : "割傷"
]),
([     "action": "$N盤膝端坐，一招「佛法無邊」，右手拇指彈出一道勁風，擊向$n",
       "force" : 160,
       "attack": 60,
       "parry" : 30,
       "dodge" : 5,
       "damage": 100,
       "lvl"   : 200,
       "skill_name" : "佛法無邊",
       "damage_type" : "刺傷"
]),
([     "action": "$N縱身而上，一招「金剛伏魔」，雙手食指端部各射出一道青氣擊向$n",
       "force" : 180,
       "attack": 60,
       "parry" : 40,
       "dodge" : -5,
       "damage": 120,
       "lvl"   : 225,
       "skill_name" : "金剛伏魔",
       "damage_type" : "刺傷"
]),
([     "action": "$N臉上忽現祥和之氣，一招「無色無相」，一指遙遙指向$n，似乎毫無勁力",
       "force" : 200,
       "attack": 70,
       "parry" : 50,
       "dodge" : 15,
       "damage": 180,
       "lvl"   : 250,
       "skill_name" : "無色無相",
       "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; } 
     
int valid_combine(string combo) { return combo == "xumishan-zhang"; } 
      
int valid_learn(object me) 
{ 
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練大力金剛指必須空手。\n"); 
      
        if ((int)me->query_skill("force") < 60) 
                return notify_fail("你的內功火候不夠，無法學大力金剛指。\n"); 
     
        if( query("max_neili", me)<300 )
                return notify_fail("你的內力太弱，無法練大力金剛指。\n"); 
      
        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("jingang-zhi", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的大力金剛指。\n"); 
      
        return 1; 
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
        level = (int) me->query_skill("jingang-zhi", 1); 
        for (i = sizeof(action); i > 0; i--) 
                if (level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)]; 
} 
      
int practice_skill(object me) 
{ 
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n"); 
      
        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練大力金剛指。\n"); 
      
        me->receive_damage("qi", 60); 
        addn("neili", -64, me);
        return 1; 
} 
      
string perform_action_file(string action) 
{ 
        return __DIR__"jingang-zhi/" + action; 
} 