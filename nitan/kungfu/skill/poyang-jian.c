#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action":"$N使一式「力破天下」，手中$w由左至右橫掃向向$n的$l",
        "force" : 126,
        "parry" : 3,
        "dodge" : 5,
        "damage": 21,
        "lvl"   : 0,
        "skill_name" : "力破天下",
        "damage_type":  "割傷"
]),
([      "action":"$N踏上一步，「寒魄式」，手中$w盤旋飛舞出一道金光劈向$n的$l",
        "force" : 149,
        "parry" : 13,
        "dodge" : 10,
        "damage": 25,
        "lvl"   : 30,
        "skill_name" : "寒魄式",
        "damage_type":  "割傷"
]),
([      "action":"$N手中$w一抖，一招「天降式」，斜斜反腕撩出，攻向$n的$l",
        "force" : 167,
        "parry" : 12,
        "dodge" : 15,
        "damage": 31,
        "lvl"   : 50,
        "skill_name" : "天降式",
        "damage_type":  "割傷"
]),
([      "action":"$N手中$w連繞數個大圈，一式「龍舞九天」，一道光飛向$n的$l",
        "force" : 187,
        "parry" : 23,
        "dodge" : 19,
        "damage": 45,
        "lvl"   : 70,
        "skill_name" : "龍舞九天",
        "damage_type":  "刺傷"
]),
([      "action":"$N手中$w斜指蒼天，一式「天罡式」，對準$n的$l斜斜擊出",
        "force" : 197,
        "parry" : 31,
        "dodge" : 27,
        "damage": 56,
        "lvl"   : 90,
        "skill_name" : "天罡式",
        "damage_type":  "刺傷"
]),
([      "action":"$N一式「冷兵出鞘」，$w飛斬盤旋，如疾電般射向$n的胸口",
        "force" : 218,
        "parry" : 49,
        "dodge" : 35,
        "damage": 63,
        "lvl"   : 110,
        "skill_name" : "冷兵出鞘",
        "damage_type":  "刺傷"
]),
([      "action":"$N手中$w一沉，一式「破光式」，無聲無息地滑向$n的$l",
        "force" : 239,
        "parry" : 52,
        "dodge" : 45,
        "damage": 72,
        "lvl"   : 130,
        "skill_name" : "破光式",
        "damage_type":  "刺傷"
]),
([      "action":"$N手中$w斜指蒼天，劍芒吞吐，一式「天孤冷月式」，對準$n的$l斜斜擊出",
        "force" : 257,
        "parry" : 55,
        "dodge" : 51,
        "damage": 88,
        "lvl"   : 150,
        "skill_name" : "天孤冷月式",
        "damage_type":  "刺傷"
]),
([      "action":"$N左指凌空虛點，右手$w逼出丈許雪亮光芒，一式「劍氣縱橫」刺向$n的嚥喉",
        "force" : 282,
        "parry" : 63,
        "dodge" : 55,
        "damage": 105,
        "lvl"   : 170,
        "skill_name" : "劍氣縱橫",
        "damage_type":  "刺傷"
]),
([      "action":"$N合掌跌坐，一式「破陽無極」，$w自懷中躍出，如疾電般射向$n的胸口",
        "force" : 335,
        "parry" : 76,
        "dodge" : 55,
        "damage": 122,
        "lvl"   : 190,
        "skill_name" : "破陽無極",
        "damage_type":  "刺傷"
])
});

int valid_enable(string usage)
{ 
       return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        object weapon;
        int lv = me->query_skill("poyang-jian", 1);

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，不能學習破陽冷光劍。\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("你的內力修為不夠，不能學習破陽冷光劍。\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候不夠，不能學習破陽冷光劍。\n");

        if ((int)me->query_skill("sword", 1) < lv)
                return notify_fail("你的基本劍法水平有限，無法領會更高深的破陽冷光劍。\n");

        if ((int)me->query_skill("sword", 1) < lv)
                return notify_fail("你的基本刀劍水平有限，無法領會更高深的破陽冷光劍。\n");

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
        level = (int) me->query_skill("poyang-jian", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的體力不夠練破陽冷光劍。\n");

        if( query("neili", me)<130 )
                return notify_fail("你的內力不夠練破陽冷光劍。\n");

        me->receive_damage("qi", 80);
        addn("neili", -100, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"poyang-jian/" + action;
}

void skill_improved(object me)
{
        int lvl;

        lvl = me->query_skill("poyang-jian", 1);

        if( lvl > 120 &&
            !query("can_perform/poyang-jian/xian", me) ) 
        {
                tell_object(me, WHT "你通曉了破陽冷光劍「" HIY "神光再現" WHT "」的奧秘。\n" NOR);    
                set("can_perform/poyang-jian/xian", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
        }
        
        if( lvl > 180 &&
            !query("can_perform/poyang-jian/long", me) ) 
        {
                tell_object(me, WHT "你通曉了破陽冷光劍「" HIC "天外玉龍" WHT "」的奧秘。\n" NOR);    
                set("can_perform/poyang-jian/long", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
}
