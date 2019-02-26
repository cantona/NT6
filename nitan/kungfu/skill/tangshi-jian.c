// tangshi-jian.c 唐詩劍法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N手中$w自左上方斜劈向下，跟着向後挺劍刺出，一招"HIC"「孤鴻海上來，池潢不敢顧」"NOR"，手中$w更不回頭，一劍劍點向$n的$l。",
        "lvl" : 0,
        "skill_name" : "孤鴻海上來，池潢不敢顧"
]),
([        "action" : "$N退了兩步，$w大開大闔，一聲吆喝，橫削三劍，一招"HIB"「哥翁喊上來，是橫不敢過」"NOR"直刺$n的$l",
        "lvl" : 10,
        "skill_name"  : "哥翁喊上來，是橫不敢過"
]),
([        "action" : "突然間嗤嗤嗤三聲，$N向$n連刺三劍，一式"HIG"「俯聽聞驚風，連山若波濤」"NOR"，劍刃在$n的$l邊堪堪掠過，$n只覺$l涼颼颼地，大吃一驚，急忙倒退。",
        "lvl" : 20,
        "skill_name" : "俯聽聞驚風，連山若波濤"
]),
([        "action" : "$N手中$w遞出，一個虛招指向$n的左肩，反手卻使出一式"HIY"「落日照大旗，馬鳴風蕭蕭」"NOR"，由下而上$w疾刺$n的$l",
        "lvl" : 30,
        "skill_name" :"落日照大旗，馬鳴風蕭蕭"
]),
([        "action" : "$N一招"HIW"「舉頭望明月，低頭思故鄉」"NOR"，身子前傾，忽地回劍斜削，手中$w平平地向$n的$l揮去",
        "lvl" : 40,
        "skill_name" : "舉頭望明月，低頭思故鄉"
]),
([        "action" : "$N上身往左側一擰，一招"BLU"「長安一片月，萬户搗衣聲」"NOR"，右手$w反手向$n的$l揮去",
        "lvl" : 50,
        "skill_name" : "長安一片月，萬户搗衣聲"
]),
([        "action" : "$N左一招"MAG"「萬國仰宗周」"NOR"，右一招"HIM"「衣冠拜冕旒」"NOR"，劍鋒平指，一氣呵成橫掃$n的$l",
        "lvl" : 60,
        "skill_name" : "萬國仰宗周 衣冠拜冕旒"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<30 || query("neili", me)<10 )
                return notify_fail("你的內力或氣不夠練唐詩劍法。\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 40;
        int d_e2 = 60;
        int p_e1 = 10;
        int p_e2 = 30;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 10;
        int m_e2 = 110;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("tangshi-jian", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "割傷" : "刺傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n唐詩劍法："NOR"\n");
        write(@HELP

    鐵骨墨萼梅念笙傳給他三個徒弟五雲手萬震山，陸地神龍言達
平，鐵鎖橫江戚長髮的劍法。

        學習要求：
                內力100
HELP
        );
        return 1;
}