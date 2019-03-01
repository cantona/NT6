// hamagong.c 蛤蟆功

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force) { return 1; } 

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("hamagong", 1);
        return lvl * lvl * 15 * 22 / 100 / 200;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

/*
mapping *action = ({
([      "action" : "$N忽而倒豎，一手撐地，身子橫挺，只以一掌向$n的$l拍出",
        "lvl" : 0,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "$N雙手在地上一撐，身子忽地拔起，一躍三尺，落在$n的面前，單掌向$p直劈而下",
        "lvl" : 10,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "$N突然伸手在自己臉上猛抓一把，又反足在自己腎上狠踢一腳，一掌擊出，中途方向必變，實不知將打何處",
        "lvl" : 20,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "突然之間，$N俯身疾攻，上盤全然不守，微微側頭，一口唾沫往$n$l吐去",
        "lvl" : 30,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "$N絲毫不動聲色，雙腿微曲，右掌平伸，左掌緩緩運起蛤蟆功的勁力，呼的一聲推向$n",
        "lvl" : 80,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "$N默念口訣運氣經脈，只覺癒轉癒是順遂，當下一個翻身躍起，咕的一聲叫喊，雙掌對著$n拍出",
        "lvl" : 110,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "但見$N雙腿微曲，雙掌會收，然後向$n一上一下，一放一收，鬥然擊出",
        "lvl" : 140,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "$N閉眼逼住呼吸，過了片刻，猛躍而起，眼睛也不及睜開，雙掌便向$n的方向推了出去",
        "lvl" : 170,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "$N腳步搖搖幌幌的看上去馬上就會跌倒，忽然雙腿一彎、一登，口中閣的一聲叫喝，手掌向$n猛然推出",
        "lvl" : 199,
        "skill_name" : "蛤蟆功"
]),
});
*/
mapping *action = ({
([      "action": "$N輕身一躍，使出一招" + HIY"「沙漠孤舟」"NOR + "，左掌橫，右掌帶，將$n逼開。",
        "force" : 200,
        "lvl"   : 0,
        "dodge" : -20,
        "damage": 240,
        "skill_name": "沙漠孤舟",
        "damage_type": "瘀傷"
]),
([      "action":"只見$N倏地向前跨出一步，一招" + WHT"「萬裡獨歸」"NOR + "，雙掌一錯，順勢攻向$n",
        "force" : 220,
        "lvl"   : 20,
        "dodge" : -20,
        "damage": 250,
        "skill_name": "萬裡獨歸",
        "damage_type": "瘀傷"
]),
([      "action":"$N一招" + HIW"「鳴沙寒煙」"NOR + "，來勢曼妙無方，掌力微吐，罩向$n周身。",
        "force" : 400,
        "lvl"   : 40,
        "dodge" : -30,
        "damage": 250,
        "skill_name": "鳴沙寒煙",
        "damage_type": "瘀傷"
]),
([      "action":"$N低眉曲身，掌勢若有若無，恰恰將$n來招一一封住，並暗含反擊之意，正是一招" + HIR"「霓裳弄雪」"NOR + "。",
        "force" : 225,
        "dodge" : -30,
        "lvl"   : 70,
        "damage": 270,
        "skill_name": "霓裳弄雪",
        "damage_type": "瘀傷"
]),
([      "action":"$N一招" + HIB"「秋恨客途」"NOR + "，抽身提步，不退反進，雙掌平推，來如電閃，徑直拍向$n。",
        "force" : 530,
        "dodge" :-20,
        "lvl"   : 100,
        "damage": 300,
        "skill_name": "秋恨客途",
        "damage_type": "瘀傷"
]),
});

mapping *reverse_action = ({
([      "action": "忽聽$N大叫三聲，三個筋鬥翻將出來，大吼一聲，惡狠狠的朝$n撲將上來",
        "dodge": -15,
        "parry": -20,
        "force": 300,
        "damage": 60,
        "damage_type": "跌傷"
]),
([      "action":"但見$N瘋勢更加厲害，口吐白沫，舉頭朝$n猛撞",
        "parry": -15,
        "force": 360,
        "damage": 70,
        "damage_type": "瘀傷"
]),
([      "action":"$N驀地張口，白牙一閃，已向$n$l咬落，又快又準",
        "dodge": -5,
        "force": 420,
        "damage": 80,
        "weapon": "牙齒",
        "damage_type": "咬傷"
]),
([      "action":"$N一口唾沫急吐，勢挾勁風，竟將痰涎唾沫也當作了攻敵利器",
        "dodge": -45,
        "force": 480,
        "damage": 90,
        "weapon":"唾沫",
        "damage_type": "刺傷"
]),
([      "action":"$N忽然張嘴，一口唾沫往$n臉上吐去，發掌擊向$n趨避的方位，同時又是一口濃痰吐將過來",
        "dodge": -30,
        "force": 540,
        "damage": 100,
        "weapon" : "濃痰",
        "damage_type": "刺傷"
]),
([      "action":"此時$N所使的招數更是希奇古怪，詭異絕倫，身子時而倒豎，時而直立，忽然一手撐地，身子橫挺，一手出掌打向$n$l",
        "dodge": -10,
        "force": 600,
        "damage": 110,
        "damage_type": "瘀傷"
]),
});

