// Written by Lonely@nitan.org
// pixie-jian

#include <ansi.h>
inherit FORCE;

int valid_force(string force)
{
        return force == "riyue-xinfa" || force == "riyue-guanghua" || force == "kuihua-xinfa";
}

string *dodge_msg = ({
        "突然之間，白影急幌，$n向後滑出丈餘，立時又回到了原地，躲過了$N這一招。\n",
        "$n手臂迴轉，在$N手肘下一推，順勢閃到一旁。\n",
        "$n右手伸出，在$N手腕上迅速無比的一按，順勢跳到一旁。\n",
        "$n身形飄忽，有如鬼魅，轉了幾轉，移步到$N的身後，躲過了$N這一招。\n",
        "$N只覺眼前一花，似乎見到$n身形一幌，但隨即又見$n回到原地，卻似從未離開。\n",
        "$N眼睛一花，$n已沒了蹤影。突然$n從身後拍了一下$N的頭，輕輕躍開。\n",
        "$n嫣然一笑，詭異之極，$N竟不知如何是好，停住了攻擊。\n",
});

string *finger_name = ({ "左手中指", "左手無名指", "左手食指",
                         "右手中指", "右手無名指", "右手食指", });

mapping *weapon_action = ({
([      "action":"突然之間，白影急幌，$N向後滑出丈餘，立時又回到了原地",
        "force" : 160,
        "attack": 40,
        "parry" : 30,
        "dodge" : 120,
        "damage": 150,
        "lvl" : 0,
        "skill_name" : "白影急幌",
        "damage_type":  "刺傷"
]),
([      "action":"$N右手伸出，在$n手腕上迅速無比的一按，$n險些擊中自己小腹",
        "force" : 180,
        "attack": 50,
        "parry" : 30,
        "dodge" : 135,
        "damage": 160,
        "lvl" : 20,
        "skill_name" : "自己小腹",
        "damage_type":  "刺傷"
]),
([      "action":"驀地裏$N猱身而上，躥到$n的身後，又躍回原地",
        "force" : 225,
        "attack": 60,
        "parry" : 35,
        "dodge" : 155,
        "damage": 170,
        "lvl" : 40,
        "skill_name" : "猱身而上",
        "damage_type":  "刺傷"
]),
([      "action":"$N突然間招法一變，$w忽伸忽縮，招式詭奇絕倫。$n驚駭之中方寸大亂",
        "force" : 230,
        "attack": 70,
        "parry" : 40,
        "dodge" : 160,
        "damage": 180,
        "lvl" : 60,
        "skill_name" : "招法一變",
        "damage_type":  "刺傷"
]),
([      "action":"$N身形飄忽，有如鬼魅，轉了幾轉，移步到$n的左側",
        "force" : 240,
        "attack": 80,
        "parry" : 50,
        "dodge" : 170,
        "damage": 200,
        "lvl" : 80,
        "skill_name" : "有如鬼魅",
        "damage_type":  "刺傷"
]),
([      "action":"$N一聲冷笑，驀地裏疾衝上前，一瞬之間，與$n相距已不到一尺，$w隨即遞出",
        "force" : 260,
        "attack": 70,
        "parry" : 40,
        "dodge" : 165,
        "damage": 220,
        "lvl" : 100,
        "skill_name" : "疾衝上前",
        "damage_type":  "刺傷"
]),
([      "action":"$N喝道：“好！”，便即拔出$w，反手刺出，跟着轉身離去",
        "force" : 300,
        "attack": 90,
        "parry" : 45,
        "dodge" : 180,
        "damage": 230,
        "lvl" : 120,
        "skill_name" : "反手刺出",
        "damage_type":  "刺傷"
]),
([      "action":"$n只覺眼前一花，似乎見到$N身形一幌，但隨即又見$N回到原地，卻似從未離開",
        "force" : 340,
        "attack": 80,
        "parry" : 40,
        "dodge" : 185,
        "damage": 250,
        "lvl" : 140,
        "skill_name" : "眼前一花",
        "damage_type":  "刺傷"
]),
([      "action":"$N向後疾退，$n緊追兩步，突然間$N閃到$n面前，手中$w直指$n的$l",
        "force" : 380,
        "attack": 100,
        "parry" : 50,
        "dodge" : 190,
        "damage": 270,
        "lvl" : 160,
        "skill_name" : "向後疾退",
        "damage_type":  "刺傷"
]),
([      "action":"$N驀地衝到$n面前，手中$w直刺$n右眼！$n慌忙招架，不想$N的$w突然轉向",
        "force" : 410,
        "attack": 130,
        "parry" : 55,
        "dodge" : 210,
        "damage": 300,
        "lvl" : 180,
        "skill_name" : "直刺右眼",
        "damage_type":  "刺傷"
]),
([      "action":"$N飛身躍起，$n抬眼一望，但見得$N從天直落而下，手中$w刺向$n的$l",
        "force" : 440,
        "attack": 130,
        "parry" : 50,
        "dodge" : 230,
        "damage": 320,
        "lvl" : 200,
        "skill_name" : "飛身躍起",
        "damage_type":  "刺傷"
]),
([      "action":"$N腰枝猛擺，$n眼前彷彿突然出現了七八個$N，七八隻$w一起刺向$n",
        "force" : 480,
        "attack": 140,
        "parry" : 60,
        "dodge" : 270,
        "damage": 340,
        "lvl" : 220,
        "skill_name" : "腰枝猛擺",
        "damage_type":  "刺傷"
]),
});

