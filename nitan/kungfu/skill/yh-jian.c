#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
        "突然之間，微風吹過，$n身影一花，仿佛沒有任何動作，卻躲過了$N這一招。\n",
        "$n手掌一豎，$N覺得一股勁風撲面而來不禁眨了一下眼，再看時，$n已經換了個位置。\n",
        "$n手指一點，$N全身一麻，$n慢慢踱到一旁。\n",
        "$n身形飄忽，有如風中柳絮，飄了起來，飄到$N的身後，躲過了$N這一招。\n",
        "$N只覺眼前一花，似乎見到$n身形一幌，但隨即又見$n回到原地，卻似從未離開。\n",
        "$N眼睛一花，$n已沒了蹤影。突然$n從身後拍了一下$N的頭，輕輕躍開。\n",
        "$n輕輕一笑，高貴之極，$N竟不知如何是好，停住了攻擊。\n",
});

string *finger_name = ({ "左手中指", "左手無名指", "左手食指",
                         "右手中指", "右手無名指", "右手食指", }); 

mapping *action = ({
([          "action":"突然之間，微風輕拂，$N向後滑出丈余，立時又回到了原地", // 描述
            "force" : 1600,                                                   // 攻擊力
            "attack": 400,                                                    // 命中點
            "parry" : 300,                                                         // 如果該找可以做招架則招架點數
            "dodge" : 1200,                                                          // 輕功點數，同parry
            "damage": 1500,                                                         // 傷害力
            "lvl" : 0,                                                         // 發出該招要求的等級
            "skill_name" : "飄絮追風",                                       // 該找名字
            "damage_type":  "刺傷"                                           // 傷害類型
]),
([          "action":"$N右手伸出，在$n手腕上迅速無比的一按，$n險些擊中自己小腹",    
            "force" : 1800,
            "attack": 500,
            "parry" : 300,
            "dodge" : 1350,
            "damage": 1600,
            "lvl" : 20,
            "skill_name" : "黯然神傷",
            "damage_type":  "刺傷"
]),
([          "action":"驀地裡$N猱身而上，躥到$n的身後，又躍回原地",
            "force" : 2250,
            "attack": 600,
            "parry" : 350,
            "dodge" : 1550,
            "damage": 1700,
            "lvl" : 40,
            "skill_name" : "飄絮戲風",
            "damage_type":  "刺傷"
]),
([          "action":"$N突然間招法一變，$w忽伸忽縮，招式詭奇絕倫。$n驚駭之中方寸大亂",
            "force" : 2300,
            "attack": 700,
            "parry" : 400,
            "dodge" : 1600,
            "damage": 1800,
            "lvl" : 60,
            "skill_name" : "隨風擺柳",
            "damage_type":  "刺傷"
]),
([          "action":"$N身形飄忽，有如柳絮，轉了幾轉，移步到$n的左側",
            "force" : 2400,
            "attack": 800,
            "parry" : 500,
            "dodge" : 1700,
            "damage": 2000,
            "lvl" : 80,
            "skill_name" : "風中飄絮",
            "damage_type":  "刺傷"
]),
([          "action":"$N一聲冷笑，驀地裡疾沖上前，一瞬之間，與$n相距已不到一尺，$w隨即遞出",
            "force" : 2600,
            "attack": 700,
            "parry" : 400,
            "dodge" : 1650,
            "damage": 2200,
            "lvl" : 100,
            "skill_name" : "迎風而上",
            "damage_type":  "刺傷"
]),
([          "action":"$N喝道：“好！”，便即拔出$w，反手刺出，跟著轉身離去",
            "force" : 3000,
            "attack": 900,
            "parry" : 450,
            "dodge" : 1800,
            "damage": 2300,
            "lvl" : 120,
            "skill_name" : "回首望月",
            "damage_type":  "刺傷"
]),
([          "action":"$n只覺眼前一花，似乎見到$N身形一幌，但隨即又見$N回到原地，卻似從未離開",
            "force" : 3400,
            "attack": 800,
            "parry" : 400,
            "dodge" : 1850,
            "damage": 2500,
            "lvl" : 140,
            "skill_name" : "飄絮亂眼",
            "damage_type":  "刺傷"
]),
([          "action":"$N向後疾退，$n緊追兩步，突然間$N閃到$n面前，手中$w直指$n的$l",
            "force" : 3800,
            "attack": 1000,
            "parry" : 500,
            "dodge" : 1900,
            "damage": 2700,
            "lvl" : 160,
            "skill_name" : "進退兩難",
            "damage_type":  "刺傷"
]),
([          "action":"$N驀地沖到$n面前，手中$w直刺$n右眼！$n慌忙招架，不想$N的$w突然轉向",
            "force" : 4100,
            "attack": 1300,
            "parry" : 550,
            "dodge" : 2100,
            "damage": 3000,
            "lvl" : 180,
            "skill_name" : "暗送秋波",
            "damage_type":  "刺傷"
]),
([          "action":"$N飛身躍起，$n抬眼一望，但見得$N從天直落而下，手中$w刺向$n的$l",
            "force" : 4400,
            "attack": 1300,
            "parry" : 500,
            "dodge" : 2300,
            "damage": 3200,
            "lvl" : 200,
            "skill_name" : "天外飛仙",
            "damage_type":  "刺傷"
]),
([          "action":"$N腰枝猛擺，$n眼前仿佛突然出現了七八個$N，七八只$w一起刺向$n",
            "force" : 4800,
            "attack": 1400,
            "parry" : 600,
            "dodge" : 2700,
            "damage": 3400,
            "lvl" : 220,
            "skill_name" : "柳枝輕搖",
            "damage_type":  "刺傷"
]),
});

