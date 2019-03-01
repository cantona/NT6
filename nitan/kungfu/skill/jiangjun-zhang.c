// jiangjun-zhang.c 裴將軍詩杖法
// Last Modified by sir 11.1.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action":               
"$N手中$w向$n的$l連點三點，正是"HIC"「裴」"NOR"字起首三筆！",
        "lvl" : 0,
        "skill_name" : "裴"
]),
([      "action":               
"$N揮起$w，對準$n的$l虛點，自右上角至右下角彎曲而下，正是"HIC"「如」"NOR"字草書！",
        "lvl" : 10,
        "skill_name" : "如"
]),
([      "action":               
"$N橫過$w，寫了個"HIC"「猛」"NOR"字，對著$n斜掃過去！",
        "lvl" : 20,
        "skill_name" : "猛"
]),
([      "action":               
"$N大喝一聲，筆法一變寫出個"HIC"「將」"NOR"字，$w一挺撞向$n$l！",
        "lvl" : 30,
        "skill_name" : "將"
]),
([        "action":
"$N身形微轉，$w向著$n的$l橫掃過去，順勢帶出個"HIC"「龍」"NOR"字！",
        "lvl" : 40,
        "skill_name" : "龍"
]),
([        "action":
"$N高高躍起，手中$w劃出個"HIC"「壯」"NOR"字，向著$n的$l撞了過來！",
        "lvl" : 50,
        "skill_name" : "壯"
]),
([        "action":
"$N怒喝一聲，手中$w急舞正是個"HIC"「騰」"NOR"字，將$n$l罩于杖下！",
        "lvl" : 60,
        "skill_name" : "騰"
]),
});
int valid_enable(string usage) { return usage == "staff" || usage == "parry";}
int valid_learn(object me)
{
        if ((int)me->query_skill("kuihua-xinfa", 1) < 20)
                return notify_fail("你的葵花心法火候不夠。\n");
        if( query("max_neili", me)<200 )
                return notify_fail("你的內力修為不夠。\n");
        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "staff" )
                return notify_fail("你必須先找一根木杖或者是類似的武器，才能練杖法。\n");

        if( query("qi", me)<50 || query("neili", me)<50 )
                return notify_fail("你的內力或氣不夠練這門杖法，還是先休息休息吧。\n");
        me->receive_damage("qi", 30);
        addn("neili", -30, me);
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
        int d_e1 = -40;
        int d_e2 = -5;
        int p_e1 = 15;
        int p_e2 = 50;
        int f_e1 = 250;
        int f_e2 = 300;
        int m_e1 = 185;
        int m_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jiangjun-zhang", 1);
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
                "damage_type" : "挫傷" ,
        ]);
}
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n裴將軍詩杖法："NOR"\n");
        write(@HELP

    日月神教黑木崖武功，梅莊三莊主禿筆翁看家本領。

        學習要求：
                葵花心法20級
                最大內力200
HELP
        );
        return 1;
}