mapping *unarmed_action = ({
([      "action":"突然之間，白影急幌，$N向後滑出丈餘，立時又回到了原地",
        "force" : 100,
        "attack": 40,
        "parry" : 20,
        "dodge" : 70,
        "damage": 50,
        "lvl" : 0,
        "skill_name" : "白影急幌",
        "damage_type":  "刺傷"
]),
([      "action":"$N右手伸出，在$n手腕上迅速無比的一按，$n險些擊中自己小腹",
        "force" : 120,
        "attack": 50,
        "parry" : 30,
        "dodge" : 65,
        "damage": 60,
        "lvl" : 12,
        "skill_name" : "自己小腹",
        "damage_type":  "刺傷"
]),
([      "action":"驀地裏$N猱身而上，躥到$n的身後，又躍回原地",
        "force" : 125,
        "attack": 60,
        "parry" : 35,
        "dodge" : 85,
        "damage": 70,
        "lvl" : 25,
        "skill_name" : "猱身而上",
        "damage_type":  "刺傷"
]),
([      "action":"$N突然間招法一變，手臂忽伸忽縮，招式詭奇絕倫。$n驚駭之中方寸大亂",
        "force" : 130,
        "attack": 70,
        "parry" : 40,
        "dodge" : 60,
        "damage": 80,
        "lvl" : 5,
        "skill_name" : "招法一變",
        "damage_type":  "刺傷"
]),
([      "action":"$N身形飄忽，有如鬼魅，轉了幾轉，移步到$n的左側",
        "force" : 140,
        "attack": 80,
        "parry" : 50,
        "dodge" : 70,
        "damage": 100,
        "lvl" : 35,
        "skill_name" : "有如鬼魅",
        "damage_type":  "刺傷"
]),
([      "action":"$N一聲冷笑，驀地裏疾衝上前，一瞬之間，與$n相距已不到一尺，手指隨即刺出",
        "force" : 160,
        "attack": 70,
        "parry" : 40,
        "dodge" : 65,
        "damage": 120,
        "lvl" : 45,
        "skill_name" : "疾衝上前",
        "damage_type":  "刺傷"
]),
([      "action":"$N喝道：“好！”，便即反手刺出一指，跟着轉身離去",
        "force" : 200,
        "attack": 90,
        "parry" : 45,
        "dodge" : 80,
        "damage": 130,
        "lvl" : 55,
        "skill_name" : "反手刺出",
        "damage_type":  "刺傷"
]),
([      "action":"$n只覺眼前一花，似乎見到$N身形一幌，但隨即又見$N回到原地，卻似從未離開",
        "force" : 190,
        "attack": 80,
        "parry" : 40,
        "dodge" : 85,
        "damage": 150,
        "lvl" : 65,
        "skill_name" : "眼前一花",
        "damage_type":  "刺傷"
]),
([      "action":"$N向後疾退，$n緊追兩步，突然間$N閃到$n面前，手掌忽的劈向$n的$l",
        "force" : 180,
        "attack": 100,
        "parry" : 50,
        "dodge" : 70,
        "damage": 170,
        "lvl" : 75,
        "skill_name" : "向後疾退",
        "damage_type":  "震傷"
]),
([      "action":"$N驀地衝到$n面前，指尖直刺$n右眼！$n慌忙招架，不想$N的手腕突然轉向",
        "force" : 250,
        "attack": 130,
        "parry" : 55,
        "dodge" : 74,
        "damage": 200,
        "lvl" : 85,
        "skill_name" : "直刺右眼",
        "damage_type":  "震傷"
]),
([      "action":"$N飛身躍起，$n抬眼一望，但見得$N從天直落而下，揮掌砍向$n的$l",
        "force" : 340,
        "attack": 130,
        "parry" : 50,
        "dodge" : 80,
        "damage": 220,
        "lvl" : 94,
        "skill_name" : "飛身躍起",
        "damage_type":  "震傷"
]),
([      "action":"$N腰枝猛擺，$n眼前彷彿突然出現了七八個$N，七八隻手掌一起拍向$n",
        "force" : 400,
        "attack": 140,
        "parry" : 60,
        "dodge" : 110,
        "damage": 240,
        "lvl" : 120,
        "skill_name" : "腰枝猛擺",
        "damage_type":  "震傷"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" ||
               usage == "dodge" ||
               usage == "parry" ||
               usage == "force" ||
               usage == "unarmed";
}

int double_attack() { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("pixie-jian", 1);
        return lvl * lvl * 17 * 15 / 100 / 200;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(weapon_action) - 1; i >= 0; i--)
                if (level >= weapon_action[i]["lvl"])
                        return weapon_action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -60;
        int d_e2 = -40;
        int p_e1 = -80;
        int p_e2 = -60;
        int f_e1 = 150;
        int f_e2 = 230;
        int m_e1 = 240;
        int m_e2 = 340;
        int i, lvl, seq, ttl;
        mapping *action;

        if (objectp(weapon))
                action = weapon_action;
        else
                action = unarmed_action;

        ttl = sizeof(action);
        lvl = (int) me->query_skill("pixie-jian", 1);
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
                "damage_type" : action[seq]["damage_type"],
        ]);
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        if( query("character", me) == "光明磊落" ||
            query("character", me) == "狡黠多變" )
                return notify_fail("你心中暗道：這辟邪劍法損人損己，修煉來何用。\n");

        if( query("gender", me) == "女性" &&
            !query("special_skill/ghost", me) )
                return notify_fail("自古以來沒聽説過女人可以修習葵花寶典。\n");

        if( query("gender", me) == "男性" &&
            !query("special_skill/ghost", me) )
        {
                me->receive_wound("qi", 50);
                return notify_fail(HIR "\n你試着修煉辟邪劍法，霎時只覺內息忽然大"
                                   "亂，幾欲焚身。\n" NOR);
        }

        /*
        if( !query("family/family_name", me) ||
            query("family/family_name", me) != "日月神教" )
                return notify_fail("辟邪劍法只有日月神教的人方能領會。\n");
        */

        if( query("int", me)<34 )
                return notify_fail("你的天資不足，無法理解辟邪劍法的深意。\n");

        if( query("dex", me)<32 )
                return notify_fail("你先天身法孱弱，難以修煉辟邪劍法。\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法造詣太淺，無法理解辟邪劍法。\n");

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail("你的基本輕功造詣太淺，無法理解辟邪劍法。\n");

        if (me->query_skill("parry", 1) < 100)
                return notify_fail("你的基本架造造詣太淺，無法理解辟邪劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("pixie-jian", 1))
                return notify_fail("你的基本劍法造詣有限，無法理解更高深的辟邪劍法。\n");

        if (me->query_skill("dodge", 1) < me->query_skill("pixie-jian", 1))
                return notify_fail("你的基本輕功造詣有限，無法理解更高深的辟邪劍法。\n");

        if (me->query_skill("parry", 1) < me->query_skill("pixie-jian", 1))
                return notify_fail("你的基本招架造詣有限，無法理解更高深的辟邪劍法。\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("pixie-jian", 1))
                return notify_fail("你的基本拳腳造詣有限，無法理解更高深的辟邪劍法。\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("pixie-jian", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("pixie-jian", 1);

        if (ap / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIR "$N" HIR "眼睛一花，$n" HIR "已沒了蹤"
                                            "影。突然$n" HIR "從身後拍了一下$N" HIR "的"
                                            "頭，輕輕躍開。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "眼前一花，似乎見到$n" HIR "身"
                                            "形一晃，但隨即又見$n" HIR "回到原地，卻似"
                                            "從未離開。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIR "$n" HIR "身形飄忽，有如鬼魅，轉了幾轉"
                                            "，移步到$N" HIR "的身後，躲過了$N" HIR "這"
                                            "一招。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "突然間白影急晃，$n" HIR "向後滑出丈餘"
                                            "，立時又回到了原地，躲過了$N" HIR "這一招"
                                            "。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "$N" HIY "眼睛一花，$n" HIY "已沒了蹤影"
                                 "。可是$N" HIY "精通易理，絲毫不為所亂，儘自"
                                 "出招。\n" NOR;
                        break;
                case 1:
                        result = HIY "$N" HIY "眼前一花，似乎見到$n" HIY "身"
                                 "形一晃。$N" HIY "一聲冷笑，已瞬間看破招中虛"
                                 "實。\n" NOR;
                        break;
                case 2:
                        result = HIY "$n" HIY "身形飄忽，有如鬼魅，轉了幾轉，"
                                 "可是$N" HIY "理也不理，連續數招徑直攻出。\n"
                                 NOR;
                        break;
                default:
                        result = HIY "突然間白影急晃，$n" HIY "向後滑出丈餘，"
                                 "可是$N" HIY "不假思索，追身攻上，更是巧妙無"
                                 "方。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("pixie-jian", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 40;
        if (lvl < 200) return 60;
        if (lvl < 250) return 80;
        if (lvl < 300) return 100;
        if (lvl < 350) return 120;
        return 130;
}


void cimu_end(object me, object target)
{
        if( target && query_temp("block_msg/all", target) )
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "抹了抹流着的"
                                        HIR "鮮血" HIC "，終於能看"
                                        "見了。\n" NOR, target);

                        tell_object(target, HIR "你終於抹掉了眼前的"
                                            "鮮血，能看見了。\n" NOR);
                }
                delete_temp("block_msg/all", target);
        }
        return;
}

void poyuan_end(object me, object target)
{
        if (target && target->query_condition("no_perform"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "氣，臉色由白轉紅，看起來好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被擾亂的真氣"
                                            "慢慢平靜了下來。\n" NOR);
                }
                target->clear_condition("no_perform");
        }
        return;
}

