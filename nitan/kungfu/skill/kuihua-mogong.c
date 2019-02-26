// kuihua-shengong 葵花魔功

inherit FORCE;
#include <ansi.h>

string *dodge_msg = ({
        "$n微微一動，已然遠去，使$N的進攻全然無用。\n",
        "$n霎時間平移了數步，如鬼如魅，使$N全然無法掌握。\n",
        "$n忽的一退，閃去天下任何追擊。\n",
        "$n足不離地，腰肢猛擺，居然將$N的進攻全部躲過。\n",
});

string *finger_name = ({ "左手中指", "左手無名指", "左手食指",
                         "右手中指", "右手無名指", "右手食指", });

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("kuihua-mogong", 1);
        return lvl * lvl / 10 / 20 * 18 * 15 / 100;
}

mapping *actionf = ({
([      "action":"$N倏的近前，身形快極，手指戳向$n的$l",
        "force" : 410,
        "attack": 182,
        "dodge" : 215,
        "parry" : 60,
        "damage": 190,
        "damage_type":  "刺傷"
]),
([      "action":"$N撲向前來，身形如同鬼魅，令人難以捉摸，手指忽的刺向$n的$l",
        "force" : 410,
        "attack": 180,
        "dodge" : 224,
        "parry" : 70,
        "damage": 200,
        "damage_type":  "刺傷"
]),
([      "action":"$N身形一轉，手指刺出，直指$n的$l",
        "force" : 430,
        "attack": 175,
        "dodge" : 220,
        "parry" : 50,
        "damage": 210,
        "damage_type":  "刺傷"
]),
([      "action":"$N飄然遠去，忽又進前，速度快的不可思議，一指如閃電般刺向$n的$l",
        "force" : 445,
        "attack": 180,
        "dodge" : 255,
        "parry" : 65,
        "damage": 190,
        "damage_type":  "刺傷"
]),
([      "action":"$N身體一晃，突然飛起一腳，踢向$n的$l",
        "force" : 450,
        "attack": 200,
        "dodge" : 250,
        "parry" : 55,
        "damage": 200,
        "damage_type":  "瘀傷"
]),
([      "action":"$N足下疾走，身形變幻莫測，突然一指插向$n的$l",
        "force" : 450,
        "attack": 215,
        "dodge" : 285,
        "parry" : 55,
        "damage": 220,
        "damage_type":  "刺傷"
]),
});

mapping *actionw = ({
([      "action":"$N倏的近前，身形快極，手中的$w戳向$n的$l",
        "force" : 460,
        "attack": 200,
        "dodge" : 150,
        "parry" : 40,
        "damage": 300,
        "damage_type":  "刺傷"
]),
([      "action":"$N撲向前來，身形如同鬼魅，令人難以捉摸，手中的$w忽的刺向$n的$l",
        "force" : 490,
        "attack": 185,
        "dodge" : 160,
        "parry" : 45,
        "damage": 300,
        "damage_type":  "刺傷"
]),
([      "action":"$N身形一轉，$w刺出，直指$n的$l",
        "force" : 465,
        "attack": 210,
        "dodge" : 180,
        "parry" : 45,
        "damage": 300,
        "damage_type":  "刺傷"
]),
([      "action":"$N飄然遠去，忽又進前，速度快的不可思議，$w如閃電般刺向$n的$l",
        "force" : 480,
        "attack": 190,
        "dodge" : 195,
        "parry" : 55,
        "damage": 300,
        "damage_type":  "刺傷"
]),
([      "action":"$N身體一晃，突然飛起一腳踢向$n的下陰，驀的又收回，反手$w刺向$n的$l",
        "force" : 500,
        "attack": 220,
        "dodge" : 180,
        "parry" : 57,
        "damage": 300,
        "damage_type":  "刺傷"
]),
([      "action":"$N足下疾走，身形變幻莫測，突然一揚手，$w飛也似的插向$n的$l",
        "force" : 520,
        "attack": 260,
        "dodge" : 195,
        "parry" : 50,
        "damage": 300,
        "damage_type":  "刺傷"
]),
});

