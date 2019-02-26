// wuxiang-zhi.c - 少林無相指法

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N將雙手攏在衣袖之中，一招"HIW"「廣大無相劫」"NOR"，暗勁自袖中悄悄湧出，刺向$n",
        "lvl"   : 0,
        "skill_name" : "廣大無相劫"
]),
([        "action" : "$N微微一笑，一招"HIW"「智慧無相劫」"NOR"，衣袖連擺，指勁隨機彈出，叫人琢磨不透，無法躲避",
        "lvl"   : 10,
        "skill_name" : "智慧無相劫"
]),
([        "action" : "$N垂手站立，絲毫不動，但聞$n身前哧的一聲，聞聲不見物，是那招"HIW"「真如無相劫」"NOR"",
        "lvl"   : 30,
        "skill_name" : "真如無相劫"
]),
([        "action" : "$N抬頭往天，一指"HIW"「性海無相劫」"NOR"暗襲$n$l，本人卻見絲毫不動，仿若無事發生一樣",
        "lvl"   : 60,
        "skill_name" : "性海無相劫"
]),
([        "action" : "$N一招"HIW"「穎悟無相劫」"NOR"向$n點出，聞得一破空之聲，卻見$P微笑點頭，卻再無任何動靜",
        "lvl"   : 100,
        "skill_name" : "穎悟無相劫"
]),
([        "action" : "但聞哧哧兩聲，$n臉色突變，$N卻悠閒自在，並無動過手的跡象，這好像是那招"HIW"「圓覺無相劫」"NOR"",
        "lvl"   : 150,
        "skill_name" : "圓覺無相劫"
]),
});

/*
mapping *action = ({
([     "action": "$N隨手前踏上一步，右指中宮直進，一式「無聲無息」擊向$n的$l",
       "force" : 80,
       "attack": 20,
       "parry" : 20,
       "dodge" : -5,
       "damage": 20,
       "lvl"   : 0,
       "skill_name" : "無聲無息",
       "damage_type" : "刺傷"
]),
([     "action": "$N一招「無慾無望」，輕唱一聲佛號，左右看似隨意一彈，一屢勁風已射向$n",
       "force" : 90,
       "attack": 30,
       "parry" : 5,
       "dodge" : 20,
       "damage": 50,
       "lvl"   : 40,
       "skill_name" : "無慾無望",
       "damage_type" : "刺傷"
]),
([     "action": "$N身形飄忽不定，一式「無法無天」，右指擊向$n的$l",
       "force" : 150,
       "attack": 50,
       "parry" : 35,
       "dodge" : 25,
       "damage": 80,
       "lvl"   : 80,
       "skill_name" : "無法無天",
       "damage_type" : "刺傷"
]),
([     "action": "$N腳踏七星步，突然一招「佛光普照」，左指從意想不到的角度攻向$n的各大要穴",
       "force" : 180,
       "attack": 70,
       "parry" : 35,
       "dodge" : -10,
       "damage": 100,
       "lvl"   : 120,
       "skill_name" : "佛光普照",
       "damage_type" : "刺傷"
]),
([     "action": "$N一招「佛恩濟世」，背朝$n，轉身一指，令$n防不勝防",
       "force" : 230,
       "attack": 70,
       "parry" : 30,
       "dodge" : 15,
       "damage": 130,
       "lvl"   : 160,
       "skill_name" : "佛恩濟世",
       "damage_type" : "割傷"
]),
([     "action": "$N盤膝端坐，一招「佛法無邊」，右手拇指彈出一道勁風，擊向$n",
       "force" : 160,
       "attack": 60,
       "parry" : 30,
       "dodge" : 5,
       "damage": 100,
       "lvl"   : 120,
       "skill_name" : "佛法無邊",
       "damage_type" : "刺傷"
]),
([     "action": "$N雙目緊閉，一招「無色無相」，聚集全身內力於一指射出一道無色勁氣直逼$n",
       "force" : 250,
       "attack": 100,
       "parry" : 50,
       "dodge" : 25,
       "damage": 180,
       "lvl"   : 200,
       "skill_name" : "無色無相",
       "damage_type" : "刺傷"
]),
});
*/
int valid_enable(string usage) { return usage == "finger" || usage == "parry"; }

int valid_combine(string combo) { return combo == "xuni-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練無相指必須空手。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的內功火候不夠，無法學無相指。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力太弱，無法練無相指。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("wuxiang-zhi", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的無相指。\n");

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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 10;
        int d_e2 = 30;
        int p_e1 = -45;
        int p_e2 = -25;
        int f_e1 = 450;
        int f_e2 = 550;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("wuxiang-zhi", 1);
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
                "damage_type" : random(2) ? "刺傷" : "瘀傷",
        ]);
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手練習！\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練無相指。\n");

        me->receive_damage("qi", 50);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuxiang-zhi/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n無相劫指："NOR"\n");
        write(@HELP

    無相劫指是少林高級指法，不能互備，取自佛法十二字“廣大，智慧，
真如，性海，穎悟，圓覺”。

        學習要求：
                一指禪50級
                內力修為2500
HELP
        );
        return 1;
}
