// weituo-zhang.c 韋馱掌

inherit SHAOLIN_SKILL;

mapping *action = ({
([        "action" : "$N雙眼微睜，袍袖微微鼓氣，雙掌齊推，一招「開天闢地」，一股排山之勢壓向$n",
        "force" : 170,
        "parry" : 5,
        "lvl" : 0,
        "skill_name" : "開天闢地",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N口中阿彌陀佛，一招「即世即空」，左掌擊向$n面門，另一掌卻按向$n的小腹",
        "force" : 200,
        "parry" : 10,
        "lvl" : 15,
        "skill_name" : "即世即空",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N雙掌互錯，變幻莫測，一招「無相無色」，瞬息之間向$n攻出了三四一十二招",
        "force" : 230,
        "parry" : 15,
        "lvl" : 30,
        "skill_name" : "無相無色",
        "damage_type" : "瘀傷",
]),
([        "action" : "$N呼的一掌，沒有半點徵兆，一招「佛法無邊」，猛地向$n的$l擊打過去",
        "force" : 260,                                    
        "parry" : 20,
        "lvl" : 40,
        "skill_name" : "佛法無邊",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N雙掌交錯，若有若無，一招「誰入地獄」，帶着勁風拍向$n的肩頭和前胸",
        "force" : 310,
        "parry" : 25,
        "lvl" : 50,
        "skill_name" : "誰入地獄",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一招「禪心永明」，右手一掌擊出，緊接着右掌上一搭，擊向$n的$l",
    "force" : 340,
        "parry" : 30,
        "lvl" : 60,
        "skill_name" : "禪心永明",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N雙手在空中齊劃，跟着雙掌齊推，一招「我佛慈悲」，一股排山倒海的掌力，直撲$n面門",
    "force" : 380,
        "parry" : 35,
        "lvl" : 70,
        "skill_name" : "我佛慈悲",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N突然身行急轉，一招「苦海回頭」，掌影飛舞，霎時之間將$n四面八方都裹住了",
    "force" : 410,
        "parry" : 40,
        "lvl" : 80,
        "skill_name" : "苦海回頭",
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }


int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練韋馱掌必須空手。\n");
        if ((int)me->query_skill("hunyuan-yiqi", 1) < 100)
        return notify_fail("你的心意氣混元功火候不夠，無法練韋馱掌。\n");
        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力太弱，無法練韋馱掌。\n");
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
        level   = (int) me->query_skill("weituo-zhang",1);
                  for(i = sizeof(action); i > 0; i--)
                  if(level > action[i-1]["lvl"])
                  return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("jing", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練韋馱掌。\n");
        me->receive_damage("jing", 25);
        addn("neili", -10, me);
        return 1;
  }