int valid_combine(string combo) { return combo=="shexing-diaoshou"; }

int valid_enable(string usage)
{
        if (usage == "force" || usage == "parry" ) return 1;
        if (usage == "strike") {
                if (this_player()->query_skill("hamagong",1) < 200) {
                        /*
                        message_vision("$N蹲下身來，口中咕咕咕的叫了幾聲，要將蛤蟆功口訣用在拳腳之上，但無論如何使用不上。\n", this_player() );
                        write("你的蛤蟆功火候不足，無法運用它到掌法中。\n");
                        */
                        return 0;
                }
                return 1;
        }
        return 0;
}
int valid_learn(object me)
{
        mapping skl;
        string *sname;
        int v, i, k=0;

        if( query("character", me) == "光明磊落"
            || query("character", me) == "狡黠多變" )
                return notify_fail("你心中暗道：這蛤蟆功陰毒異常，估計會傷及自"
                                   "身，還是別練為妙。\n");

        /*
        if( query("con", me)<32 )
                return notify_fail("你先天根骨孱弱，無法修煉蛤蟆功。\n");

        if( query("dex", me)<32 )
                return notify_fail("你先天身法太差，無法修煉蛤蟆功。\n");
        */

        if( query("gender", me) == "無性" && query("hamagong", me)>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的蛤蟆功。\n");

        /*
        if ((int)me->query_skill("poison", 1) < 50)
                return notify_fail("你的基本毒技火候不足，難以領會蛤蟆功。\n");
        */

        i = (int)me->query_skill("hamagong", 1);

        if ((int)me->query_skill("force", 1) < 30
         || (int)me->query_skill("force", 1)/2 < i/3 )
                return notify_fail("你的基本內功火候不足，不能學蛤蟆功。\n");

        if( query("tianmo_jieti/times", this_player()) )
                return ::valid_learn(me);

        skl=this_player()->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );

        if(me->query_skill("hamagong", 1) > 99){

                for(v=0; v<sizeof(skl); v++) {
                        if (SKILL_D(sname[v])->check() == "force")
                        k++;
                }
                if ( k >=3 )
                return notify_fail("你體內不同內力互相沖撞，難以領會更高深的內功。\n");
        }

        if( query("class", me) == "bonze" && !query("reborn/times", me))
        {
                if( query("gender", me) == "女性" )
                        return notify_fail("小尼姑練蛤蟆功，不怕別人叫你禿頭蛤蟆嗎？\n");
                if( query("gender", me) == "男性" )
                        return notify_fail("大師傅練蛤蟆功，不怕別人叫你禿頭蛤蟆嗎？\n");
        }

        if( query("family/family_name", me) == "丐幫" && !query("reborn/times", me) )
                return notify_fail("老叫化的徒弟學不了蛤蟆功。\n");

        if( query("family/family_name", me) == "武當派"  && !query("reborn/times", me))
                return notify_fail("老道練蛤蟆功，不怕別人叫你牛鼻子蛤蟆嗎？\n");

        return ::valid_learn(me);
}
int practice_skill(object me)
{
        if( query("family/master_id", me) != "ouyang feng"
         && me->query_skill("hamagong", 1) > 200)
                return notify_fail("蛤蟆功需高人指點才能繼續提高。\n");

        if( query_temp("weapon", me) )
                 return notify_fail("蛤蟆從不手持兵刃，所以練蛤蟆功也必須空手。\n");

        if( query("jing", me)<50 )
                return notify_fail("你的精氣不夠練蛤蟆功。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練蛤蟆功。\n");
        addn("neili", -30, me);
        me->receive_damage("jing", 10);
        if (me->query_skill("hamagong", 1) > 100){
                addn("neili", -40, me);
                me->receive_damage("jing", 20);
        }
        if (me->query_skill("hamagong", 1) > 150){
                addn("neili", -20, me);
                me->receive_damage("jing", 10);
        }
        if (me->query_skill("hamagong", 1) > 200){
                addn("neili", -10, me);
                me->receive_damage("jing", 10);
        }
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
        int d_e1 = -40;
        int d_e2 = -20;
        int p_e1 = 0;
        int p_e2 = 30;
        int f_e1 = 190;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        string *power_msg =
        ({
                HIR"$N蹲下身來，運起蛤蟆功，雙手平推，吐氣揚眉，閣閣閣三聲叫喊。這三推之力帶有風疾雷迅的猛勁，實是非同小可"NOR,
                WHT"$N閣閣兩聲怒吼，蹲下身來，呼的雙掌齊出，掌力未到，掌風已將地下塵土激起，一股勁風直撲$n面門，勢道雄強無比"NOR,
                HIR"$N臉色陰沉，臉頰上兩塊肌肉微微牽動，兩臂彎曲，閣的一聲大叫，雙手挺出，一股巨力橫沖直撞的朝$n推將過來"NOR,
                WHT"$N蹲低身子，口中咕咕咕的叫了三聲，雙手推出，以蛤蟆功向$n猛攻。$n身周在$P掌力籠罩之下，只激得灰泥彌漫，塵土飛揚"NOR,
        });
        string *reverse_msg =
        ({
                HIM"但見$N招術奇特，怪異無倫，忽爾伸手在自己臉上猛抓一把，忽爾反足在自己臀上狠踢一腳，每一掌打將出來，中途方向必變，實不知打將何處"NOR,
                HIM"$N忽然反手拍拍拍連打自己三個耳光，大喊一聲，雙手據地，爬向$n，忽地翻身一滾，驟然間飛身躍起，雙足向$n連環猛踢"NOR,
                HIM"突然之間，$N俯身疾攻，上盤全然不守，出招怪異無比，將蛤蟆功逆轉運用，上者下之，左者右之，招數難以捉摸"NOR,
                HIM"$N全身經脈忽順忽逆，手上招數雖然走了錯道，但是錯有錯著，出手怪誕，竟教$n差愕難解"NOR,
        });

        lvl = (int) me->query_skill("hamagong", 1);
        if (me->query_skill_mapped("force") == "hamagong" ) {
                if( !query_temp("hmg_dzjm", me) && query_temp("powerup", me) && random(me->query_skill("force",1))>250 && query("neili", me)>1000 && query("jiali", me)>100 )
                        return ([
                        "action": power_msg[random(sizeof(power_msg))],
                        "dodge": -120,
                        "parry": -120,
                        "force": 650+random(100),
                        "damage": 120,
                        "damage_type": random(2)?"內傷":"瘀傷"
                        ]);
                else if( query_temp("reverse", me) && random(me->query_skill("force",1))>400 && random(me->query_skill("strike",1))>300 && query("neili", me)>1000 )
                        return ([
                        "action": reverse_msg[random(sizeof(reverse_msg))],
                        "dodge": -200,
                        "parry": -200,
                        "force": 630+random(100),
                        "damage": 300+random(20),
                        "damage_type": "瘀傷",
                        ]);
        }

        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        if( query_temp("hmg_dzjm", me) )
                return ([
                        "action"      : reverse_action[random(6)]["action"],
                        "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                        "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                        "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                        "damage_type" : random(2) ? "內傷" : "瘀傷",
                ]);
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("hamagong", 1);

        if (damage_bonus < 150
           || lvl < 180
           || query("neili", me)<300
        // || query_temp("weapon", me )
           || me->query_skill_mapped("force") != "hamagong"
           || me->query_skill_mapped("strike") != "hamagong"
           || me->query_skill_prepared("strike") != "hamagong")
                return 0;

        if (damage_bonus / 2 > victim->query_con() / 10)
        {
                addn("neili", -30, me);
                victim->receive_wound("qi", damage_bonus/2, me);
                return WHT "$n" WHT "硬承下$N" WHT "一掌，霎時全"
                       "身一顫，經脈受震，噴出一口鮮血！\n" NOR;
        }
}

string exert_function_file(string func)
{
        return __DIR__"hamagong/exert/" + func;
}

string perform_action_file(string action)
{
        return __DIR__"hamagong/perform/" + action;
}

int help(object me)
{
        write(HIC"\n蛤蟆功："NOR"\n");
        write(@HELP

    歐陽鋒創立此功，為白駝山派本門內功。此功也可作為掌法使
用，並能與蛇形刁手互備。
    這蛤蟆功純系以靜制動，他全身涵勁蓄勢，蘊力不吐，只要敵
人一施攻擊，立時便有猛烈無比的勁道反擊出來，剛猛無匹。

        學習要求：
                基本內功10級
                太監無法領悟50級以上的蛤蟆功
                相應的戾氣
HELP
        );
        return 1;
}
