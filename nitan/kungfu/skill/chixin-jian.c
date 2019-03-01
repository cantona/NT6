// chixin-jian.c 痴心情長劍
// Made by deaner
// Modified by Venus Oct.1997

#include <ansi.h>

inherit SKILL;

mapping *action = ({
   (["skill_name" : "情投意合展歡顏",
     "action" : "$N使一式"+HIC"『情投意合展歡顏』"NOR+"，面露微笑，手中$w一抖，劍光"
                "暴長，洒向$n的$l",
     "dodge"  : 10,
     "force"  : 50,
     "damage" : 10,
     "lvl"    : 0,
     "damage_type":  "刺傷"]),
   (["skill_name" : "突來橫禍陰陽隔",
     "action" : "$N使一式"+HIC"『突來橫禍陰陽隔』"NOR+"，身形驟閃，劍招陡變，手中$w"
                "從一個絕想不到的方位斜斜刺向$n的$l",
     "dodge"  : 20,
     "force"  : 70,
     "damage" : 5,
     "lvl"    : 10,
     "damage_type":  "刺傷"]),
   (["skill_name" : "朝朝暮暮頻思憶",
     "action" : "$N使一式"+HIC"『朝朝暮暮頻思憶』"NOR+"，暴退數尺，低首撫劍片刻，隨"
                "後手中$w驟然穿上，刺向$n的$l",
     "dodge"  : 20,
     "force"  : 75,
     "damage" : 20,
     "lvl"    : 20,
     "damage_type":  "刺傷"]),
   (["skill_name" : "千裡嬋娟只是空",
     "action" : "$N使一式"+HIC"『千裡嬋娟只是空』"NOR+"，身形一晃，疾掠而上，手中$w"
                "龍吟一聲，對準$n的$l連遞數劍",
     "dodge"  : 40,
     "force"  : 90,
     "damage" : 25,
     "lvl"    : 30,
     "damage_type":  "刺傷"]),
   (["skill_name" : "生生世世長相伴",
     "action" : "$N使一式"+HIC"『生生世世長相伴』"NOR+"，一閃而上撲向$n，如影相隨，"
                "手中$w“錚”然有聲，往$n的$l刺去",
     "dodge"  : 60,
     "force"  : 100,
     "damage" : 25,
     "lvl"    : 40,
     "damage_type":  "刺傷"]),
   (["skill_name" : "卻恨天公不作美",
     "action" : "$N使一式"+HIC"『卻恨天公不作美』"NOR+"，一個側身，手中$w疾往斜上挑"
                "起，直指$n的$l",
     "dodge"  : 50,
     "force"  : 130,
     "damage" : 30,
     "lvl"    : 50,
     "damage_type":  "刺傷"]),
   (["skill_name" : "聚日無多相思苦",
     "action" : "$N使一式"+HIC"『聚日無多相思苦』"NOR+"，微微一個轉身，手中$w卻已自"
                "肋下穿出，罩向$n的$l",
     "dodge"  : 40,
     "force"  : 150,
     "damage" : 30,
     "lvl"    : 60,
     "damage_type":  "刺傷"]),
   (["skill_name" : "此恨綿綿無絕期",
     "action" : "$N使一式"+HIC"『此恨綿綿無絕期』"NOR+"，神色微變，劍招陡然變得凌厲無"
                "比，手中$w如匹鏈般洒向$n的$l",
     "dodge"  : 30,
     "force"  : 180,
     "damage" : 40,
     "lvl"    : 70,
     "damage_type":  "刺傷"]),
   (["skill_name" : "黯然神傷淚滿面",
     "action" : "$N使一式"+HIC"『黯然神傷淚滿面』"NOR+"，緩緩低首，暗自嘆了口氣，眼中"
                "瑩光流動，接著手中$w中宮直進，迅捷無比地往$n的$l刺去",
     "dodge"  : 20,
     "force"  : 200,
     "damage" : 35,
     "lvl"    : 80,
     "damage_type":  "刺傷"]),
   (["skill_name" : "願人長久空遺恨",
     "action" : "$N使一式"+HIC"『願人長久空遺恨』"NOR+"，騰身飛躍，手中$w于半空中閃下，"
                "化作一道白色長弧洒向$n的$l",
     "dodge"  : 30,
     "force"  : 220,
     "damage" : 45,
     "lvl"    : 90,
     "damage_type":  "刺傷"]),
   (["skill_name" : "今世未能偕白頭",
     "action" : "$N使一式"+HIC"『今世未能偕白頭』"NOR+"，矮身側步，手中$w反手疾挑而出，"
                "“唰”的一聲往$n的$l刺去",
     "dodge"  : 65,
     "force"  : 240,
     "damage" : 50,
     "lvl"    : 100,
     "damage_type":  "刺傷"]),
   (["skill_name" : "來生還盼續前緣",
     "action" : "$N使一式"+HIC"『來生還盼續前緣』"NOR+"，驀地疾退一步，又沖前三步，手中"
                "$w化為光弧往$n的$l刺去",
     "dodge"  : 40,
     "force"  : 260,
     "damage" : 50,
     "lvl"    : 110,
     "damage_type":  "刺傷"]),
   (["skill_name" : "此情不移堅似鋼",
     "action" : "$N使一式"+HIC"『此情不移堅似鋼』"NOR+"，縱身躍起，不見蹤影，接著卻又從"
                "半空中穿下，雙手握著$w，聲勢逼人地刺向$n的$l",
     "dodge"  : 60,
     "force"  : 280,
     "damage" : 65,
     "lvl"    : 120,
     "damage_type":  "刺傷"]),
   (["skill_name" : "質問天公不開眼",
     "action" : "$N使一式"+HIC"『質問天公不開眼』"NOR+"，手中$w“嗤”的一聲斜刺向天空，"
                "隨即向下“唰唰”兩下，劃出一個叉字，往$n的$l刺去",
     "dodge"  : 45,
     "force"  : 300,
     "damage" : 60,
     "lvl"    : 130,
     "damage_type":  "刺傷"]),
   (["skill_name" : "痴痴傷懷動情時",
     "action" : "$N使一式"+HIC"『痴痴傷懷動情時』"NOR+"，左腿微抬，手中$w自下方挑起，"
                "激起一股勁風反挑$n的$l",
     "dodge"  : 50,
     "force"  : 310,
     "damage" : 70,
     "lvl"    : 140,
     "damage_type":  "刺傷"]),
   (["skill_name" : "但舞痴心情長劍",
     "action" : "$N傾盡全力舞出"+HIC"『但舞痴心情長劍』"NOR+"，神色十分激動，眼中淚珠"
                "滾動，手中$w疾舞不停，全身都已籠罩在迫人的劍氣中，$n不由駭然，只見$N"
                "身形微變，無數道劍氣已逼向$n的$l",
     "dodge"  : 70,
     "damage" : 80,
     "force"  : 320,
     "lvl"    : 150,
     "damage_type":  "刺傷"])
});

int valid_enable(string usage){return usage=="sword" || usage=="parry";}

int valid_learn(object me)
{
        if( query("max_neili", me)<900 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候不夠，無法學習痴心情長劍。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("chixin-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的痴心情長劍。\n");

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
    level   = (int) me->query_skill("chixin-jian",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if( !objectp(weapon=query_temp("weapon", me) )
     || query("skill_type", weapon) != "sword" )
        return notify_fail("你使用的武器不對。\n");

    if( query("qi", me)<50 )
        return notify_fail("你的體力目前沒有辦法練習痴心情長劍。\n");

    if( query("neili", me)<60 )
        return notify_fail("你的內力不夠，無法練習痴心情長劍。\n");
        
    me->receive_damage("qi", 40);
    addn("neili", -55, me);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"chixin-jian/" + action;
}