void exert_end(object me, object target)
{
        if (target && target->query_condition("no_exert"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "氣，臉色由白轉紅，看起來好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到周身穴道不再疼痛，輕鬆多了。\n" NOR);
                }
                target->clear_condition("no_exert");
        }
        return;
}

mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        object weapon;
        string name;

        // 辟邪劍影特效
        if( random(20)<5 && query_temp("pixie-jian/pfm_jian", me) )
        {
                switch(random(8))
                {
                        case 0:
                                if( !query_temp("block_msg/all", victim) )
                                {
                                        set_temp("block_msg/all", 1, victim);
                                        call_out("cimu_end", 20, me, victim);
                                        message_combatd(HIR "$N" HIR "只覺雙目一陣劇痛，眼前一黑，就什麼"
                                               "也看不見了，頓時長聲痛極而呼。\n" NOR, victim);
                                }
                                break;
                        case 1:
                                if (! victim->query_condition("no_perform"))
                                {
                                        victim->apply_condition("no_perform", 5);
                                        call_out("poyuan_end", 15, me, victim);
                                        message_combatd(HIR "$N" HIR "只覺眼前寒芒一閃而過，隨即全身一陣"
                                                "刺痛，幾股血柱自身上射出。\n$N陡然間一提真氣，"
                                                "竟發現周身力道竟似渙散一般，全然無法控制。\n" NOR, victim);
                                }
                                break;
                        case 2:
                                set("jiali", 0, victim);
                                break;
                        case 3:
                                if (! victim->query_condition("no_exert"))
                                {                       
                                        victim->apply_condition("no_exert", 1);
                                        call_out("exert_end", 30, me, victim);
                                        message_combatd(HIR "$N" HIR "只覺寒光逼人，隨即全身一陣"
                                                "刺痛，氣門已傷。\n$N陡然間一提真氣，"
                                                "竟發現周身穴道具痛無比。\n" NOR, victim);
                                }
                                break;
                        default:
                                if (! victim->is_busy())
                                        victim->start_busy(8);                          
                                break;
                }
        }
        weapon=query_temp("weapon", me);

        if( query_temp("weapon", me) )
                name = "手中" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        attack_time = (int)(me->query_skill("pixie-jian", 1) / 40);

        if (attack_time > 8)
                attack_time = 8;

        if (me->is_busy()
           || ! living(victim)
           || random(3) > 0
           || damage_bonus < 120
           || query_temp("px_link", me)
           || query_temp("pixie-jian/hit_msg", me)
           || query("neili", me)<300
           || query_temp("action_flag", me) == 1
           || me->query_skill("pixie-jian", 1) < 120)
                return 0;

        if( query_temp("pixie-jian/pfm_jian", me) ) tell_object(me,HIG"---------------------------=\n"NOR);
        // 避免在使用Pfm時訊息重複
        if( !query_temp("pixie-jian/hit_msg", me) )
                message_combatd(HIW "\n霎時間只見$N" HIW "鬼魅般揉身衝上，" + name +
                               HIW "指指點點，宛如夜雨流星，連續刺向$n" HIW "！\n"
                               NOR, me, victim);

        //me->start_busy(1 + random(attack_time / 10));
        addn("neili", -200, me);
        set_temp("px_link", 1, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;
                COMBAT_D->do_attack(me, victim, weapon, 0);
        }
        delete_temp("px_link", me);
        return 1;
}

