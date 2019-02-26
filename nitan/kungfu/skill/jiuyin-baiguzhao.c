//jiuyin-baiguzhao.c 九陰白骨爪

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action": "$N左爪虛晃，右爪蓄力，一招「勾魂奪魄」直插向$n的$l",
        "force" : 250,
        "attack": 45,
        "dodge" : 10,
        "parry" : 18,
        "damage": 30,
        "lvl"   : 0,
        "skill_name" : "勾魂奪魄" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N雙手連環成爪，爪爪鈎向$n，「九子連環」已向$n的$l抓出",
        "force" : 270,
        "attack": 50,
        "dodge" : 20,
        "parry" : 26,
        "damage": 45,
        "lvl"   : 40,
        "skill_name" : "九子連環" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N雙手使出「十指穿心」，招招不離$n的$l",
        "force" : 300,
        "attack": 60,
        "dodge" : 20,
        "parry" : 32,
        "damage": 45,
        "lvl"   : 70,
        "skill_name"  : "九子連環" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N身形圍$n一轉，使出「天羅地網」，$n的$l已完全籠罩在爪影下",
        "force" : 340,
        "attack": 85,
        "dodge" : 30,
        "parry" : 55,
        "damage": 55,
        "lvl"   : 100,
        "skill_name" : "天羅地網" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N使一招「風捲殘雲」，雙爪幻出滿天爪影抓向$n全身",
        "force" : 370,
        "attack": 110,
        "dodge" : 40,
        "parry" : 68,
        "damage": 70,
        "lvl"   : 130,
        "skill_name" : "風捲殘雲" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N吐氣揚聲，一招「唯我獨尊」雙爪奮力向$n天靈戳下",
        "force" : 420,
        "attack": 140,
        "dodge" : 50,
        "parry" : 85,
        "damage": 90,
        "lvl"   : 160,
        "skill_name" : "唯我獨尊" ,
        "damage_type" : "抓傷"
]),
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }
int valid_combine(string combo) { return combo=="cuixin-zhang"; }
int valid_learn(object me)
{
        if( query("character", me) != "心狠手辣" && query("character", me) != "國士無雙" )
                return notify_fail("你天性不符，受其拘束，無法領會九陰白骨爪的妙旨。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練九陰白骨爪必須空手。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法練九陰白骨爪。\n");

        if ((int)me->query_str() < 30)
                return notify_fail("你現在膂力孱弱，還無法練九陰白骨爪。\n");

        if ((int)me->query_skill("force") < 90)
                return notify_fail("你的內功太差，無法練九陰白骨爪。\n");

        if ((int)me->query_skill("claw", 1) < 60)
                return notify_fail("你的基本爪法太差，無法領會九陰白骨爪。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("jiuyin-baiguzhao", 1))
                return notify_fail("你的基本爪法火候不夠，無法領會更高深的九陰白骨爪。\n");

        return 1;
}
int practice_skill(object me)
{
        object obj;
        object *obs;
        int i, skill, damage;

        skill = me->query_skill("jiuyin-baiguzhao", 1);
        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠練九陰白骨爪。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不能練功。\n");

        if( query("sleep_room", environment(me)) )
                return notify_fail("這裏練功會打擾別人休息。\n");

        if (skill < 200)
        {
                obs = filter_array(all_inventory(environment(me)),
                                   (: (base_name($1) == CORPSE_OB &&
                                       !query("been_cut/head", $1) ||
                                       base_name($1) == "/clone/misc/head") &&
                                       query_temp("clawed_by_jiuyin", $1)<10:));
                if (sizeof(obs) < 1)
                        return notify_fail("練九陰白骨抓需有屍體或是完好的頭蓋骨。\n");

                addn("neili", -450, me);
        }

        me->receive_damage("qi", 80);
        addn("neili", -40, me);
        if (skill < 200)
        {
                message_vision(HIB "只見$N" HIB "左手上圈下鈎、左旋右轉，連變了"
                               "七八般花樣，驀地裏右手一伸，噗的一響，五根手指直"
                               "插入\n頭骨的腦門。隨後五根手指" HIR "血淋淋"
                               HIB "的提將起來。\n" NOR, me);

                if (base_name(obs[0]) == "/clone/misc/head")
                        obs[0]->set("long",query("long", obs[0])+
                                    "上面赫然有五個小洞，伸手一探，剛好可以插入。\n");

                addn_temp("clawed_by_jiuyin", 1, obs[0]);
                me->improve_skill("jiuyin-baiguzhao", 100 + skill * 5 + random(500));
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
        int d_e1 = 20;
        int d_e2 = 5;
        int p_e1 = -20;
        int p_e2 = -60;
        int f_e1 = 300;
        int f_e2 = 600;
        int i, lvl, seq, ttl = sizeof(action);

        seq = random(ttl);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "抓傷" : "內傷",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        if( query("shen", me) <= -100000)return 1;
        else if( query("shen", me)<0)return 0.8;
        else return 0.6;
}

void skill_improved(object me)
{
        tell_object(me, HIR"你忽然從心底生出一股惡念：殺、殺、殺！我要殺絕天下人！\n" NOR );
        addn("shen", -200, me);
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;
        mixed result;

        lvl  = me->query_skill("jiuyin-baiguzhao", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (damage_bonus / 2 > victim->query_str())
        {
            victim->affect_by("jy_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ]));
                result = ([ "damage" : damage_bonus ]);
                result += ([ "msg" : HIR "你聽到「喀啦」一聲輕響，竟似是骨碎的聲音！\n" NOR ]);

                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("jiuyin-baiguzhao", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
string perform_action_file(string action)
{
        return __DIR__"jiuyin-baiguzhao/" + action;
}

int help(object me)
{
        write(HIC"\n九陰白骨爪："NOR"\n");
        write(@HELP

    徽宗皇帝於政和年間，遍搜普天下道家之書，雕版印行，一共
有五千四百八十一卷，稱為‘萬壽道藏’。皇帝委派刻書之人，叫
做黃裳。他生怕這部大道藏刻錯了字，皇帝發覺之後不免要殺他的
頭，因此上一卷一卷的細心校讀。他居然便因此精通道學，更因此
而悟得了武功中的高深道理。他無師自通，修習內功外功，竟成為
一位武功大高手。他因此涉及江湖仇殺，退隱山林。不知不覺竟已
過了四十多年，終於對每一個敵人所使過的招數，他都想通了破解
的法子對付。於是出得山來，去報仇雪恨。不料那些敵人全都已不
在人世了。黃裳心想：‘原來我也老了，可也沒幾年好活啦。’他
花了這幾十年心血，想出了包含普天下各家各派功夫的武學，過得
幾年，這番心血豈不是就此湮沒？於是他將所想到的法門寫成了上
下兩卷書，那就是《九陰真經》。九陰白骨爪就是依此書練成的霸
道功夫。

        學習要求：
                內力200
HELP
        );
        return 1;
}
