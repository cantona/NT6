// songshan-sword.c 嵩山劍法
// Last Modified by winder on Mar. 10 2000
// Modified by Java Sep.1998

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "skill_name" : "萬嶽朝宗",
        "action" : "$N右手$w一立，舉劍過頂，彎腰躬身，使一招"HIY"「萬嶽朝宗」"NOR"正是\n嫡系正宗的嵩山劍法",
        "lvl" : 0
]),
([        "skill_name" : "開門見山",
        "action" : "$N左手向外一分，右手$w向右掠出，使的是嵩山派劍法"HIG"「開門見\n山」"NOR"",
        "lvl" : 10
]),
([        "skill_name" : "獨劈華山",
        "action" : "$N手中$w自上而下的向$n直劈下去，一招"HIB"「獨劈華山」"NOR"，真有石\n破天驚的氣勢，將嵩山劍法之所長髮揮得淋漓盡致",
        "lvl" : 20
]),
([        "skill_name" :"千古人龍",
        "action" : "$N手中$w突然間劍光一吐，化作一道白虹，端嚴雄偉，端麗飄逸，\n正是嵩山劍法的精要所在，一招"RED"「千古人龍」"NOR"向$n$l直刺過來",
        "lvl" : 30
]),
([        "skill_name" :"疊翠浮青",
        "action" : "$N手中$w突然間劍光一吐，一招"GRN"「疊翠浮青」"NOR"化成一道青光，氣\n壯雄渾，向$n$l直刺過來",
        "lvl" : 40
]),
([        "skill_name" : "玉井天池",
        "action" : "$N手中$w劍光一吐，一招"HIW"「玉井天池」"NOR"威儀整肅，端嚴雄偉，向\n$n$l直刺過來",
        "lvl" : 50
]),
([        "skill_name" : "天外玉龍",
        "action" : "$N手中$w刷的一劍自左而右急削過去，正是一招嵩山派正宗劍法\n"HIC"「天外玉龍」"NOR"。奔騰矯夭，氣勢雄渾。但見$w自半空中橫過，劍身似曲似\n直，長劍便如一件活物一般",
        "lvl" : 60
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
int valid_learn(object me)
{
        object ob;
        if( query("max_neili", me)<150 )
                return notify_fail("你的內力不夠，沒有辦法練嵩山劍法。\n");

        if( !(ob=query_temp("weapon", me)) || 
                query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<40 || query("neili", me)<30 )
                return notify_fail("你的內力或氣不夠，沒法練習嵩山劍法。\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
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
        int d_e1 = 5;
        int d_e2 = 25;
        int p_e1 = -25;
        int p_e2 = -5;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 120;
        int m_e2 = 210;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("songshan-sword", 1);
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
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int valid_effect(object me, object weapon, string name, int skill)
{
}

string perform_action_file(string action)
{
        return __DIR__"songshan-sword/" + action;
}
int help(object me)
{
        write(HIC"\n嵩山劍法："NOR"\n");
        write(@HELP

    嵩山劍法是五嶽盟主、嵩山掌門左冷禪整理本派劍譜，集其大
成，重新釐定的劍法。

        學習要求：
                寒冰真氣
                內力50
HELP
        );
        return 1;
}