string *usage_skills = ({ "finger", "sword", "dodge",
                          "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_combo(string combo)
{
        return combo == "kuihua-mogong";
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        if( query("combat_exp", me)<3000000 )
                return notify_fail("你覺得葵花魔功深奧之極，"
                                   "憑自己的戰鬥經驗一時間難以領會。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 150)
                return notify_fail("你覺得葵花魔功過於深奧之極，以"
                                   "自己的武學修養全然無法明白。\n");

        if( query("character", me) != "陰險奸詐" && query("character", me) != "國士無雙"
            && query("character", me) != "心狠手辣" )
                return notify_fail("你看了葵花魔功這些陰險毒辣的武功，不"
                                   "由的心驚肉跳，難以領會。\n");

        if( query("dex", me)<22 && me->query_dex()<61 )
                return notify_fail("你覺得自己的身法不夠靈動，不可能掌握這麼飄緲"
                                   "玄奇的葵花魔功。\n");

        /*
        if( query("int", me)<34 )
                return notify_fail("你覺得自己的先天悟性不夠，不可能領悟這麼高深"
                                   "玄奇的葵花魔功。\n");
        */

        level = me->query_skill("kuihua-mogong", 1);

        if ((int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("你覺得自己的武學修養有限，難以領會更高深的葵花魔功。\n");

        for (i = 0; i < sizeof(usage_skills); i++)
                if (me->query_skill(usage_skills[i], 1) < level)
                        return notify_fail("你對" + to_chinese(usage_skills[i]) +
                                           "的理解還不夠，無法繼續領會更高深的葵花魔功。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("葵花魔功博大精深，無法簡單的通過練習進步。\n");
}

int difficult_level()
{
        return 1600;
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("kuihua-mogong", 1);
        if (lvl <= 200) return 70;
        if (lvl < 250) return 90;
        if (lvl < 300) return 100;
        if (lvl < 350) return 115;
        return 130;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("kuihua-mogong", 1) < 210 ||
            ! living(me) ||
            me->query_skill_mapped("dodge") != "kuihua-mogong")
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("kuihua-mogong", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIW "$N" HIW "眼睛一花，$n" HIW "已沒了蹤"
                                            "影。突然$n" HIW "從身後拍了一下$N" HIW "的"
                                            "頭，輕輕躍開。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$N" HIW "眼前一花，似乎見到$n" HIW "身"
                                            "形一晃，但隨即又見$n" HIW "回到原地，卻似"
                                            "從未離開。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$n" HIW "尖嘯一聲，忽然身子一轉已不見了蹤影，$N" HIW
                                           "只覺耳邊風聲不斷，但隨即又見$n" HIW "回到了原地。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "忽然間，只見$n" HIW "腰枝一擺，頓時出現無數個"
                                            "$n" HIW "的影子，$N" HIW "卻無法辨別出$n" HIW "的方位。\n" NOR]);
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
                        result = HIY "突然間白影急晃，$n" HIY "身形頓時化分成萬千身影，"
                                 "可是$N" HIY "不假思索，追身攻上，更是巧妙無"
                                 "方。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}


mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        object weapon;
        string name;

        weapon=query_temp("weapon", me);

        if( query_temp("weapon", me) )
                name = "手中" + weapon->name();
        else
                name = finger_name[random(sizeof(finger_name))];

        attack_time = (int)(me->query_skill("kuihua-mogong", 1) / 40);

        if (attack_time > 9)
                attack_time = 9;

        if (me->is_busy()
           || random(3) == 0
           || ! living(victim)
           || victim->is_busy()
           || damage_bonus < 120
            || query("neili", me)<300
            || query_temp("action_flag", me )
           || me->query_skill("kuihua-mogong", 1) < 200)
                return 0;

        // 避免在使用Pfm時訊息重複
        if( !query_temp("kuihua-mogong/hit_msg", me) )
                message_vision(HIW "\n霎時間只見$N" HIW "身子猛擺，頓時化分為無數身影，" + name +
                               HIW "宛若流星般分從不同的方位同時刺向$n" HIW "！\n"
                               NOR, me, victim);

        addn("neili", -attack_time*30, me);
        set_temp("action_flag", 1, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;
                COMBAT_D->do_attack(me, victim, weapon, 0);
        }
        delete_temp("action_flag", me);

        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"kuihua-mogong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"kuihua-mogong/exert/" + action;
}