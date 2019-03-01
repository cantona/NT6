// jinshe-jian.c 金蛇劍法
// Last Modified by sega on Mar. 10 2000
// 擬在拿金蛇劍時提升damage屬性,

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "skill_name" : "金光蛇影",
        "action"     : "$N使一招"HIY"「金光蛇影」"NOR"，手中的$w在一彈指間已向$n的$l連刺數劍",
        "lvl"        : 0
]),
([      "skill_name" : "蛇影萬道",
        "action"     : "$N使一招"HIY"「蛇影萬道」"NOR"，手中$w狂風驟雨般地向$n的$l連攻數劍",
        "lvl"        : 10
]),
([      "skill_name" : "雪地飛蛇",
        "action"     : "$N身形一轉，陡地貼地躍起，手中$w靈動夭躍，一招"HIY"「雪地飛蛇」"NOR"疾刺$n的$l",
        "lvl"        : 20
]),
([      "skill_name" : "金蛇吞信",
        "action"     : "$N身形一轉，一招"HIY"「金蛇吞信」"NOR"，手中的$w從左肋下向$n的$l戳了過去",
        "lvl"        : 30
]),
([      "skill_name" : "金蛇狂舞",
        "action"     : "$N手腕一抖，一招"HIY"「金蛇狂舞」"NOR"，$w挾著閃閃劍光，變幻無方逼向$n的$l",
        "lvl"        : 40
]),
([      "skill_name" : "靈蛇電閃",
        "action"     : "$N心念電閃手腕疾振處，一招"HIY"「靈蛇電閃」"NOR"，$w以無法形容的速度直射$n的$l",
        "lvl"        : 50
]),
([      "skill_name" : "蛇困愁城",
        "action"     : "$N身形一矮，一招"HIY"「蛇困愁城」"NOR"，手中的$w由下往上刺向$n的$l",
        "lvl" : 60
]),
([      "skill_name" : "金蛇化龍",
        "action"     : "$N手中$w劍光暴長，一招"HIY"「金蛇化龍」"NOR"，如千年蛇蠍往$n$l咬去",
        "lvl"        : 70
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
int valid_learn(object me)
{

        if( query("dex", me)<28 )
                return notify_fail("你研究了半天，只覺得身法有些差，始終無法理解其中的真諦。\n");

        if( query("str", me)<28 )
                return notify_fail("你研究了半天，感覺膂力有些低，始終無法隨意施展。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力修為不夠，沒有辦法練金蛇劍法。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本內功火候不夠，沒有辦法練金蛇劍法。\n");

        if ((int)me->query_skill("dodge", 1) < 140)
                return notify_fail("你的基本輕功火候不夠，沒有辦法練金蛇劍法。\n");

        if ((int)me->query_skill("sword", 1) < 120)
                return notify_fail("你的基本劍法火候不夠，沒有辦法練金蛇劍法。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 120)
                return notify_fail("你的武學修養不足，沒有辦法領悟金蛇劍法。\n");

        if( query("character", me) == "心狠手辣" )
                return notify_fail("你一心想殺盡敵人，沒能理解金蛇劍法。\n");

        if( query("character", me) == "陰險姦詐" )
                return notify_fail("你一心想怎麼學好劍法去害人，結果沒能理解金蛇劍法。\n");

        if( query("character", me) == "光明磊落" )
                return notify_fail("你心中暗道：什麼金蛇劍法，亂七八糟的，沒有半點氣勢。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("jinshe-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的金蛇劍法。\n");

        return 1;
}

int practice_skill(object me)
{
        object ob;

        if( !(ob=query_temp("weapon", me)) || 
            query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的氣不夠，沒有辦法練習金蛇劍法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠，沒有辦法練習金蛇劍法。\n");

        me->receive_damage("qi", 70);
        addn("neili", -70, me);
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
        int d_e2 = 55;
        int p_e1 = 5;
        int p_e2 = 25;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 30;
        int m_e2 = 120;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jinshe-jian", 1);
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

int effective_level() { return 25;}

string *parry_msg = ({
        "$n手中的$W化作千百把，護住了全身。\n",
        "$n手中的$W自上削下，幾乎將$N的$w削成兩段。\n",
        "$n使動$W，在身前布起了一道銅牆鐵壁，封住了$N的攻勢。\n",
        "$n將$W往地上一刺，$W反彈起來，剛好直刺$N的雙臂。\n",
        "$n舉劍靜立，一股內力從劍梢透出，逼開了$N。\n",
        "$n一抖手中的$W，護住了全身。\n",
});

string *unarmed_parry_msg = ({
        "$n回招自守，架住了$N的$w。\n",
        "$n不退反進，氣走周天，狠狠磕開了$N的$w。\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}
string perform_action_file(string action)
{
        return __DIR__"jinshe-jian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon;
        int i, ap, dp;

        lvl = me->query_skill("jinshe-jian", 1);

        if( query("neili", me)<300
           || me->query_skill_mapped("sword") != "jinshe-jian"
            || !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                     return 0;

        ap = me->query_skill("sword");
        dp = victim->query_skill("dodge");

        addn("neili", -80, me);

        switch(random(5))
        {
           case 1:
             break;

           case 2:
             break;

          case 3:
             break;

          case 4:
             if (ap / 2 + random(ap) > dp &&
                 ! me->is_busy() &&
                 ! victim->is_busy())
             {
                 message_sort(HIW "\n$N" HIW "劍鋒一轉，手中" + weapon->name() + HIW
                              "猶如靈蛇般地舞動著，竟將$n" HIW "周身纏繞。\n" NOR);
                 me->start_busy(1);
                 victim->start_busy(1 + random(lvl / 20));
             }
             break;

          default :
             if (ap * 3 / 5 + random(ap) > dp &&
                 ! me->is_busy() &&
                 !query_temp("jinshe-jian/lian", me) )
             {
                weapon=query_temp("weapon", me);
                message_sort(HIY "\n$N" HIY "一聲長吟，手中" + weapon->name() + HIY
                             "頓時化作一條靈蛇，迅捷無比地襲向$n" HIY "。\n" NOR,
                             me, victim);

                addn("neili", -180, me);

                set_temp("jinshe-jian/lian", 1, me);
                for (i = 0; i < 9; i++)
                {
                    if (! me->is_fighting(victim))
                            break;

                    if (! victim->is_busy() && random(2) == 1)
                            victim->start_busy(1);

                    COMBAT_D->do_attack(me, victim, weapon, 0);
                }
                delete_temp("jinshe-jian/lian", me);

             }
             break;
       }
}
int help(object me)
{
        write(HIC"\n金蛇劍法："NOR"\n");
        write(@HELP

    金蛇劍法載于「金蛇密笈」，乃金蛇郎君夏雪宜的獨門武功。
夏雪宜幼時全家不幸被溫家五老劫掠滅門，立志報仇。後于苗疆得
識五毒教教主之妹何紅藥，並得其助獲得五毒教的「三寶」──金
蛇劍、金蛇錐及藏寶圖，因而練成絕世武功。
    夏雪宜性情古怪，為人陰狠，武功便正如其人般詭異難測。江
湖上人人聞其名而為之色變，乃是出名的難纏人物。夏雪宜留下的
「金蛇密笈」載有他一身武功，即金蛇劍法、金蛇錐法和金蛇遊身
掌。

        學習要求：
                內力500
HELP
        );
        return 1;
}
