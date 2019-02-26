// dagou-bang.c 打狗棒法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action": "$N使出一招"HIG"「棒打雙犬」"NOR"，手中$w化作兩道青光砸向$n的$l",
        "lvl"        : 10,
        "skill_name" : "棒打雙犬"
]),
([      "action": "$N手中$w左右晃動，一招"HIG"「撥草尋蛇」"NOR"向$n的$l攻去",
        "lvl"        : 20,
        "skill_name" : "撥草尋蛇"
]),
([      "action": "$N舉起$w，居高臨下使一招"HIG"「打草驚蛇」"NOR"敲向$n的$l",
        "lvl"        : 30,
        "skill_name" : "打草驚蛇"
]),
([      "action": "$N施出"HIG"「撥狗朝天」"NOR"，$w由下往上向$n撩去",
        "lvl"        : 40,
        "skill_name" : "撥狗朝天"
]),
([      "action":"$N眼中射出一道青芒，手中綠玉棒使出"HIR"「天下無狗」"NOR"，劈天蓋地劈落",
        "lvl"        : 50,
        "skill_name" : "天下無狗"
]),
});

int valid_enable(string usage)
{
        return usage == "staff" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("dex", me)<26 )
                return notify_fail("你的先天身法太差，無法學習打狗棒法。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為不足，無法學習打狗棒法。\n");

        if ((int)me->query_skill("staff", 1) < 100)
                return notify_fail("你的基本杖法不夠，無法學習打狗棒法。\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("dagou-bang", 1))
                return notify_fail("你的基本杖法水平有限，無法領會更高深的打狗棒法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練打狗棒法。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練打狗棒法。\n");

        me->receive_damage("qi", 75);
        addn("neili", -80, me);
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
        int d_e1 = -60;
        int d_e2 = -30;
        int p_e1 = -10;
        int p_e2 = 10;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 100;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("dagou-bang", 1);
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
                "damage_type" : "挫傷",
        ]);
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int) me->query_skill("dagou-bang", 1) < 100
            || !query_temp("feng_zijue", me )
            || !(weapon=query_temp("weapon", me) )
            || ! living(me)
            || query("skill_type", weapon) != "staff" )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("dagou-bang", 1);

        if (ap / 2 + random(ap) < dp * 3 / 4)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "巧妙的施展打狗棒「" HIY "封"
                                            HIG "」字訣，手中" + weapon->name() + HIG
                                            "左封右閉，使得$N" HIG "的攻勢全然落空。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "急轉手中" + weapon->name() +
                                            HIG "，打狗棒「" HIY "封" HIG "」字訣發揮"
                                            "得淋漓盡致，頓將$N" HIG "的招式驅於無形。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "$n" HIY "驀地施展出打狗棒「封」字"
                                 "訣，可是$N" HIY "理也不理，當即揮招直"
                                 "入，進襲$n" HIY "。\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "急轉手中" + weapon->name() +
                                 HIY "，左封右閉，然而$N" HIY "卻是精演"
                                 "天數，絲毫不受$n" HIY "的迷惑。\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

mixed hit_ob(object me, object victim, int damage)
{
        string msg;
        int ap, dp, zhencost;
        string result;
        object weapon;
        int fmsk = me->query_skill("bixue-danxin", 1);

        if (random(fmsk) >= random(600))
                damage += fmsk / 2 + random(fmsk / 2);

        if( !objectp(weapon=query_temp("weapon", me)) )
                return 0;

        zhencost = sqrt(weapon->weight() / 10) + 10;
        if( query("neili", me)<zhencost || query("jing", me)<zhencost )
                return 0;

        ap = me->query_skill("stick", 1) / 2 +
             me->query_skill("dagou-bang", 1);

        dp = victim->query_skill("dodge", 1) / 2 +
              victim->query_skill("parry", 1) / 4;
        dp += victim->query_skill("martial-cognize", 1);



        if (random(ap+dp) > ap)
        {
                result=HIG"突然青光閃動，棒招來勢神妙無方，"+query("name", weapon)+HIG"擊中了$n。\n"NOR;
                damage=query("weapon_prop/damage", weapon)*3;
                if (! victim->is_busy())
                        victim->start_busy(1 + random(3));
                addn("neili", -zhencost, me);
                addn("jing", -zhencost, me);
                return ([ "msg" : result, "damage" : damage ]);
        }
        else if (random(ap + 2 * dp) > ap)
        {
                result = HIG "$N猛地遞出一招，這一棒迅捷無倫，直取$n眉心，$p「啊」的一聲，連退出數尺！\n" NOR;
                damage=query("weapon_prop/damage", weapon)*2;
                if (! victim->is_busy())
                        victim->start_busy(1 + random(2));
                addn("neili", -zhencost, me);
                addn("jing", -zhencost, me);
                return ([ "msg" : result, "damage" : damage ]);
        }
        else
        {
                result = weapon->name()+ HIG "幌動，霎眼之間竟已轉到$n身後，拍的一聲，在$p臀上抽了一下。！\n" NOR;
                damage=query("weapon_prop/damage", weapon);
                if (! victim->is_busy())
                        victim->start_busy(1+random(1));
                addn("neili", -zhencost, me);
                addn("jing", -zhencost, me);
                return ([ "msg" : result, "damage" : damage ]);
        }
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 5; }
int power_point() { return 1.0; }
int query_effect_parry(object attacker, object me)
{
        int lvl;
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "staff" )
                return 0;

        lvl = me->query_skill("dagou-bang", 1);
        if (lvl < 80)  return 50;
        if (lvl < 200) return 100;
        if (lvl < 280) return 160;
        if (lvl < 350) return 200;
        return 240;
}

string perform_action_file(string action)
{
        return __DIR__"dagou-bang/" + action;
}

int help(object me)
{
        write(HIC"\n打狗棒法："NOR"\n");
        write(@HELP

    三十六路打狗棒法是丐幫開幫祖師爺所創，歷來是前任幫主傳
後任幫主，決不傳給第二個人。丐幫第三任幫主的武功尤勝開幫祖
師，他在這路棒法中更加入無數奧妙變化。數百年來，丐幫逢到危
難關頭，幫主親自出馬，往往便仗這打狗棒法除奸殺敵，鎮懾羣邪。
    打狗棒法名字雖然陋俗，但變化精微，招術奇妙，實是古往今
來武學中第一等特異的功夫，卓然自成一家，與各門派的功夫均無
牽涉。單學招數，若是不明『絆、劈、纏、戳、挑、引、封、轉』
八字口訣，那是一點無用。每句口訣，須與每個招數相配，威力無
儔。為丐幫幫主歷代相傳的鎮幫之寶。

        學習要求：
                混天氣功50級
                內力200
HELP
        );
        return 1;
}
