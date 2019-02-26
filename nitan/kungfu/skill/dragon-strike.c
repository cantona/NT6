// dragon-strike.c 降龍十八掌

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string main_skill() { return "yinyang-shiertian"; }

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});
mapping *action = ({
([        "action" : "$N雙掌平平提到胸前，神色沉重的緩緩施出"+(order[random(13)])+"「亢龍有悔」"NOR"推向$n的$l",
          "lvl"        : 10,
          "skill_name" : "亢龍有悔",
]),
([        "action" : "$N突然身形飛起，雙掌居高臨下一招"+(order[random(13)])+"「飛龍在天」"NOR"拍向$n的$l",
          "lvl"        : 20,
          "skill_name" : "飛龍在天",
]),
([        "action" : "$N右掌一招"+(order[random(13)])+"「見龍在田」"NOR"，迅捷無比地劈向$n的$l",
          "lvl"        : 30,
          "skill_name" : "見龍在田",
]),
([        "action" : "$N雙掌施出一招"+(order[random(13)])+"「鴻漸於陸」"NOR"，隱隱帶着風聲拍向$n的$l",
          "lvl"        : 40,
          "skill_name" : "鴻漸於陸",
]),
([        "action" : "$N左掌聚成拳狀，右掌一招"+(order[random(13)])+"「潛龍勿用」"NOR"緩緩推向$n的$l",
          "lvl"        : 50,
          "skill_name" : "潛龍勿用",
]),
([        "action" : "$N施出一招"+(order[random(13)])+"「利涉大川」"NOR"，右掌插腰，左掌劈向$n的$l",
          "lvl"        : 60,
          "skill_name" : "利涉大川",
]),
([        "action" : "$N使出"+(order[random(13)])+"「突如其來」"NOR"，右掌從不可能的角度向$n的$l推出",
          "lvl"        : 70,
          "skill_name" : "突如其來",
]),
([        "action" : "$N大吼一聲，雙掌使出"+(order[random(13)])+"「震驚百里」"NOR"，不顧一切般擊向$n",
          "lvl"        : 80,
          "skill_name" : "震驚百里",
]),
([        "action" : "$N使出"+(order[random(13)])+"「或躍在淵」"NOR"，向$n的$l連拍數掌",
          "lvl"        : 90,
          "skill_name" : "或躍在淵",
]),
([        "action" : "$N身形滑動，雙掌使一招"+(order[random(13)])+"「雙龍取水」"NOR"一前一後按向$n的$l",
          "lvl"        : 100,
          "skill_name" : "雙龍取水",
]),
([        "action" : "$N使出"+(order[random(13)])+"「魚躍於淵」"NOR"，身形飛起，雙掌並在一起向$n的$l劈下",
          "lvl"        : 110,
          "skill_name" : "魚躍於淵",
]),
([        "action" : "$N雙掌立起，使出"+(order[random(13)])+"「時乘六龍」"NOR"向$n連砍六下",
          "lvl"        : 120,
          "skill_name" : "時乘六龍",
]),
([        "action" : "$N使出"+(order[random(13)])+"「密雲不雨」"NOR"，左掌封住$n的退路，右掌斜斜地劈向$l",
          "lvl"        : 130,
          "skill_name" : "密雲不雨",
]),
([        "action" : "$N使出"+(order[random(13)])+"「損則有孚」"NOR"，雙掌軟綿綿地拍向$n的$l",
          "lvl"        : 140,
          "skill_name" : "損則有孚",
]),
([        "action" : "$N腳下一轉，突然欺到$n身前，一招"+(order[random(13)])+"「龍戰於野」"NOR"拍向$n的$l",
          "lvl"        : 150,
          "skill_name" : "龍戰於野",
]),
([        "action" : "$N門户大開，一招"+(order[random(13)])+"「履霜冰至」"NOR"向$n的$l劈去",
          "lvl"        : 160,
          "skill_name" : "履霜冰至",
]),
([        "action" : "$N使出"+(order[random(13)])+"「羝羊觸蕃」"NOR"，雙掌由下往上擊向$n的$l",
          "lvl"        : 170,
          "skill_name" : "羝羊觸蕃",
]),
([        "action" : "$N左掌護胸，右掌使一招"+(order[random(13)])+"「神龍擺尾」"NOR"上下晃動着擊向$n的$l",
          "lvl"        : 180,
          "skill_name" : "神龍擺尾",
]),
});

