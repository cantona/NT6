// riyue-lun.c 日月輪法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N使一招"GRN"「破竹勢」"NOR"，掄起手中的$w向$n的$l砸去",
        "skill_name" : "破竹勢",
        "lvl" : 0
]),
([      "action" : "$N使一招"BLU"「隱山谷勢」"NOR"，雙肩一沉，舞動手中$w向$n的$l橫掃",
        "skill_name" : "隱山谷勢",
        "lvl" : 8
]),
([      "action" : "$N使一招"MAG"「隱微勢」"NOR"，就地一滾，手中自下而上撩向$n的$l",
        "skill_name" : "隱微勢",
        "lvl" : 16
]),
([      "action" : "$N使一招"RED"「擒縱勢」"NOR"，身形起伏之際$w掃向$n的$l",
        "skill_name" : "擒縱勢",
        "lvl" : 24
]),
([      "action" : "$N使一招"YEL"「圓滿勢」"NOR"，$w如離弦之箭般直搗$n的$l",
        "skill_name" : "圓滿勢",
        "lvl" : 32
]),
([      "action" : "$N躍入半空，使一招"HIC"「月重輝勢」"NOR"，高舉$w敲向$n的$l",
        "skill_name" : "月重輝勢",
        "lvl" : 40
]),
([      "action" : "$N使一招"HIW"「捉月勢」"NOR"，斜舉手中$w擊向$n的$l",
        "skill_name" : "捉月勢",
        "lvl" : 48
]),
([      "action" : "$N提一口真氣，使出"HIR"「顯吉祥」"NOR"，$w掃向$n的頭部",
        "skill_name" : "顯吉祥",
        "lvl" : 56
]),
});
string  *msg = ({
        CYN"空中那五隻$w"CYN"對擊，聲若龍吟，悠悠不絕，就在$n"CYN"一呆之際，$w"CYN"飛砸了出去！"NOR,
        MAG"嗚嗚聲響中，$w"MAG"旋轉飛舞着撞向$n"MAG"，在$p"MAG"便要擋隔時，卻繞過$n"MAG"飛到了身後"NOR,
        MAG"$w"MAG"連續擲出，連續飛回，繞著$n"MAG"兜個圈子，忽高忽低，或正或斜，所發聲音也是有輕有響，旁觀眾人均給擾得眼花撩亂，心神不定"NOR,
        YEL"一聲「小心了！」，驀然間$w"YEL"五體歸一，並排向$n"YEL"撞去，勢若五牛衝陣，威不可擋"NOR,
        HIB"只見$w"HIB"繞著$n"HIB"，上下翻飛，$w"HIB"跳躍靈動，嗚嗚響聲不絕，掀的陣陣狂風有如刀割，似要把$n"HIB"從中劈開"NOR,
        HIR"突然，狂風亂起，激盪中那$w"HIR"相碰相撞，五輪歸一，合併了向$n砸去"NOR,
        HIG"法輪在$n"HIG"身前環饒，猛地向$p"HIG"迎頭擊下，接着又飛來一輪，一抄一送，嗚嗚聲響，兜向$n"HIG"$l"NOR,
        HIW"呼呼飛嘯聲中，那五隻$w"HIW"或直飛、或斜飛、或迴旋、或下墜、或上升，霎時間$n"HIW"的全部退路已被封死"NOR,
        HIC"猛地裏$w"HIC"向$n"HIC"$l飛砸下，在$p"HIC"沉肩卸避之時，$w"HIC"又突然上飛擊出，砸向$p"HIC"的$l"NOR,
        HIM"那$w"HIM"飛旋砸到，$n"HIM"卻並不回頭，聽風辨器，一一擋開，但$w"HIM"便如長上了眼睛一般，竟然又旋飛到了$n"HIM"$l"NOR,
        HIG"隨着森森懾人的厲吼，$w"HIG"錘驀而急顫晃動，輪身嗡嗡震響，在不及眨眼的瞬息間，耀目的電光金蛇四射迸閃，飛掠周遭，迅捷無匹的擊$n！"NOR,
        MAG"法輪再次合圍，紫電精芒圍著$n"MAG"的四周旋舞閃射，千百輪影幻映出一幅美麗而眩目的圖案，這圖案美極了，似是一片多角形的紫色雪晶體"NOR,
});
int valid_enable(string usage) { return usage == "hammer" || usage == "parry"; }
int valid_learn(object me)
{
        /*
        if( query("str", me)<32 )
                return notify_fail("你先天膂力不足，難以修煉日月輪法。\n");
        */

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("hammer", 1) < 100)
                return notify_fail("你的基本錘法不夠，難以修煉日月輪法。\n");

        if ((int)me->query_skill("hammer", 1) < (int)me->query_skill("riyue-lun", 1))
                return notify_fail("你的基本錘法水平有限，無法領會更高深的日月輪法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "hammer" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 || query("neili", me)<50 )
                return notify_fail("你的內力或氣不夠,練不了日月輪法。\n");
        me->receive_damage("qi", 40);
        addn("neili", -40, me);
        return 1;
}
/*
mixed hit_ob(object me, object victim, int damage_bonus)
{
        object my_w, victim_w;
        object piece;
        victim_w=query_temp("weapon", victim);
        my_w=query_temp("weapon", victim);

//      if( me->query("dex") < 20 || me->query("str") < 20 )

        if( query_temp("weapon", victim) || query_temp("secondary_weapon", victim) )
        {
                if( (int)(me->query_skill("riyue-lun", 1)) < 20 )
                        return HIW"一陣兵刃相撞的聲音過後，對方兵器居然完好無損。\n"NOR;
                if( random(query_temp("apply/damage", victim))<random(me->query_skill("riyue-lun",1)/3) )
                {
                        if( objectp(my_w=query_temp("weapon", me)) &&
                                (query("id", my_w) == "falun"
                                   || query("id", my_w) == "yinlun"
                                    || query("id", my_w) == "jinlun" )
                                    && query("ownmake", my_w) != 1 )
                        {
                                seteuid(getuid());
                                piece = new("/clone/misc/piece");
                                piece->set_name(query("name", victim_w)+"的碎片",({query("id", victim_w),"piece"}));
                                piece->move(environment(victim));
                                set("long", "一堆破碎物事，好像是兵器碎片。\n", piece);
                                destruct(victim_w);
                                return HIB "你聽到「叮噹」一聲兵刃破碎的聲音，兵器碎片濺了一地！\n" NOR;
                        }
                        else return HIR"可惜你沒用法輪，沒法砸碎對方兵器！\n"NOR;
                }
        }
}
*/
mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon, weapon1;  object master;
        weapon=query_temp("weapon", me);
        weapon1=query_temp("weapon", victim);

        if (weapon && weapon1
        &&  me->query_skill("riyue-lun",1)>150 && query("jiali", me )
        &&  query("neili", me)>1000
        // &&  random(10) >= 5
        &&  query("skill_type", weapon) == "hammer"
        &&  me->query_skill_mapped("parry") == "riyue-lun")
        {
                message_combatd(HIW"$N手臂暴長，施展「鎖」字訣，"+weapon->name()+
                                HIW"探出，嚓的一聲鎖住了$n"+weapon1->name()+HIW"。\n"NOR,
                                me, victim);

                if (random(me->query_str()) > victim->query_str())
                {
                        addn("neili", -100, me);
                        message_combatd(HIG+query("name", me)+"運勁回拉，$n臂骨喀的一聲，險些就被拉斷，劇痛之下手一鬆，"+
                                        weapon1->name()+HIG"被奪了過去！\n"NOR, me, victim);
                        weapon1->unequip();
                        weapon1->move(me);
                } else
                if (random(me->query_str()) > victim->query_str() / 2)
                {
                        addn("neili", -50, me);
                        message_combatd(HIG+query("name", me)+"運勁回拉，$N被帶得踉蹌幾步，但覺虎口劇痛，"+
                                        weapon1->name()+HIG"脱手飛出！\n"NOR, victim);
                        weapon1->unequip();
                        weapon1->move(environment(victim));
                } else
                if( query_temp("shield", victim) )
                {
                        addn("neili", -50, me);
                        message_combatd(HIY"$N借勢前衝，"+weapon1->name()+HIY"直刺過去，但被"+
                                        query("name", victim)+"護體真氣蕩得滑了開去。\n"NOR,victim);
                }

                else message_combatd(HIY"$N借勢前衝，"+weapon->name()+HIY"直刺"+query("name", victim)+"，"+
                                        query("name", victim)+"變招奇快，"+weapon->name()+HIY"一抖鬆脱，縱身退了開去。\n"NOR,
                                        victim);
        }
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
        int d_e1 = 20;
        int d_e2 = 40;
        int p_e1 = -40;
        int p_e2 = -20;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 100;
        int m_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);
        string str, message;
        if (weapon)
        {
                if( query("id", weapon) == "jin lun" )
                        str = "金輪";
                else if( query("id", weapon) == "yin lun" )
                        str = "銀輪";
                else if( query("id", weapon) == "fa lun" )
                        str = "法輪";
                else str = weapon->name();
                message = msg[random(sizeof(msg))];
                message = replace_string(message, "$w", str);
                switch(str)
                {
                case "金輪" :
                        message = HIY+message+NOR; break;
                case "銀輪" :
                        message = HIW+message+NOR; break;
                case "法輪" :
                        message = HIC+message+NOR; break;
                default : break;
                }
                return ([
                        "action" : message,
                        "damage" : 300,
                        "damage_type" : random(2)?"砸傷":"瘀傷",
                        "dodge" : -100,
                        "parry" : -100,
                        "attack": 200,
                ]);
        }
        lvl = (int) me->query_skill("riyue-lun", 1);
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
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"riyue-lun/" + action;
}

int help(object me)
{
        write(HIC"\n日月輪法："NOR"\n");
        write(@HELP

    日月輪法為金輪法王的武功，是雪山寺極為霸道的功夫。

        學習要求：
                龍相般若功20級
                內力100
HELP
        );
        return 1;
}
