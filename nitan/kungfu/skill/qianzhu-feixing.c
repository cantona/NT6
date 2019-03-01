//duoming-jinhua 奪命金花
// 1997-2-14

inherit SKILL;

string  *msg = ({
"$N一式「變幻多端」，忽聽得颼颼兩聲，黃光閃動，$w向$n的$l射出",
"$w倏左倏右，四面八方的罩向$n，卻是$N以一式「倏左倏右」向$n發出八枚$w",
"$N低哼一聲，一式「仙女散花」，的把$w向$n撒出，共有四四一十六之多",
"$n只聽得颼颼聲響，卻是$N一招「滿天星雨」，十多枚$w向$n各大穴飛去",
"突然黃光一閃，$N一式「千裡追魂」，三枚$w向$n的胸口要害打去",
"$N一式「回頭望月」，突然反手擲出三枚$w，飛向$n的後腦",
"$N一招「閃電風雷」，五枚$w連續飛射，破風聲勁急，快得$n不能看清形影",
"$N一招「金花奪命」，全身飛撲而進，左手飛揚，四枚$w射向$n和胸部",
"$N飛身而起，一招「梅花頓現」，$w一枚枚的從$N手中飛出，雜雜梅花射向$n"
});

int valid_enable(string usage)
{
        return usage == "throwing" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        return ([
                "action":msg[random(sizeof(msg))],
                "damage":(random(3)+1)*50,
                "damage_type":random(2)?"刺傷":"割傷",
                "dodge":random(30),
                "force":random(200)+100,
                "post_action":
                  (: call_other, WEAPON_D, "throw_weapon" :)
                ]);
}
int practice_skill(object me)
{
       object weapon;
       if( !objectp(weapon=query_temp("weapon", me) )
        || query("skill_type", weapon) != "throwing" )
               return notify_fail("你使用的武器不對。\n");
       if( query("jingli", me)<50 )
               return notify_fail("你的體力不夠練奪命金花。\n");
       me->receive_damage("jingli", 30);
       return 1;
}

int valid_learn(object me)
{
       if( query("max_neili", me)<500 )
               return notify_fail("你的內力不夠。\n");
       if ((int)me->query_skill("shenghuo-shengong", 1) < 50)
               return notify_fail("你的聖火神功火候太淺。\n");
               return 1;
}
string perform_action_file(string action)
{
       return __DIR__"duoming-jinhua/" + action;
}