int practice_skill(object me)
{
        return notify_fail(HIC "辟邪劍法只能通過研習「辟邪劍譜」或「葵花"
                           "寶典」來學習。\n" NOR);
}

int difficult_level()
{
        return 800;
}

string perform_action_file(string action)
{
            return __DIR__"pixie-jian/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"pixie-jian/exert/" + action;
}
/*
void do_interlink(object me, object victim)
{
        int skill, i, j;
        object *enemy;
        object weapon;

        if( userp(me) && !query("reborn/times", me) )
                return;

        skill = me->query_skill("pixie-jian", 1);
        if( random(skill)>400 && objectp(weapon=query_temp("weapon", me)) )
        {
                enemy = me->query_enemy();
                if (! sizeof(enemy)) return;
                addn_temp("str", skill/10, me);
                addn_temp("dex", skill/10, me);
                // 對所有敵人均自動進行攻擊
                for (i = 0; i < sizeof(enemy); i++)
                {
                        for (j = 0; j < (skill / (60 * sizeof(enemy))); j++)
                        if( (me->is_fighting(enemy[i]) || enemy[i]->is_fighting(me)) && query("qi", enemy[i])>0 )
                        {
                                if (environment(me) == environment(enemy[i]))
                                {
                                        COMBAT_D->do_attack(me,enemy[i],query_temp("weapon", me),0);
                                }
                        } else break;
                }
                addn_temp("str", -skill/10, me);
                addn_temp("dex", -skill/10, me);
        }
}
*/

