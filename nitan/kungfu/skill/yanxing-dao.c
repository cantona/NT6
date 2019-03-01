// yanxing-dao.c 雁行刀法

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "skill_name" : "讓字訣",
        "action" : "$N使出"MAG"「讓字訣」"NOR"，上身側過，手中刀斜斜砍出，一道白光劈向$n的$l",
        "lvl"    : 0
]),
([        "skill_name" : "打字訣",
        "action" : "$N使出"BLU"「打字訣」"NOR"，左手護頂，大喝一聲，右手刀當頭直劈，化作一道白芒直向$n的$l砍落",
        "lvl"    : 10
]),
([        "skill_name" : "頂字訣",
        "action" : "$N使出"HIY"「頂字訣」"NOR"，左手後撤，刀斜上招架，順勢下剁，左手自腋下穿出，托住對方手腕，刀光不停指向$n的$l",
        "lvl"    : 20
]),
([        "skill_name" : "引字訣",
        "action" : "$N使出"HIC"「引字訣」"NOR"，側身而上，身形突閃，左手帶過對方$n兵刃，右手刀猛地彈出，把$n絞在刀光中",
        "lvl"    : 30
]),
([        "skill_name" : "套字訣",
        "action" : "$N使出"HIG"「套字訣」"NOR"，身形向後乍然一閃，左手急速纏住$n左手，手中刀一陣亂披風，刀光罩住$n的$l",
        "lvl"    : 40
]),
([        "skill_name" : "陳字訣",
        "action" : "$N使出"HIM"「陳字訣」"NOR"，身法陡變，輕靈飄忽，捉摸不透，乘$n眼花耳鳴之際，右手刀光反卷向$n的$l",
        "lvl"    : 50
]),
([        "skill_name" : "探字訣",
        "action" : "$N使出"HIR"「探字訣」"NOR"，輕盈地一個急轉身，兩腳撤步，右手刀盡力向前，直抵$n的$l",
        "lvl"    : 60
]),
([        "skill_name" : "逼字訣",
        "action" : "$N凝神使出"HIB"「逼字訣」"NOR"，身隨意轉，手隨心動，繞著$n疾轉，手中刀光漫卷，將$n的全身籠罩在自己布下的刀網中，無從逃脫",
        "lvl"    : 70
]),
([        "skill_name" : "藏字訣",
        "action" : "$N凝神使出"GRN"「藏字訣」"NOR"，側身藏刀，引誘$n前進了一步，刀光陡現，勢如千軍萬馬，奔騰而出",
        "lvl"    : 80
]),
([        "skill_name" : "錯字訣",
        "action" : "$N凝神使出"RED"「錯字訣」"NOR"，雙手交叉，刀光批攉，$n實在看不清刀光來向，退後欲避，只覺一陣寒氣直逼過來",
        "lvl"    : 90
]),
});

int valid_enable(string usage) { return usage=="blade" || usage=="parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的內功火候不夠。\n");

        if ((int)me->query_skill("blade", 1) < 20)
                return notify_fail("你的基本刀法火候不夠，無法學習雁行刀。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("yanxing-dao", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的雁行刀。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練雁行刀。\n");
        me->receive_damage("qi", 10);
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
        int d_e1 = 35;
        int d_e2 = 15;
        int p_e1 = -15;
        int p_e2 = -35;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 170;
        int m_e2 = 280;
/*        int d_e1 = -50;
        int d_e2 = -35;
        int p_e1 = -25;
        int p_e2 = -0;
        int f_e1 = 200;
        int f_e2 = 250;
        int m_e1 = 200;
        int m_e2 = 300;*/
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("yanxing-dao", 1);
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
                "damage_type" : random(2) ? "割傷" : "擦傷",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return __DIR__"yanxing-dao/" + action;
}
int help(object me)
{
        write(HIC"\n雁行刀法："NOR"\n");
        write(@HELP

    雁行刀法為峨嵋派刀法。

        學習要求：
                基本刀法等級不能低于雁行刀法等級
                臨濟十二莊20級
                內力50
HELP
        );
        return 1;
}
