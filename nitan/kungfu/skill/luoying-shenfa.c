// This program is a part of NT MudLIB
// luoying-shenfa 落英身法

#include <combat.h>
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$n將頭一低，雙臂內彎，手肘向前，似箭般向$N懷中撲去，正是一招“靈鰲步”，$N大驚之下，所發招數統統打在$n身後，盡數落空。\n",
        "dodge"  : 10,
        "skill_name" : "靈鰲步"
]),
([      "action" : "$n身形疾閃，使出一招“海燕騰空”，身體如同為海風所激，向後飄開一丈有餘，避過$N攻擊。\n",
        "dodge"  : 20,
        "skill_name" : "海燕騰空"
]),
([      "action" : "$n將身一縱，躍在半空，收腹含胸，一招“長空落雁”，在空中輕輕巧巧一個翻身，悄無聲息地落在$N身後。\n",
        "dodge"  : 30,
        "skill_name" : "長空落雁"
]),
([      "action" : "$n眼見敵招攻來，委實避無可避，忽然一招“巫峽雲斷”，凌空一個鐵板橋，全身自膝蓋以上，平平折斷，$N招數頓時失了準頭，全部打在空處。\n",
        "dodge"  : 40,
        "skill_name" : "巫峽雲斷"
]),
([      "action" : "$n身形閃動，使出一招“青鳥振翼”，雙臂展開，宛若翩翩起舞，姿態飄逸，閃過$N攻擊。\n",
        "dodge"  : 50,
        "skill_name" : "青鳥振翼"
]),
([      "action" : "$n身法一變，一式“湘靈空舞”，隨着$N攻勢，敵左則左，敵右則右，$N雖看似大佔上風，卻無一招能夠擊中。\n",
        "dodge"  : 60,
        "skill_name" : "湘靈空舞"
]),
([      "action" : "$n一聲清嘯，身形拔地而起，正是一招“鵬搏九霄”，在空中一連幾個轉折，扶搖直上，迅若鯤鵬，舉重若輕的閃過$N攻擊。\n",
        "dodge"  : 70,
        "skill_name" : "鵬搏九霄"
]),
([      "action" : "$n氣凝丹田，腳下疾踩後天八卦方位，一式“歸去來兮”，當真是望之在前，忽焉在後，$N手忙腳亂，連抵擋都有所不能，更別提還手反擊了。\n",
        "dodge"  : 80,
        "skill_name" : "歸去來兮"
])
});

mapping query_action(object me, object weapon)
{
        int zhaoshu, level;

        zhaoshu = sizeof(action);
        level   = (int) me->query_skill("luoying-shenfa");

        if (level < 60 )
                zhaoshu--;

        if (level < 50 )
                zhaoshu--;

        if (level < 40 )
                zhaoshu--;

        return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
        return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(string limb)
{
        return action[random(sizeof(action))]["action"];
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的氣血太差了，不能練落英身法。\n");
        me->receive_damage("qi", 30);
        return 1;
}

mixed valid_damage(object me, object victim, int damage, object weapon)
{
        mapping prepare,action;
        string msg,result,attack_skill;
        object w,w2;
        int ap, dp;
        w=query_temp("weapon", victim);
        w2=query_temp("weapon", me);

        if( !query_temp("wuzhuan", victim))return ;

        if( !living(victim) ) return;

        if( query("neili", victim)<300)return ;

        if( objectp(w2) )
                attack_skill=query("skill_type", w2);
        else {
                prepare = me->query_skill_prepare();
                if (!prepare) prepare = ([]);
                else if ( sizeof(prepare) == 0)        attack_skill = "unarmed";
                else if ( sizeof(prepare) == 1)        attack_skill = (keys(prepare))[0];
                else if ( sizeof(prepare) == 2)        attack_skill = (keys(prepare))[query_temp("action_flag",me)];
        }

        attack_skill = me->query_skill_mapped(attack_skill);

        ap=query("combat_exp", me)/1000;
        ap+=query("jiali", me)*2;

        dp=query("combat_exp", victim)/1000;
        dp += victim->query_skill("luoying-shenfa", 1);
        dp += victim->query_skill("tanzhi-shentong", 1);
        dp = (dp + random(dp*3/2)) / 2;

        action=query("actions", me);

        if( ap > dp ) return;

        if(victim->query_skill_mapped("parry") !="tanzhi-shentong") return;

        if((int)victim->query_skill("tanzhi-shentong", 1) < 120) return;

        if(victim->query_skill_prepared("finger") != "tanzhi-shentong") return;

        if( query_temp("wuzhuan_hit", victim)<0)return ;
        if(attack_skill=="tanzhi-shentong")
                result = HIG"$n伸指一彈，嗤的一聲輕響，一股細細的勁力激射出去，兩股「彈指神通」指力互擊，登時消弭於無形。\n" NOR;
        else if( objectp(w2) )
                result = HIG"$n伸指一彈，嗤的一聲輕響，一股細細的勁力激射出去，登時將$N的"+w2->name()+HIG"上所附內勁盡數抵銷，化解了這招"+to_chinese(attack_skill)+"。\n" NOR;
        else result = HIG"$n伸指一彈，嗤的一聲輕響，一股細細的勁力激射出去，這「彈指神通」與$N的「"+to_chinese(attack_skill)+"」鬥了個旗鼓相當，誰也沒能傷誰。\n" NOR;


        addn("neili", -(30+query("jiali", me)/2), victim);
        addn_temp("wuzhuan_hit", -1, victim);

        return ([ "msg" : result, "damage" : -damage ]);
}
