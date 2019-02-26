// taiji-jian.c 太極劍法

#include <ansi.h>;
#include <combat.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

int taiji(object me, object victim, object weapon, int damage);
int raozhi(object me, object victim, object weapon, int damage);

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

string *parry_msg = ({
         "$p左手劍訣斜引，$W橫過，畫了個半圈，平搭在$P$w之上，勁力傳出，$w登時一沉。\n",
         "$p$W交左手，在身前劃了兩個圓圈，$P見$p劍勁連綿，護住全身，竟無半分空隙。\n",
         "$p劍招未曾使老，已然圈轉。突然之間，$P眼前出現了幾個白色光圈，大圈小圈，正圈斜圈，閃爍不已。$P眼睛一花，只好回招。\n",
         "$p當下凝神專志，將一套太極劍法使得圓轉如意，嚴密異常的守住門户。\n",
         "$p以太極劍中「雲麾三舞」三式解開。$P見$p化解時舉重若輕，深得內家劍術三昧，不待$p回手，跳開一步。\n"
});
string *taiji_msg = ({
         "$N當下左足踏上，劍交左手，一招「三環套月」，虛虛實實，以左手劍攻敵，劍尖上光芒閃爍，嗤嗤嗤的發出輕微響聲",
         "$N劍法吞吐開合、陰陽動靜，將太極劍法中最精要之處都發揮了出來，功勁一加運開，綿綿不絕",
         "$N左手$w緩緩向前劃出，成一弧形。$n只覺一股森森寒氣，直逼過來",
         "$N右手捏著劍訣，左手$w不住抖動，突然平刺，劍尖急顫，看不出攻向何處。$P這一招中籠罩了$n上盤七大要穴",
         "$N劍招未曾使老，已然圈轉。突然之間，$n眼前出現了幾個白色光圈，大圈小圈，正圈斜圈，閃爍不已",
         "$N劍上所幻的光圈越來越多，過不多時，$P全身已隱在無數光圈之中，光圈一個未消，另一個再生。\n$w雖使得極快，卻聽不到絲毫金刃劈風之聲，足見劍勁之柔韌已達於化境",
         "$n只覺似有千百柄$w護住了$N全身。$N純採守勢，端的是絕無破綻。\n可是這座劍鋒所組成的堡壘卻能移動，千百個光圈猶如浪潮一般，緩緩湧來",
         "$N並非一招一招的相攻，而是以數十招劍法混成的守勢，同時化為攻勢，使$n無法抵禦"
});
mapping *action = ({
([      "action" : "$N虛步提腰，一招"+(order[random(13)])+"「蜻蜓點水」"NOR"，手中$w輕輕顫動，一劍劍點向$n的$l",
        "lvl" : 0,
        "skill_name" : "蜻蜓點水"
]),
([      "action" : "$N向前跨上一步，左手劍訣，右手$w使出一式"+(order[random(13)])+"「指南針」"NOR"直刺$n的$l",
        "lvl" : 4,
        "skill_name" : "指南針"
]),
([      "action" : "$N身形往右一挫，左手劍訣，右手$w使出一式"+(order[random(13)])+"「大魁星」"NOR"刺向$n的$l",
        "lvl" : 9,
        "skill_name" : "大魁星"
]),
([      "action" : "$N雙膝下沉，右手$w使出一式"+(order[random(13)])+"「探海式」"NOR"，由下而上疾刺$n的$l",
        "lvl" : 14,
        "skill_name" : "探海式"
]),
([      "action" : "$N一招"+(order[random(13)])+"「燕子掠波」"NOR"，$w自上而下劃出一個大弧，平平地向$n的$l揮
去",
        "lvl" : 19,
        "skill_name" : "燕子掠波"
]),
([      "action" : "$N上身往左側一擰，一招"+(order[random(13)])+"「烏龍擺尾」"NOR"，右手$w反手向$n的$l揮去",
        "lvl" : 24,
        "skill_name" : "烏龍擺尾"
]),
([      "action" : "$N一招"+(order[random(13)])+"「右攔掃」"NOR"，一招"+(order[random(13)])+"「左攔掃」"NOR"，劍鋒平指，一氣呵成橫掃$n的
$l",
        "lvl" : 29,
        "skill_name" : "右攔掃左攔掃"
]),
([      "action" : "$N左腿提膝，手中$w斜指，一招"+(order[random(13)])+"「宿鳥投林」"NOR"刺向$n的$l",
        "lvl" : 34,
        "skill_name" : "宿鳥投林"
]),
([      "action" : "$N一招"+(order[random(13)])+"「青龍出水」"NOR"，$w自下而上劃出一個大弧，平平地揮向$n的$l",
        "lvl" : 39,
        "skill_name" : "青龍出水"
]),
([      "action" : "$N使出"+(order[random(13)])+"「三環套月」"NOR"，$w劃出三個圓圈，劍鋒直出，綿綿不斷划向$n
的$l",
        "lvl" : 44,
        "skill_name" : "三環套月"
]),
([      "action" : "$N一招"+(order[random(13)])+"「風捲荷葉」"NOR"，$w輕靈地劃出幾個圓弧，迅速地向$n的$l揮去",
        "lvl" : 49,
        "skill_name" : "風捲荷葉"
]),
([      "action" : "$N一招"+(order[random(13)])+"「虎抱頭」"NOR"，$w劃出一個左低右高的大弧，斜斜地斬向$n的$l",
        "lvl" : 54,
        "skill_name" : "虎抱頭"
]),
([      "action" : "$N使出"+(order[random(13)])+"「獅子搖頭」"NOR"，$w由右向左劃出一個大８字，將$n圈在其中",
        "lvl" : 59,
        "skill_name" : "獅子搖頭"
]),
([      "action" : "$N左腳踏實，右腳虛點，一招"+(order[random(13)])+"「仙人指路」"NOR"，右手$w帶着一團劍花，
逼向$n的$l",
        "lvl" : 64,
        "skill_name" : "仙人指路"
]),
([      "action" : "$N輕輕躍起，一招"+(order[random(13)])+"「野馬跳澗」"NOR"，$w在半空中化為一圈銀芒，落向$n
的$l",
        "lvl" : 69,
        "skill_name" : "野馬跳澗"
]),
([      "action" : "$N兩腿前箭後弓，一招"+(order[random(13)])+"「射雁式」"NOR"，右手$w直刺$n的$l",
        "lvl" : 74,
        "skill_name" : "射雁式"
]),
([      "action" : "$N一招"+(order[random(13)])+"「小魁星」"NOR"，身形往左一挫，左手劍訣，右手$w平平地向$n的
$l揮去",
        "lvl" : 79,
        "skill_name" : "小魁星"
]),
([      "action" : "$N猱身撲上，一招"+(order[random(13)])+"「白猿獻果」"NOR"，手中$w斜斜地向$n的$l揮去",
        "lvl" : 84,
        "skill_name" : "白猿獻果"
]),
([      "action" : "$N一招"+(order[random(13)])+"「迎風撣塵」"NOR"，$w看似隨意地一揮，$n卻陡覺一股勁氣迎面襲
來。",
        "lvl" : 89,
        "skill_name" : "迎風撣塵"
]),
([      "action" : "$N一招"+(order[random(13)])+"「順水推舟」"NOR"，$w自上而下劃出一個大弧，平平地向$n的$l揮
去。",
        "lvl" : 94,
        "skill_name" : "順水推舟"
]),
([      "action" : "$N一招"+(order[random(13)])+"「流星趕月」"NOR"，$w疾刺$n的$l",
        "lvl" : 99,
        "skill_name" : "流星趕月"
]),
([      "action" : "$N突然盤蹲下身來，一招"+(order[random(13)])+"「海底撈月」"NOR"，$w自下而上地向$n的$l揮去",
        "lvl" : 104,
        "skill_name" : "海底撈月"
]),
([      "action" : "$N一招"+(order[random(13)])+"「挑簾式」"NOR"，$w自下而上徐徐劃出一個大弧，平平地向$n的$l
揮去",
        "lvl" : 109,
        "skill_name" : "挑簾式"
]),
([      "action" : "$N一招"+(order[random(13)])+"「黃蜂入洞」"NOR"，$w自上而下劃出一個大弧，平平地向$n的$l揮
去",
        "lvl" : 114,
        "skill_name" : "黃蜂入洞"
]),
([      "action" : "$N一招"+(order[random(13)])+"「大鵬展翅」"NOR"，身形躍起，右手$w刺向$n的$l",
        "lvl" : 119,
        "skill_name" : "大鵬展翅"
]),
([      "action" : "$N一招"+(order[random(13)])+"「車輪劍」"NOR"，$w化作一片銀盤，平平地向$n的$l捲去",
        "lvl" : 124,
        "skill_name" : "車輪劍"
]),
([      "action" : "$N左腳輕點地面，身形往前一撲，一招"+(order[random(13)])+"「天馬行空」"NOR"，$w向$n的$l揮
去",
        "lvl" : 129,
        "skill_name" : "天馬行空"
]),
([      "action" : "$N一招"+(order[random(13)])+"「風掃梅花」"NOR"，身體躍在半空，手中$w掃向$n的$l",
        "lvl" : 90,
        "skill_name" : "風掃梅花"
]),
([      "action" : "$N一招"+(order[random(13)])+"「卻步抽劍」"NOR"，左腳躍步落地，$w回抽，反手勾向$n的$l",
        "lvl" : 139,
        "skill_name" : "卻步抽劍"
]),
([      "action" : "$N右腿半屈般蹲，一招"+(order[random(13)])+"「如封似閉」"NOR"，劍尖虛指，轉身撩向$n的$l",
        "lvl" : 144,
        "skill_name" : "如封似閉"
]),
([      "action" : "$N回身擰腰，右手虛抱，一招"+(order[random(13)])+"「撥雲瞻日」"NOR"，$w中宮直進，刺向$n的$l",
        "lvl" : 149,
        "skill_name" : "撥雲瞻日"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("int", me)<26 )
                return notify_fail("你先天悟性太差，難以領會太極劍的要詣。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("taiji-quan", 1) < 100)
                return notify_fail("你的太極拳火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法水平有限，無法修煉太極劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("taiji-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的太級劍法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的體力不夠練太極劍法。\n");

        if( query("neili", me)<75 )
                return notify_fail("你的內力不夠練太極劍法。\n");

        me->receive_damage("qi", 50);
        addn("neili", -64, me);
        return 1;
}
string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
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
        int d_e1 = -55;
        int d_e2 = -45;
        int p_e1 = -50;
        int p_e2 = -45;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 60;
        int m_e2 = 150;
        int i, lvl, seq, ttl = sizeof(action), busy_time;
        object victim;
        string *limbs, limb, target, msg;

        lvl = (int) me->query_skill("taiji-jian", 1);
        busy_time = lvl/20;
        if( objectp(victim = me->select_opponent()) )
        {
                limbs=query("limbs", victim);
                limb = limbs[random(sizeof(limbs))];
                target = victim->name();
        }

//////// 附加雙擊 yun taiji後的雙擊/////
        if( query_temp("double_attack", me) )
        {
                return ([
                        "action" : HIW"突然之間，$N劍交右手，寒光一閃，向$n$l劃出，這一下快速無倫"NOR,
                        "force"  : 350+random(100),
                        "dodge"  : -80,
                        "parry"  : -80,
                        "damage" : 200+random(50),
                        "damage_type" : "割傷" ]);
        }
////////太極劍 chan 好像沒用/////
        if( query_temp("chan/"+target, me) )
        {
                victim->start_busy(2);
                addn("neili", -20, me);
                addn_temp("chan/"+target, 1, me);

                if( query_temp("chan/"+target, me) >= busy_time )
                        delete_temp("chan/"+target, me);
        }
//////// perform raozhi後的雙（三）擊 ////
        if( random(query_temp("wudang/raozhi", me))>50 ||
                query_temp("raozhi_attack", me) )
        {
                switch(query_temp("raozhi_attack", me) )
                {
                        case 1: msg =HIY"不料錚的一聲輕響，$w"+HIY+"反彈過來，直刺向$p$l"NOR;
                                break;
                        case 2: msg =HIC"誰知$N於$w"HIC"上連催兩重勁，劍彎成弧，又是一彎，便如長蛇之遊，奇詭不可設想"NOR;
                                break;
                        default: msg = HIW"突然間$N$w"HIW"破空，疾刺$n"+limb+"，劍到中途，劍尖微顫，竟然彎了過去，斜刺$p$l"NOR;
                                break;
                }
                addn_temp("wudang/raozhi", -1, me);
                addn("neili", -25, me);
//              if( wizardp(me) )
//                      tell_object(me, sprintf("\nap: %d", COMBAT_D->skill_power(me, "sword", SKILL_USAGE_ATTACK)));
                return ([
                        "action": msg,
                        "dodge" : -100,
                        "parry" : -100,
                        "force" : 380+random(120),
                        "damage": 220+random(80),
                        "damage_type":"刺傷",
                        "post_action": (: raozhi :)
                ]);
        }
///////////yun taiji後的普通招////////////
        if( query_temp("taiji", me) && query("neili", me)>100 )
        {
                addn_temp("taiji_fight", 1, me);
                addn("neili", -10, me);
                return ([
                        "action": taiji_msg[random(sizeof(taiji_msg))],
                        "force" : 420+random(120),
                        "dodge" : -100-random(50),
                        "parry" : -100-random(50),
                        "damage": 220+random(80),
                        "damage_type" : random(2)?"刺傷":"割傷",
                        "post_action" : (: taiji :) ]);
        }
/////////// 都沒有的話/////////
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
int taiji(object me, object victim, object weapon, int damage)
{
        int n = random(2);

        if( damage == RESULT_DODGE )
        {
                if( n == 0 && me->query_skill_mapped("unarmed") == "taiji-quan"
                && me->query_skill_prepared("unarmed") == "taiji-quan" )
                {
                        set_temp("double_attack", 1, me);
                        weapon->unequip();
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                        weapon->wield();
                }
                else
                {
                        set_temp("double_attack", 1, me);
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                        message_combatd("\n$N又是劍交左手，在身前劃了兩個圓圈。$n見$P劍勁連綿，護住全身，竟無半分空隙。\n"NOR,me,victim);
                }
                delete_temp("double_attack", me);
                return 1;
        }
        else if( damage <= 0 )
        {
                message_combatd("$p但覺$P劍上有股綿勁，震得自己手臂隱隱發麻。\n", me, victim);
//              if( !victim->is_busy() )
//              victim->start_busy(1+random((int)(me->query_skill("force")/150)));
                addn("neili", -(me->query_skill("force")/10), victim);
        }
        return 1;
}
int raozhi(object me, object victim, object weapon, int damage)
{
        int level = (int)me->query_skill("taiji-jian", 1)/2;
        string ductile;

        if( !objectp(weapon) ) return 1;
        ductile=query("id", weapon);
        addn_temp("raozhi_attack", 1, me);

        if( damage == RESULT_DODGE && query_temp("raozhi_attack", me)<3 )
        {
                addn_temp("apply/attack", level, me);

                if( query_temp("raozhi_attack", me) == 1 ||
                        ( (ductile == "bailong jian" || ductile == "ruanjian"
                                 || ductile == "shuixinjian") && query("neili", me)>500) )
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me),TYPE_QUICK);
                else delete_temp("raozhi_attack", me);

                addn_temp("apply/attack", -level, me);
                return 1;
        }
        else delete_temp("raozhi_attack", me);
        return 1;
}
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        object m_weapon;

        if ((int) me->query_skill("taiji-jian", 1) < 100 ||
            !(m_weapon=query_temp("weapon", me)) ||
            !living(me) || query("skill_type", m_weapon) != "sword" )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("taiji-jian", 1);

        if (ap / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "一抖手中的" + m_weapon->name() +
                                            HIC "，劃出了一個圓圈，竟然讓$N" +
                                            HIC "的攻擊全然落空。\n" NOR]);
                        break;

                case 1:
                        result += (["msg" : HIC "$n" HIC "手中" + m_weapon->name() + HIC
                                            "輕挑，正指向$N" HIC "攻勢中的破綻。\n" NOR]);
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "晃動手中的" + m_weapon->name() +
                                            HIC "，不住的變幻劍勢，讓$N"
                                            HIC "完全無法捕捉到力道。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "$n" HIY "一抖手中的" + m_weapon->name() +
                                 HIY "，劃出了一個圓圈，$N"
                                 HIY "理也不理，當即揮招直入，進襲$n"
                                 HIY "！\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "手中" + m_weapon->name() + HIY "輕挑，"
                                 HIY "正指向$N" HIY "攻勢中的破綻，可是$N"
                                 HIY "身形一變，破綻立刻不成為破綻。\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "晃動手中的" + m_weapon->name() +
                                 HIY "，不住的變幻劍勢，然而$N"
                                 HIY "算理深厚，精演天數，絲毫不受$n"
                                 HIY "的迷惑。\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}
int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }
int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( !objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("taiji-jian", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

string perform_action_file(string action)
{
        return __DIR__"taiji-jian/" + action;
}
int help(object me)
{
        write(HIC"\n太極劍法："NOR"\n");
        write(@HELP

    和太極拳武學原理相同，亦是張三丰祖師晚年時閉關悟得，劍
勢圓融，並無固定招式，講究以無招勝有招，招名乃是後人所加。
太極劍法有了一定修為後，需相當的太極拳基礎，方可上進。

        學習要求：
                太極拳20級
                太極神功20級
                內力100
HELP
        );
        return 1;
}
