// This program is a part of NITAN MudLIB
// mingyu-gong.c

#include <ansi.h>

inherit FORCE;

int valid_force(string force) { return 1; }  
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("mingyu-gong", 1);
        return lvl /10 * lvl /10 * 15 * 28 / 10 / 20;
}
string *dodge_msg = ({
        "$N身形加速，電光挪移，饒是$n攻擊范圍既廣且厲，卻總能在間不容發的空隙避過",
        "$N空中快速轉折，在$n每次攻擊前又倏乎消失，一下子就脫出$n的攻擊范圍",        
        "$N只覺眼前一花，只見到$n身形一幌，自己的招數居然莫名其妙就落空了", 
        "$N憑著高速身法，在$n的攻擊范圍內進退趨避，險險閃過一道又一道的攻擊",
        "$N騰挪快速，竟然在空中形成身影殘像，有如無數$N一起挪動",
        "$n眼前忽然一花，眼前$N的身影似乎有些淡化，而另外一個$N竟爾出現在面前不足一尺的近處",
});

string *parry_msg = ({
        "眼看$n轉眼已攻至，$N輕描淡寫，卻又快絕無比，把$n的招式化于無形",
        "$n眼看得手之際，突覺一股陰柔勁道蝕$W急上，沒等接觸，整條手臂已劇痛起來，忙叫一聲不好，慌然急退",
        "$n陡覺手上勁力如泥牛入海，摸不著底處，暗叫不妙，$N卻又已經攻至",
        "$n心下一凜，但見對手守勢，如萬裡長空，曠遠不知其深，包容萬物，無從下手",
});


string *action_msg = ({
        "$N十指微張，看似簡單的，卻在張開的同時，爆發了沛然莫敵的沖擊力擊向$n",
        "$N運起明玉功，身體逐漸變得透明，森寒殺意如有實質，隔空鎖鎮住$n",
        "$N雙手一張一收，平實的一招卻讓$n有如處于漩渦之中，動彈不得",
        "$N將明玉功提至極限，一招一式，神妙無方，如天外神龍，縱橫來去",
        "$N手中$w幻化出點點星雨，逕自往四面八方洒去，形成無數小氣旋",
        "$n陡覺一股氣旋急壓而下，扯得自己身形不定，同時一股陰柔內勁夾於其，盡數封死了$n周遭退路",
        "$N一招擊中$n，同時一股陰柔內勁綿綿不絕的湧入$n的體內，侵筋蝕脈",
        "$N催運明玉功，，進似神龍矯捷，退若靈蛇竄動，$n只覺得眼花撩亂",
        "$N微一揚手，繞身明玉勁如毒蛇洪水似地爆起，群蛇亂舞，亂攻向$n",
        "$n只覺得股陰柔內勁傳來，跟著便是手上一沉，好似有什麼東西，讓手臂變成千斤重物，拖的自己直往前跌",
});

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 500 + random(120),
                "attack": 200 + random(60),
                "dodge" : -80 - random(60),
                "parry" : -80 - random(60),
                "damage" : 180 + random(60),
                "damage_type" : random(2)?"刺傷":"內傷",  
        ]);
}

string query_dodge_msg(string limb){        return dodge_msg[random(sizeof(dodge_msg))];}

string query_parry_msg(object weapon){        return parry_msg[random(sizeof(parry_msg))];}

int valid_enable(string usage)
{
         return usage == "force" || usage == "unarmed" || usage == "sword" ||
                usage == "dodge" || usage == "parry";
}

int double_attack() { return 1; }

