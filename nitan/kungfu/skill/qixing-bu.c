#include <ansi.h>

inherit SKILL;

string *dodge_msg = ({
     "$n一式「翩翩若驚鴻」，身不傾，腳不移，身體如行雲流水般直滑出丈余。\n",
     "$n一式「遊龍出海」，忽然一彎腰，全身貼地而行，頓時閃過了$N的凌厲攻勢。\n",
     "$n一式「倒轉七星」，足不動，手不抬，一轉眼間便繞到了$N的身後。\n",
     "$n一式「無影無蹤」，一轉身間，四面八方飄動著無數個$n的身影，令$N手足無措。\n",
     "$n一式「逆轉乾坤」，左踏巽，右轉乾，身行一晃，便到幾丈遠的地方。\n",
     "$n一式「直沖雲霄」，身在空中，左腳在右足上一點，從$N頭頂騰空而過。\n",
     "$n一式「芙蓉出水」，長袖一拂，全身化為一道白影，幽幽地從$N頭頂飄落。\n",
     "$n一式「秋風掃落葉」，身行倏的從$N的眼前直繞到身後，$N瞪大了兩眼，不明所以。\n",
     "$n一式「驀然回手」，身行倏的從$N的眼前飄過，瀟洒之極。\n",
});

int valid_enable(string usage) 
{ 
    return (usage == "dodge") || (usage == "move"); 
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
      if( query("qi", me)<40 )
           return notify_fail("你的體力太差了，不能練倒轉七星步。\n");

      if( query("neili", me)<30 )
           return notify_fail("你的內力太差了，不能練倒轉七星步。\n");

      me->receive_damage("qi", 35);
      addn("neill", -24, me);
      return 1;
}