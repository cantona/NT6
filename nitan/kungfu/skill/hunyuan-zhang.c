// hunyuan-zhang.c 混元掌

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一式"HIW"「白雲出岫」"NOR"，雙掌間升起一團淡淡的白霧，緩緩推向$n的$l",
        "lvl" : 0,
        "skill_name" : "白雲出岫"
]),
([        "action" : "$N並指如劍，一式"HIW"「白虹貫日」"NOR"，疾向$n的$l戳去",
        "lvl" : 10,
        "skill_name" : "白虹貫日"
]),
([        "action" : "$N使一式"HIB"「雲斷秦嶺」"NOR"，左掌微拂，右掌乍伸乍合，猛地插往$n的$l",
        "lvl" : 20,
        "skill_name" : "雲斷秦嶺"
]),
([        "action" : "$N雙掌隱隱泛出青氣，一式"GRN"「青鬆翠翠」"NOR"，幻成漫天碧綠的鬆針，雨點般向$n擊去",
        "lvl" : 30,
        "skill_name" : "青鬆翠翠"
]),
([        "action" : "$N身形往上一縱，使出一式"HIC"「天紳倒懸」"NOR"，雙掌並攏，筆直地向$n的$l插去",
        "lvl" : 40,
        "skill_name" : "天紳倒懸"
]),
([        "action" : "$N身形一變，使一式"MAG"「無邊落木」"NOR"，雙掌帶著蕭剎的勁氣，猛地擊往$n的$l",
        "lvl" : 50,
        "skill_name" : "無邊落木"
]),
([        "action" : "$N使一式"HIG"「高山流水」"NOR"，左掌凝重，右掌輕盈，同時向$n的$l擊去",
        "lvl" : 60,
        "skill_name" : "高山流水"
]),
([        "action" : "$N突地一招"RED"「金玉滿堂」"NOR"，雙掌挾著一陣風雷之勢，猛地劈往$n的$l",
        "lvl" : 70,
        "skill_name" : "金玉滿堂"
]),
([        "action" : "$N一式"HIM"「風伴流雲」"NOR"，雙掌縵妙地一陣揮舞，不覺已擊到$n的$l上",
        "lvl" : 80,
        "skill_name" : "風伴流雲"
]),
([        "action" : "$N一式"BLU"「煙雨飄渺」"NOR"，身形凝立不動，雙掌一高一低，看似簡單，卻令$n無法躲閃",
        "lvl" : 90,
        "skill_name" : "煙雨飄渺"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo == "poyu-quan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練混元掌必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學混元掌。\n");

        if( query("max_neili", me)<150 )
                return notify_fail("你的內力太弱，無法練混元掌。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練混元掌。\n");
        me->receive_damage("qi", 30);
        addn("neili", -15, me);
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
        int d_e1 = -25;
        int d_e2 = -5;
        int p_e1 = 15;
        int p_e2 = 45;
        int f_e1 = 150;
        int f_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("hunyuan-zhang", 1);
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
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}
int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("hunyuan-zhang", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("hyz_damage",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIR "$n" HIR "只覺得一股火熱的內力襲入內腑，混身燥熱無比！\n" NOR;
        }
}

void skill_improved(object me)
{
        int i =3 +random(8);
        if (me->query_skill("hunyuan-zhang", 1) > 200
         && query("hunyuan/gift", me)+200<me->query_skill("hunyuan-zhang",1) )
        {
                if( !query("hunyuan/gift", me) )
                        set("hunyuan/gift", me->query_skill("hunyuan-zhang",1)-200, me);
                else
                        addn("hunyuan/gift", 1, me);
                addn("max_neili", i, me);
                tell_object(me, HIW "\n隨著混元掌的提高，你感覺自己內力增加了" + chinese_number(i) + "點。\n" NOR);
        }
}

string perform_action_file(string action)
{
        return __DIR__"hunyuan-zhang/" + action;
}
int help(object me)
{
        write(HIC"\n混元掌："NOR"\n");
        write(@HELP

    混元掌為華山武功。混元掌緣自劍法，故招數名稱多與劍招相
符。
    可與劈石破玉拳互備。

        學習要求：
                紫霞神功20級
                內力100
HELP
        );
        return 1;
}
