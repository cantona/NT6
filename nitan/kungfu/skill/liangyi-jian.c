//liangyi-jian.c 兩儀劍法
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "skill_name" : "法分玄素",
        "action"     : "$N劍尖劍芒暴長，一招"HIC"「法分玄素」"NOR"，手中$w自左下大開大闔，一劍斜上刺向$n的$l",
        "lvl"        : 0
]),
([      "skill_name" : "道盡陰陽",
        "action"     : "$N劍勢圈轉，手中$w如粘帶連，平平展展揮出，一招" HIR"「道盡陰陽」"NOR"輕輕劃過$n的$l",
        "lvl"        : 10
]),
([      "skill_name" : "淵臨深淺",
        "action"     : "$N長劍輕靈跳動，劍隨身長，右手$w使出一式" HIB"「淵臨深淺」"NOR"刺向$n的$l",
        "lvl"        : 20
]),
([      "skill_name" : "水泛青黃",
        "action"     : "$N長劍下指，劍意流轉，一招"HIG"「水泛青黃」"NOR"直取$n的$l",
        "lvl"        : 30
]),
([      "skill_name" : "雲含吞吐",
        "action"     : "$N劍芒吞吐，幻若靈蛇，右手$w使出一式"HIW"「雲含吞吐」"NOR"，劍勢極盡曼妙，刺向$n的$l",
        "lvl"        : 40
]),
([      "skill_name" : "夢醒蝶莊",
        "action"     : "$N屈腕雲劍，劍光如彩碟紛飛，幻出點點星光，右手$w使出一式"HIG"「夢醒蝶莊」"NOR"躍躍灑灑飄向$n的$l",
        "lvl"        : 50
]),
([      "skill_name" : "人在遐邇",
        "action"     : "$N揮劍分擊，劍勢自胸前躍出，右手$w一式"HIM"「人在遐邇」"NOR"，毫無留戀之勢，刺向$n的$l",
        "lvl"        : 60
]),
([      "skill_name" : "情繫短長",
        "action"     : "$N退步，左手劍指劃轉，腰部一扭，右手$w一記" GRN"「情繫短長」"NOR"自下而上刺向$n的$l",
        "lvl"        : 80
]),
});

int valid_enable(string usage){return (usage== "sword") || (usage== "parry");}
int valid_learn(object me)
{
        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("liangyi-jian", 1) )
                return notify_fail("你的基本劍法火候太淺。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練兩儀劍法。\n");
        if( query("neili", me)<45 )
                return notify_fail("你的內力不足以練兩儀劍法。\n");
        me->receive_damage("qi", 55);
        addn("neili", -40, me);
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
        int d_e2 = 0;
        int p_e1 = -50;
        int p_e2 = -35;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 200;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("liangyi-jian", 1);
        if( random(lvl)>240 && me->query_skill("force")>200 && query("neili", me) >= 500 )
         {
        return ([
        "action":HIC"$N神色凝重，手中$w"NOR+HIY"一頓，氣隨意轉，$w"+HIY"上劍芒突盛，
                   心中默唸劍訣，如暴風般地刺向$n的$l！"NOR,
        "force" : 500,
        "dodge" : -140,
        "parry" : -140,
        "damage": 900,
        "weapon": HIY"劍罡"NOR,
        "damage_type":  "刺傷"
        ]);
        }
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
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"liangyi-jian/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
       string msg;
       int j, k;
       j = me->query_skill("liangyi-jian", 1);
       k = me->query_skill("qinqi-shuhua",1);
       if( random(10) >= 5
        && !me->is_busy()
        && !victim->is_busy()
        && j > 120
        && k > 120
        && me->query_skill_mapped("parry") == "liangyi-jian"
        && j > random(victim->query_skill("dodge",1))){
          switch(random(3)){
            case 0 :
               msg = HIW"$N施展開劍路，劍勢浩蕩起伏，犀利無比！\n"NOR;
               msg+= HIW"$n連連後退，全力招架，無力還招！\n"NOR;
               victim->start_busy(3);
               message_vision(msg, me, victim);
               COMBAT_D->do_attack(me,victim,query_temp("weapon", me),2);
               break;
            case 1 :
               msg = HIW"$N繞着$n飛快地旋轉，一下子連刺出好幾十劍！\n"NOR;
               msg+= HIW"$n根本分不清楚那一劍是虛，那一劍是實，好停下攻勢，嚴守門户。\n"NOR;
               victim->start_busy(2);
               message_vision(msg, me, victim);
               COMBAT_D->do_attack(me,victim,query_temp("weapon", me),0);
               break;
            case 2 :
               msg = HIW"$N風馳電掣的繞著$n快跑，忽東忽西，簡直像是足不點地的飛行一般！\n"NOR;
               msg+= HIW"$n隨着$N轉來轉去，弄得眼花繚亂，搖搖欲墜。\n"NOR;
               victim->start_busy(3);
               message_vision(msg, me, victim);
               COMBAT_D->do_attack(me,victim,query_temp("weapon", me),1);
               break;
          }
       }
}

int help(object me)
{
        write(HIC"\n兩儀劍法："NOR"\n");
        write(@HELP

    太極生兩儀。
    武當派兩位道長，窮數十年心血，創此兩儀劍法，劍法中有陰
有陽，亦剛亦柔，陰陽合一，威力無儔。

        學習要求：
                太極神功50級
                內力200
                基本劍法不低於兩儀劍法
HELP
        );
        return 1;
}
