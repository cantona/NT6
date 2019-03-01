// yinyang-shiertian.c 陰陽十二重天
// 三十歲之前通曉九陽神功、九陰神功、北冥神功、凌波微步、乾
// 坤大挪移、降龍十八掌和六脈神劍，合其為一創出，S+++級武學。
// 陰陽十二重天可以激發為天下所有的武功。

#include <ansi.h>

inherit FORCE;

string *xue_name = ({ 
"勞宮穴", "膻中穴", "曲池穴", "關元穴", "曲骨穴", "中極穴", "承漿穴", "天突穴", "百會穴",
"幽門穴", "章門穴", "大橫穴", "紫宮穴", "冷淵穴", "天井穴", "極泉穴", "清靈穴", "至陽穴", });

string *attack_name = ({
"九陽六脈劍氣", "九陰六脈劍氣", "九陽無極勁", "九陰無極勁", "九陰太玄勁","九陽太玄勁" });

string *dodge_msg = ({
        HIW "$n" HIW "手足忽的一晃，$N" HIW "竟然無法進擊，只能自保。\n" NOR,
        HIW "只見$n" HIW "身子輕輕晃動，$N" HIW "眼前頓時出現了無數個$n" HIW
        "的幻影，令$N" HIW "完全無法辨出虛實。\n" NOR,
        HIW "$n" HIW "往旁邊歪歪斜斜的邁出一步，卻恰好令$N" HIW "的攻擊失之"
        "毫厘。\n" NOR,
        HIW "$N" HIW "這一招來的好快，然後$n" HIW "一閃，似乎不費半點力氣，"
        "卻將$N" HIW "這一招剛好避開。\n" NOR,
        HIW "但見$n" HIW "輕輕一躍，已不見了蹤影，$N" HIW "心中大駭，卻又見"
        "$n" HIW "擦肩奔過，步法之奇巧，當真令人思索菲儀。\n" NOR,
});