int help(object me)
{
        write(HIC"\n辟邪劍法："NOR"\n");
        write(@HELP

    要説辟邪劍法，就要從《葵花寶典》談起。

    《葵花寶典》是一位宦官所作。這樣一位大高手，為什麼在皇
宮中做太監，那是誰也不知道。至於寶典中所載的武功，卻是精深
之極，三百多年來，始終無一人能據書練成。百餘年前，這部寶典
為福建莆田少林寺下院所得。其時莆田少林寺方丈紅葉禪師，乃是
一位大智大慧的了不起人物，依照他的武功悟性，該當練成寶典上
所載武功才是。但他研究多年，直到逝世，始終沒有起始練寶典中
的武功。

    一日華山派的嶽肅和蔡子峯到莆田少林寺作客，偷看到《葵花
寶典》。其時匆匆之際，二人不及同時閲遍全書，當下二人分讀，
一人讀一半，後來回到華山，共同叁悟研討。不料二人將書中功夫
一加印證，竟然牛頭不對馬嘴，全然合不上來。二人都深信對方讀
錯了書，只有自己所記的才是對的。華山的劍氣二宗之分由此而起。

    紅葉禪師不久發現此事，他知道這部寶典所載武學不僅博大精
深，且蒹兇險之極。這最難的還是第一關，只消第一關能打通，到
後來也沒什麼。第一關只要有半點岔差，立時非死即傷。紅葉當下
派遣得意弟子渡元禪師前往華山，勸論嶽蔡二位，不可修習寶典中
的武學。

    渡元禪師上得華山，嶽蔡二人對他好生相敬，承認私閲《葵花
寶典》，一面深致歉意，一面卻以經中所載武學向他請教。殊不知
渡元雖是紅葉的得意弟子，寶典中的武學卻未蒙傳授。當下渡元禪
師並不點明，聽他們背誦經文，隨口加以解釋，心中卻暗自記下。
渡元禪師武功本極高明，又是絕頂機智之人，聽到一句經文，便己
意演繹幾句，居然也説來頭頭是道。

    不過嶽蔡二人所記的本已不多，經過這麼一轉述，不免又打了
折扣。渡元禪師在華山上住了八日，這才作別，但從此卻也沒再回
到莆田少林寺去。不久紅葉禪師就收到渡元禪師的一通書信，説道
他凡心難抑，決意還俗，無面目再見師父云云。

    由於這一件事，華山派弟子偷窺《葵花寶典》之事也流傳於外。
過不多時，魔教十長老來攻華山，在華山腳下一場大戰。魔教十長
老多身受重傷，大敗而去。但嶽肅和蔡子峯兩人均在這一役中斃命，
而二人所錄《葵花寶典》也被魔教奪了去。

    渡元禪師還俗之後，復了原姓，將法名顛倒過來取名遠圖，娶
妻生子，創立鏢局，在江湖上轟轟烈烈幹了一番事業。

    莆田少林寺的紅葉禪師園寂之時，召集門人弟子，説明這部寶
典的前因後果，便即將其投如爐中火化。紅葉説：這部武學祕笈精
妙奧妙，但其中許多關鍵之處，當年的撰作人並未能妥為叁通解透，
留下的難題太多。尤其是第一關難過，不但難過，簡直是不能過不
可過，流傳後世，實非武林之福。

    林遠圖的辟邪劍法，是從《葵花寶典》殘篇中悟出的武功，兩
者系出同源。辟邪劍法有七十二路，但一來從不外傳，二來使用此
劍法之人個個動作迅捷詭異，外間無人得知其招法的名目，只知道
其招式乃匪夷所思。林遠圖所自錄的《辟邪劍譜》加了許多自己的
解釋，故較魔教所藏的《葵花寶典》易入門，但少了些內容。所以
玩家欲習此功，當遵循先易後難之序。致於如何得到這兩部武林祕
笈，則一直是江湖上避而不談的祕密。如泄露此祕，會招來殺身之
禍。

        學習要求：
                自宮做太監
HELP
        );
        return 1;
}