// string main_skill() { return "dragon-strike"; }

mapping sub_skills = ([
       "kanglong-youhui"  : 80,        // 1
       "feilong-zaitian"  : 80,        // 2
       "jianlong-zaitian" : 80,        // 3
       "hongjian-yulu"    : 80,        // 4
       "qianlong-wuyong"  : 80,        // 5
       "lishe-dachuan"    : 80,        // 6
       "turu-qilai"       : 80,        // 7
       "zhenjing-baili"   : 80,        // 8
       "huoyue-zaiyuan"   : 80,        // 9
       "shuanglong-qushui": 80,        // 10
       "yuyue-yuyuan"     : 80,        // 11
       "shicheng-liulong" : 80,        // 12
       "miyun-buyu"       : 80,        // 13
       "sunze-youfu"      : 80,        // 14
       "longzhan-yuye"    : 80,        // 15
       "lvshuang-bingzhi" : 80,        // 16
       "diyang-chufan"    : 80,        // 17
       "shenlong-baiwei"  : 80,        // 18
]);

int get_ready(object me)
{
       return 1;
}

int get_finish(object me)
{
       if( query("str", me)<31 || me->query_str()<45 )
       {
               tell_object(me, "你演練完畢，手臂又酸又軟，幾乎抬不起來。\n");
               return 0;
       }

       if( query("con", me)<24 || me->query_con()<37 )
       {
               tell_object(me, "你演練完畢，就覺得眼前金星亂冒，太陽穴突突的跳。\n");
               return 0;
       }

       if ((int)me->query_skill("force") < 150)
       {
               tell_object(me, "你演練完畢，幾乎虛脱，自己的內功水平看來還有待提高。\n");
               return 0;
       }

       if( query("max_neili", me)<1500 )
       {
               tell_object(me, "你演練完畢，丹田提不起半點力來，看來應該繼續鍛鍊內力。\n");
               return 0;
       }

       if (random(10) < 5)
       {
               tell_object(me, "你對十八掌的奧妙頗有領悟，或許再演練一次就能夠融會貫通。\n");
               return 0;
       }

       tell_object(me, HIY "你一氣呵成，將十八掌從頭到尾演練了一變，心中頓悟，通\n"
                           "曉了降龍十八掌的奧妙精髓，融會貫通了掌法的精微之處，\n"
                           "再也非拆開使用那麼那麼簡單。\n" NOR);
       return 1;
}

mapping query_sub_skills()
{
       return sub_skills;
}

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
       if( query("str", me)<31 )
               return notify_fail("就你這身子骨還練降龍十八掌？小心弄折了胳膊。\n");

       if( query("con", me)<24 )
               return notify_fail("算了吧，你先天根骨不好，彆強學了。\n");

       if ((int)me->query_skill("force") < 150)
               return notify_fail("你的內功火候不夠，無法學習降龍十八掌。\n");

       if( query("max_neili", me)<1500 )
               return notify_fail("你的內力這麼差，怎能融會貫通降龍十八掌？\n");

       if ((int)me->query_skill("strike", 1) < 30)
               return notify_fail("你的基本掌法火候不夠，無法學習降龍十八掌。\n");

       if ((int)me->query_skill("strike", 1) < (int)me->query_skill("dragon-strike", 1))
               return notify_fail("你的基本掌法水平有限，無法領會更高深的降龍十八掌。\n");

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
        mapping a_action;
        int level, tmp;
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -60;
        int d_e2 = -40;
        int p_e1 = -20;
        int p_e2 = 10;
        int f_e1 = 520;
        int f_e2 = 640;
        int i, seq, ttl = sizeof(action);

        level = (int)me->query_skill("dragon-strike", 1);
        if( query_temp("xlz/hanglong", me) )
        {
                tmp = 4 + random(15);
                delete_temp("xlz/hanglong", me);
                return ([
                        "action": HIY "\n$N叫道：「看招！」左腿微屈，右掌劃了個圓圈，平推出去，正是降龍十八掌中的「亢龍有悔」。\n" +
                                  "初推出去看似輕描淡寫，但一遇阻力，剎時之間連加" + chinese_number(tmp) + "道後勁，一道強似一道，\n" +
                                  "重重疊疊，直至無堅不摧，無強不破！" NOR,
                        "dodge" : -140,
                        "parry" : -140,
                        "attack": 200,
                        "force" : 500 + 40 * tmp,
                        "damage": 100 + 20 * tmp,
                        "damage_type": random(2)?"內傷":"瘀傷"
                ]);
        }

        seq = random(ttl);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}