string *parry_msg = ({
        HIW "$N" HIW "一招擊在$n" HIW "身上，卻被$n" HIW "暗運乾坤大挪移內勁"
        "，將內力盡數移入地下。\n" NOR,
        HIW "$n輕輕一帶，$N" HIW "發現自己招數回擊過來，嚇得往後倒退幾步。\n" NOR,
        HIW "$n手臂回轉，在$N" HIW "手肘下輕輕一推，$N" HIW "招數落空。\n" NOR,
        HIW "$n右手伸出，在$N" HIW "手腕上輕輕一拉，$N" HIW "收勢不住，直往前撲去。\n" NOR,
        HIW "$n身形不動，$N" HIW "一招擊下，有如石沉大海，不覺呆住了。\n" NOR,
        HIW "$n左牽右引，$N" HIW "如身處漩流，連續轉了好幾個圈。\n" NOR,
        HIW "$n雙手回圈，$N" HIW "只覺得前面好象有一堵牆，再也攻不進去。\n" NOR,
        HIW "$n輕輕一轉，$N" HIW "一招擊在地上，只打得塵土飛揚。\n" NOR,
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yinyang-shiertian", 1);
        return lvl /10 * lvl /10 * 15 * 40 / 10 / 20;
}

int query_jingli_improve(object me)
{
        int lvl;
        
        lvl = (int)me->query_skill("yinyang-shiertian", 1);
        
        if (me->query_skill_mapped("force") == "yinyang-shiertian")
                return lvl * 14 / 7;

        return 0;
}

mapping *actionf = ({
([      "action": HIW "$N" HIW "右手中指一豎，「六脈神劍」向前刺出。真氣鼓盪，嗤"
                  "然聲響，無形劍氣直指$n" HIW,
        "force" : 700,
        "attack": 300,
        "dodge" : 450,
        "parry" : 450,
        "damage": 550,
        "weapon": HIW "破體無形劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "action": HIR "$N" HIR "身體一側，一掌凌空劈出，一股熾熱無比的氣流頓時澎"
                  "湃湧至$n" HIR "全身各處",
        "force" : 800,
        "attack": 400,
        "dodge" : 350,
        "parry" : 350,
        "damage": 250,
        "weapon": HIR "九陽無極勁" NOR,
        "damage_type":  "割傷"
]),
([      "action": HIY "$N" HIY "身形一轉，拳頭攜著疾速旋轉的氣流揮出，疾如閃電，"
                  "勢如雷霆，擊向$n" HIY,
        "force" : 800,
        "attack": 400,
        "dodge" : 350,
        "parry" : 350,
        "damage": 250,
        "weapon": HIY "九陰無極勁" NOR,
        "damage_type":  "刺傷"
]),
([      "action": WHT "$N" WHT "雙掌平平提到胸前，神色沉重的緩緩施出「降龍十八掌"
                  "」推向$n" WHT "全身各處",
        "force" : 1000,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": WHT "降龍無極勁" NOR,
        "damage_type": "刺傷"
]),
([      "action": HIW "$N" HIW "雙手十指齊伸，數十條氣流從少沖穴中激射而出，「六"
                  "脈神劍」出手如風，指向$n" HIW,
        "force" : 700,
        "attack": 300,
        "dodge" : 450,
        "parry" : 450,
        "damage": 550,
        "weapon": HIW "破體無形劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "action": WHT "$N" WHT "突然身形飛起，雙掌居高臨下一招「降龍十八掌」在呼"
                  "嘯聲中迅捷無比地劈向$n" WHT "全身各處",
        "force" : 1000,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": WHT "降龍無極勁" NOR,
        "damage_type": "刺傷"
]),
});

mapping *actionw = ({
([      "action": HIY "$N" HIY "攻勢忽緩而不疏，$w" HIY "變化無常，捉摸不定向$n"
                  HIY "慢慢卷去",
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "內傷"
]),
([      "action": HIY "$N" HIY "手中的$w" HIY "突煥氣象森嚴，便似千軍萬馬奔馳而"
                  "來，如同棍棒一般橫掃$n" HIY,
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "內傷"
]),
([      "action": HIY "$N" HIY "卷起手中的$w" HIY "，就如鐵錘一般對著$n" HIY "亂"
                  "砍亂砸，沒有半點章法",
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "內傷"
]),
([      "action": HIY "$N" HIY "運用$w" HIY "幻化做一個一個圓圈，似乎要將$n" HIY
                  "團團包圍",
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "內傷"
]),
([      "action": HIY "$N" HIY "含笑回轉$w" HIY "，伸手一指，頗得拈花指之意，點"
                  "向$n" HIY "全身",
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "內傷"
]),
});

string main_skill()
{
        return "yinyang-shiertian";
}

mapping sub_skills = ([
        "moon-blade"  : 350,
        "jiuyang-shengong" : 350,
        "taixuan-gong"     : 350,
        "six-finger"       : 350,
        "dragon-strike"    : 350,
        "qiankun-danuoyi"  : 350,
        "wuming-jianfa"    : 350,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        if( query("int", me)<39 )
        {
                tell_object(me, "你演練完畢，只感思緒紊亂，看來依你的悟性，無"
                                "法將其合一。\n");
                return 0;
        }
        if( query("con", me)<39 )
        {
                tell_object(me, "你演練完畢，只覺全身真氣亂竄，眼冒金星，兩耳轟鳴，好"
                                "不容易才控制下來。\n");
                return 0;
        }
        if( query("str", me)<39 )
        {
                tell_object(me, "你演練完畢，只覺雙臂酸疼，全身發軟。\n");
                return 0;
        }
        if( query("dex", me)<39 )
        {
                tell_object(me, "你演練完畢，發現依你的身法暫時還無法將其融會貫通。\n");
                return 0;
        }

        if( query("age", me) >= 18 )
        {
                                tell_object(me, "你已錯過演練的最佳時刻，今生將于此高深武學無緣。\n");
                return 0;
        }

        if (random(100) != 1 && ! wizardp(me))
        {
                tell_object(me, "你覺得有所感悟，或許再演練一次就能融會貫通，練成陰陽九轉十二重天。\n");
                return 0;
        }

        tell_object(me, HIW "一陣凡塵往事湧上心頭，你幾欲放聲長嘆。霎那間，你放眼回首，竟有一股莫名\n"
                        "的悲哀。宗師泰鬥那種高出不勝寒、登泰山而小天下之感猶然而生，你只覺得以\n往的"
                        "武學現在看來是多麼的渺小可笑。\n" NOR);

        CHANNEL_D->do_channel(this_object(), "rumor", "聽說" + me->name() + "演練出"HIY"陰陽九轉十二重天"HIM"。\n");
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

string *usage_skills = ({ "unarmed", "strike", "claw", "hand", "cuff", "finger",
                          "sword", "blade", "hammer", "throwing", "club", "whip",
                          "staff", "dodge", "dagger", "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force)
{
        return 1;
}

int double_attack()
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        level = me->query_skill("yinyang-shiertian", 1);
        for (i = 0; i < sizeof(usage_skills); i++)
                if (me->query_skill(usage_skills[i], 1) < level)
                        return notify_fail("你對" + to_chinese(usage_skills[i]) + "的理解還"
                                           "不夠，無法繼續領會更高深的陰陽十二重天。\n");

        if (me->query_skill("martial-cognize", 1) < level)
                                return notify_fail("你武學修養不夠，無法繼續修煉。\n");
        
        if( level>380 && query("yinyang-shiertian/yinyang", me) )
                                return notify_fail("你陰陽九轉十二重天已達到新的層次，須修煉出陰陽境界方能再次提升。\n");
        
        if( level>480 && query("yinyang-shiertian/qiankun", me) )
                                return notify_fail("你陰陽九轉十二重天已達到新的層次，須修煉出乾坤境界方能再次提升。\n");

        if( level>600 && query("yinyang-shiertian/shier", me) )
                                return notify_fail("你陰陽九轉十二重天已達到新的層次，須修煉出十二重天境界方能再次提升。\n");      

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("陰陽十二重天博大精深，無法簡單的通過練習進步。\n");
}

int difficult_level()
{
        return 3000;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name1, name2, weapon;
        name1 = xue_name[random(sizeof(xue_name))];
        name2 = attack_name[random(sizeof(attack_name))];

        victim->receive_wound("qi", damage_bonus * 3, me);
        addn("neili",query("jiali",  me)/3, me);

        if( query("neili", victim)<500 )
                set("neili", 0, victim);
        else
                addn("neili", -300, victim);

        return NOR + HIR "$n" HIR "接下$N" HIR "一招，" + name2 + "頓時破體而"
               "入，全身真氣由" + name1 + "狂瀉而出。\n" NOR;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;

        ap = ob->query_skill("parry");
        dp = me->query_skill("yinyang-shiertian", 1);

        if (random(ap * 2 / 3) < dp * 3 / 2)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIW "$n" HIW "面含微笑，輕輕一格，已將天"
                                            "下所有進攻招數全部封死。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" HIW "眉頭微微一皺，動也不動，將"
                                            "$N" HIW "震到一邊。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$n" HIW "身形微微一抖，已將$N" HIW 
                                            "迫退至丈許開外。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" HIW "一聲輕哼，身形微微一動，已"
                                            "飄然遠去，使$N" HIW "的進攻全無用處。\n" NOR]);
                        break;
                }
                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("yinyang-shiertian", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("yinyang-shiertian", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

string perform_action_file(string action)
{
        return __DIR__"yinyang-shiertian/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"yinyang-shiertian/exert/" + action;
}

void skill_improved(object me) 
{ 
        int i; 
        string *sub_skillnames; 

        sub_skillnames = keys(sub_skills); 
        for (i = 0; i < sizeof(sub_skillnames); i++) 
                me->delete_skill(sub_skillnames); 
} 