// valid_enable()函數返回該技能可激發的種類
int valid_enable(string usage)
{
        return usage == "sword" ||
               usage == "dodge" ||
               usage == "parry" ||
               usage == "unarmed";
}

// 返回1表示該找可以一招兩式
int double_attack() { return 1; }

// 這個不用說了吧，是yanjiu和learn的時候調用的函數
int valid_learn(object me)
{
        if (wiz_level(me)==0)
                return notify_fail("不是巫師無法學習炎黃神劍。\n");
  
        if( query("int", me)<100 )
                return notify_fail("你的天資不足，無法理解炎黃神劍的深意。\n");

        if( query("dex", me)<100 )
                return notify_fail("你先天身法孱弱，難以修煉炎黃神劍。\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法造詣太淺，無法理解炎黃神劍。\n");

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail("你的基本輕功造詣太淺，無法理解炎黃神劍。\n");

        if (me->query_skill("parry", 1) < 100)
                return notify_fail("你的基本架造造詣太淺，無法理解炎黃神劍。\n");

        if (me->query_skill("sword", 1) < me->query_skill("yh-jian", 1))
                return notify_fail("你的基本劍法造詣有限，無法理解更高深的炎黃神劍。\n");

        if (me->query_skill("dodge", 1) < me->query_skill("yh-jian", 1))
                return notify_fail("你的基本輕功造詣有限，無法理解更高深的炎黃神劍。\n");

        if (me->query_skill("parry", 1) < me->query_skill("yh-jian", 1))
                return notify_fail("你的基本招架造詣有限，無法理解更高深的炎黃神劍。\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("yh-jian", 1))
                return notify_fail("你的基本拳腳造詣有限，無法理解更高深的炎黃神劍。\n");

        return 1;
}

// 這個是標準函數不需要修改
string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

// 這個是標準函數不需要修改
mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yh-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

// 返回閃避信息
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

// 被對方打中後調用的函數，比如將該招激發為招架或輕功
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("yh-jian", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("yh-jian", 1);

        if (ap / 2 + random(ap) < dp)
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
                        result += (["msg" : HIR "$n" HIR "身形飄忽，有如柳絮，隨風飄盪"
                                            "，飄到$N" HIR "的身後，躲過了$N" HIR "這"
                                            "一招。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "突然間白影急晃，$n" HIR "向後滑出丈余"
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
                                 "。可是$N" HIY "精通易理，絲毫不為所亂，盡自"
                                 "出招。\n" NOR;
                        break;
                case 1:
                        result = HIY "$N" HIY "眼前一花，似乎見到$n" HIY "身"
                                 "形一晃。$N" HIY "一聲輕笑，已瞬間看破招中虛"
                                 "實。\n" NOR;
                        break;
                case 2:
                        result = HIY "$n" HIY "身形飄忽，有如柳絮，隨風飄盪，"
                                 "可是$N" HIY "理也不理，連續數招徑直攻出。\n"
                                 NOR;
                        break;
                default:
                        result = HIY "突然間白影急晃，$n" HIY "向後滑出丈余，"
                                 "可是$N" HIY "不假思索，追身攻上，更是巧妙無"
                                 "方。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

// 當該招激發為輕功時的輕功效果
int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("yh-jian", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 60;
        if (lvl < 150) return 80;
        if (lvl < 200) return 120;
        if (lvl < 250) return 160;
        if (lvl < 300) return 200;
        if (lvl < 350) return 240;
        return 300;
}

// 當打中對方時調用的函數
mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        object weapon;
        string name;

        weapon=query_temp("weapon", me);

        if( query_temp("weapon", me) )
                name = "手中" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        attack_time = (int)(me->query_skill("yh-jian", 1) / 40);

        if (attack_time > 8)
                attack_time = 8;

        if (me->is_busy()
           || random(2) == 0
           || ! living(victim)
           || victim->is_busy()
           || damage_bonus < 120
            || query("neili", me)<300
            || query_temp("action_flag", me) == 0
           || me->query_skill("yh-jian", 1) < 120)
                return 0;

        // 避免在使用Pfm時訊息重復
        if( !query_temp("yh-jian/hit_msg", me) )
                message_vision(HIW "\n霎時間只見$N" HIW "鬼魅般揉身沖上，" + name +
                               HIW "指指點點，宛如夜雨流星，連續刺向$n" HIW "！\n"
                               NOR, me, victim);

        me->start_busy(1 + random(attack_time));
        addn("neili", -attack_time*20, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;
                COMBAT_D->do_attack(me, victim, weapon, 0);
        }

        return 1;
}

// 當練習該招時調用的函數
int practice_skill(object me)
{
        return notify_fail(HIC "炎黃神劍只能向[小寶乖乖]學習。\n" NOR);
}

// 該招的學習難度
int difficult_level()
{
        return 15000;
}

// 該招的perform文件位置__DIR__代表當前目錄；
string perform_action_file(string action)
{
        return __DIR__"yh-jian/" + action;
}