int valid_learn(object me)
{
        int level;
        int i;

        if( query("gender", me) != "女性" )
                return notify_fail("你純陰之氣不足，難以領會高深的明玉功。\n");
                
        if( query("sex/times", me) )
                return notify_fail("修煉明玉功必須是處子之身。\n");

        if( query("int", me)<30 )
                return notify_fail("你覺得明玉功過于艱深，難以理解。\n");

        if( query("max_neili", me)<3500 )
            return notify_fail("你的內力修為太淺，無法運轉明玉功。\n");

        level = me->query_skill("mingyu-gong", 1);

        if ((int)me->query_skill("martial-cognize", 1) < 100)
                return notify_fail("你覺得明玉功過于深奧，以自己的武學修養"
                                   "全然無法明白。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的基本內功修為不足，難以運轉明玉功。\n");

        if (me->query_skill("force", 1) < level)
                return notify_fail("你對基本內功的理解還不夠，無法繼續領會更"
                                   "高深的明玉功。\n");

        if (me->query_skill("unarmed", 1) < level)
                return notify_fail("你對基本拳腳的理解還不夠，無法繼續領會更"
                                   "高深的明玉功。\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;

        if ((int)me->query_skill("mingyu-gong", 1) < 150
           || me->query_skill_mapped("parry") != "mingyu-gong"
           || me->query_skill_mapped("force") != "mingyu-gong"
           || me->query_skill_mapped("unarmed") != "mingyu-gong"
            || query("neili", me)<500
           || ! living(me))
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        ap = ob->query_skill("force") * 12 + ob->query_skill("count", 1) * 6;
        dp = me->query_skill("force") * 12;

        if (ap / 2 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "默念明玉功總訣，收斂"
                                            "內勁，承下$N" + HIR "這一招，$N" HIR
                                            "只覺猶如進入綿綿長河中，絲毫不起作用。\n"
                                            NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "一招擊中$n" HIR "上身"
                                            "，可卻猶如擊在棉花上一般，力道頓時"
                                            "消失得無影無蹤。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "但見$n" HIR "微微一笑，渾若無事"
                                            "的接下了$N" HIR "這一招，純陰之勁隨之而起，"
                                            "沒有受到半點傷害。\n" NOR]);
                        break;
                }
                return result;
        }
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int i;
        object weapon;

        lvl = me->query_skill("mingyu-gong", 1);
        weapon=query_temp("weapon", me);

        if( query_temp("mingyu_pfm/qiong", me )
              && query_temp("mingyu_pfm/qiong", me)>0
              && !query_temp("mingyu_pfm/qiong_hit_done", me )
             && living(victim)
             && !weapon)
        {
                addn("neili", -40, me);
                message_vision(HIY"\n$N前招將落，後招已至，前後兩招形如一式，此起彼伏，連綿不絕！\n"NOR,me);
                set_temp("mingyu_pfm/qiong_hit_done", 1, me);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),random(2));
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),random(2));
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),random(2));
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),random(2));
//                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2));
                delete_temp("mingyu_pfm/qiong_hit_done", me);
        }


        if (damage_bonus < 100
           || lvl < 150
            || query("neili", me)<300
           || me->query_skill_mapped("force") != "mingyu-gong"
           || me->query_skill_mapped("unarmed") != "mingyu-gong"
           || me->query_skill_prepared("unarmed") != "mingyu-gong")
                return 0;
        // if (damage_bonus / 2 > victim->query_con())
        if (damage_bonus > victim->query_con()/10)
        {
                addn("neili", -50, me);
                victim->receive_wound("qi", (damage_bonus - 80) / 2, me);
                return random(2) ? HIR "只見$N" HIR "明玉功內勁自體內迸發，一股柔勁隨招式"
                                   "而盪漾，摧毀了$n" HIR "的真元！\n" NOR:

                                   HIR "$N" HIR "明玉功的潛力發揮了出來，突然間$n"
                                   HIR "只感喉嚨一甜，噴出一口鮮血！\n" NOR;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("mingyu-gong", 1);
        if (lvl < 150) return 0;
        if (lvl < 200) return 70;
        if (lvl < 250) return 80;
        if (lvl < 300) return 90;
        if (lvl < 350) return 100;
        if (lvl < 400) return 110;
        return 120;
}

int practice_skill(object me)
{
        return notify_fail("明玉功只能用學(learn)的來增加熟練度。\n");
}

int difficult_level()
{
        return 1000;
}

string perform_action_file(string action)
{
        return __DIR__"mingyu-gong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"mingyu-gong/exert/" + action;
}

void skill_improved(object me)
{
        int lvl, layer;

        lvl = me->query_skill("mingyu-gong", 1);
        layer = lvl / 40;

        if ((lvl % 40) == 0 && layer > 9)
        {
                tell_object(me, HIY "你的明玉功又進了一層。\n" NOR);
        } else
        if ((lvl % 40) == 0)
        {
                tell_object(me, HIY "你煉成了第" + chinese_number(layer) +
                                "層的明玉功。\n" NOR);
        }

        if( lvl > 200 &&
            !query("can_perform/mingyu-gong/qiong", me) ) 
        {
                tell_object(me, HIC "你通曉了明玉功「" HIR "瓊樓玉宇" HIC "」的奧秘。\n" NOR);    
                set("can_perform/mingyu-gong/qiong", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
        }

        if( lvl > 300 &&
            !query("can_perform/mingyu-gong/gua", me) ) 
        {
                tell_object(me, HIC "你通曉了明玉功「" HIR "冰河倒掛" HIC "」的奧秘。\n" NOR);    
                set("can_perform/mingyu-gong/gua", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
        }

        if( lvl > 500 &&
            !query("can_perform/mingyu-gong/moqi", me) ) 
        {
                tell_object(me, HIC "你通曉了明玉功「" HIR "魔氣血殺" HIC "」的奧秘。\n" NOR);    
                set("can_perform/mingyu-gong/moqi", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000);  
        }
}
