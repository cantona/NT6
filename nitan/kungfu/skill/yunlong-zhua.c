// yunlong-zhua.c -雲龍爪
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N全身拔地而起，半空中一個筋斗，一式"HIM"「兇鷹襲兔」"NOR"，迅猛地抓向$n的$l",
        "lvl"    : 0,
        "skills_name" : "兇鷹襲兔",
]),
([        "action" : "$N單腿直立，雙臂平伸，一式"GRN"「雄鷹展翅」"NOR"，雙爪一前一後攏向$n的$l",
        "lvl"    : 10,
        "skills_name" : "雄鷹展翅",
]),
([        "action" : "$N一式"HIG"「拔翅鷹飛」"NOR"，全身向斜裏平飛，右腿一繃，雙爪搭向$n的肩頭",
        "lvl"    : 20,
        "skills_name" : "拔翅鷹飛",
]),
([        "action" : "$N雙爪交錯上舉，使一式"HIC"「迎風振翼」"NOR"，一拔身，分別襲向$n左右腋空門",
        "lvl"    : 30,
        "skills_name" : "迎風振翼",
]),
([        "action" : "$N全身滾動上前，一式"HIW"「飛龍獻爪」"NOR"，右爪突出，鬼魅般抓向$n的胸口",
        "lvl"    : 40,
        "skills_name" : "飛龍獻爪",
]),
([        "action" : "$N伏地滑行，一式"HIY"「頂天立地」"NOR"，上手襲向膻中大穴，下手反抓$n的襠部",
        "lvl"    : 50,
        "skills_name" : "頂天立地",
]),
([        "action" : "$N左右手掌爪互逆，一式"HIW"「搏擊長空」"NOR"，無數道勁氣破空而出，迅疾無比地擊向$n",
        "lvl"    : 60,
        "skills_name" : "搏擊長空",
]),
([        "action" : "$N騰空高飛三丈，一式"YEL"「鷹揚萬里」"NOR"，天空中頓時顯出一個巨靈爪影，緩緩罩向$n",
        "lvl"    : 60,
        "skills_name" : "鷹揚萬里",
]),
([        "action" : "$N忽的撥地而起，使一式"BLU"「蒼龍出水」"NOR"，身形化作一道閃電射向$n",
        "lvl"    : 70,
        "skills_name" : "蒼龍出水",
]),
([        "action" : "$N微微一笑，使一式"HIY"「萬佛朝宗」"NOR"，雙手幻出萬道金光,直射向$n的$l",
        "lvl"    : 80,
        "skills_name" : "萬佛朝宗",
])
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }
int valid_combine(string combo) { return combo=="yunlong-shou"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練雲龍爪必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的雲龍神功火候不夠，無法學雲龍爪。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法練雲龍爪。\n");

        if ((int)me->query_skill("claw",1) < 100)
                return notify_fail("你的基本爪法火候不夠，無法學雲龍爪。\n");

        if ((int)me->query_skill("claw",1) < (int)me->query_skill("yunlong-zhua",1))
                return notify_fail("你的基本爪法水平有限，無法繼續學雲龍爪。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練雲龍爪。\n");
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
        int d_e2 = 10;
        int p_e1 = -15;
        int p_e2 = -40;
        int f_e1 = 250;
        int f_e2 = 400;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("yunlong-zhua", 1);
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
                "damage_type" : random(2) ? "內傷" : "抓傷",
        ]);
}
int learn_bonus() { return 15; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) {
        if ((int)me->query_skill("yunlong-xinfa",1) < 100)
        return 0.7;
        else if ((int)me->query_skill("yunlong-xinfa",1) > 200)
        return 1.4;
        else return ( ((int)me->query_skill("yunlong-xinfa",1)-100)/100*0.7+0.7 );
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("yunlong-zhua", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("zhua_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "remain": -1,
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIW "$n" HIW "的身子突然一陣顫抖,牙關咬得咯咯作響，看來是中了$N" HIW "抓上的凝血神抓毒。\n" NOR;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("yunlong-zhua", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
string perform_action_file(string action)
{
        return __DIR__"yunlong-zhua/" + action;
}
int help(object me)
{
        write(HIC"\n雲龍爪："NOR"\n");
        write(@HELP

    天地會雲龍門武功，陳近南成名絕技，凝血神抓威震江湖，宵
小之輩望風披靡。
    可與雲龍手互備。

        學習要求：
                基本爪法40級
                基本內功50級
                雲龍神功50級
                內力350
                相應的雲龍心法
HELP
        );
        return 1;
}