// int double_attack() { return 1; }

int practice_skill(object me)
{
        int cost;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練降龍十八掌必須空手。\n");

        if( query("qi", me)<110 )
                return notify_fail("你的體力太低了。\n");

        // cost = me->query_skill("dragon-strike", 1) / 5 + 90;
        if( query("neili", me)<110 )
                return notify_fail("你的內力不夠練降龍十八掌。\n");

        me->receive_damage("qi", 100);
        addn("neili", -100, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        string msg;
        int lvl;

        lvl = me->query_skill("dragon-strike", 1);

        if (damage < 50 || lvl < 150) return;

        if (random(10) < 2)
        {
                result = ([ "damage" : damage ]);
                result += ([ "msg" : HIY "$N" HIY "一掌既出，身子搶前，又是一招「亢龍有悔」，"
                                     "後掌推前掌，雙掌力道並在一起，排山倒海的壓將過來。\n"
                                     HIR "$n" HIR "那曾見過這樣霸道的掌力，頓時身受重創，哇的一聲，吐出一口鮮血！\n"
                                     NOR ]);
        }
        else
        {
                victim->receive_wound("qi", damage, me);
                msg = random(2) ? HIR "$n" HIR "一聲慘叫，胸前「咔嚓咔嚓」幾聲脆"
                                  "響，口中鮮血狂噴。\n" NOR :
                                  HIR "只聽$n" HIR "前胸「咔嚓」一聲脆響，竟像是"
                                  "肋骨斷折的聲音。\n" NOR;
                result = ([ "msg" : msg ]);
        }

        return result;
}

string perform_action_file(string action)
{
/*
        object me = this_player();

        if( me->query_family() != "丐幫" && query("reborn/family_name", me) != "丐幫" )
                return 0;
*/

        return __DIR__"dragon-strike/" + action;
}

void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);
        for (i = 0; i < sizeof(sub_skillnames); i++)
               me->delete_skill(sub_skillnames);
}

/*
// Let parry skill take its special effort.
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("dragon-strike", 1)) < 100 ||
            !living(query_temp("weapon", me) || objectp(me)) )
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) * 2 / 3 +
             me->query_skill("dragon-strike", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "不待回身，一招「神龍擺尾」，反手還劈一掌。\n"
                                    "$N" HIC "見這招來勢兇狠，不敢硬接，縱身避開。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIC "只見$n" HIC "左掌圓勁，右掌直勢，使招「見龍在田」，擋在身前。\n"
                                    "這一招純是防禦，卻是在雙方之間布了一道堅壁。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "當下不敢怠慢，雙掌飛舞，將自己全身籠罩在掌力之下。\n"
                                    "這一守當真是穩若淵停嶽峙，直無半點破綻。\n" NOR]);
                        break;
                }
                return result;
        }
}
*/

int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("dragon-strike", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        if (me->query_skill("huntian-qigong",1) >= 10)        return 0.8;
        else return 1.0;
}

// 技能典故介紹
string query_description()
{
        return
        "降龍十八掌勇往直前，它的威力甚至超過了六脈神劍，當然"
        "綜合起來與六脈神劍相差還頗有距離。關於降龍十八掌的"
        "定位問題頗有爭議，這裏是依據蕭峯手下的功夫定位的。"
        "當然學習還是要找洪七公，降龍十八掌乃是丐幫專用武功，"
        "其它門派的人物不可學習，丐幫學習的條件是你的妻子或"
        "女友能夠拿得出像樣的叫化雞給洪七公吃，如何作菜這就靠自"
        "己摸索了。有幾處地方可以學習廚藝。不過如果你沒有 31"
        " 點的先天膂力和 24 點的先天根骨，就省省，可不必摸索了。"
        "降龍十八掌要先將十八掌學齊到 80 級，然後通過演練合"
        "成降龍十八掌。";
}

int help(object me)
{
        write(HIC"\n降龍十八掌："NOR"\n");
        write(@HELP

    降龍十八掌是丐幫鎮幫之寶，是天下最剛猛的武功。

        學習要求：
                自行演練，將十八路掌法合而為一
                內力3000
                先天臂力25
                先天根骨20
                基本掌法180
                基本掌法不低於降龍掌
HELP
        );
        return 1;
}
