#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$n輕輕巧巧地往前一步，衣袂飄忽，一式"HIW"「輕雲蔽月」"NOR"身影恍惚如浮雲，\n$N只覺眼花繚亂。\n",
        "$n袍袖輕拂，拔地而起，在空中轉了一圈，一式"HIW"「流風迴雪」"NOR"有如漫天\n瓊花飛舞，$N目眩神迷，辨不清方向。\n",
        "$n抬手掩面，嫣然一笑，左一步，右二步，斜刺裏又三步，一式"MAG"「羅襪生塵」"NOR"\n輕捷婀娜，只見地上纖塵紛揚，$N呆立半晌，渾忘了如何出招。\n",
        "$n待$N攻近面門，突然身形後仰，後退幾步，一式"MAG"「輕裾曳霧」"NOR"施施然\n躲過了$N這一招。\n",
        "$n一式"HIM"「驚鴻回眸」"NOR"，一個側身飄然掠起，轉眼已在$N身後。\n",
        "$n舒展身體，抖擻精神，一式"HIY"「游龍翩飛」"NOR"迅捷如電，側身讓過了$N這招。\n",
        "$n回眸粲然，一式"HIG"「清流弄履」"NOR"有如流水濺濕文履，剎那間滑出丈餘許，\n$N這一招撲了個空。\n",
        "$n泰然自若，左足上挑，右足力蹬，一式"HIG"「神渚濯足」"NOR"縱躍於幾丈開外。\n",
        "$n氣定神閒，籠袖不動，足下卻是風生水起，一式"HIB"「屏翳收風」"NOR"飄然避過\n$N這招。\n",
        "$n身形將傾未傾，若往若還，一式"HIC"「川后靜波」"NOR"如微風輕掠水面，倏忽已\n不見人影。\n",
});

int valid_enable(string usage)
{
        return usage == "dodge";
}

int valid_learn(object me)
{
        int lvl;

        lvl = me->query_skill("lingbo-weibu", 1);
        if (lvl > 300) lvl = 300;

       if( query("dex", me)<21 )
                return notify_fail("你先天身法太差，無法學習凌波微步。\n");

        if( query("max_neili", me)<3000+lvl*20 )
                return notify_fail("你試着走了兩步，頓覺胸"
                                   "口煩惡之極，看來是內力不濟。\n");
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("lingbo-weibu", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) * 3/5 +
             me->query_skill("lingbo-weibu", 1);

        if( query_temp("immortal", me) )
        {
                me->stop_busy(); 
                me->clear_weak(); 
        }

        if( ap/3+random(ap)<dp || query_temp("immortal", me) )
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIW "$n" HIW "身子輕輕晃動，$N" HIW
                                            "眼前頓時出現了無數個$n" HIW "的幻影，令$N"
                                            HIW "完全無法辨出虛實。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" HIW "往旁邊歪歪斜斜的邁出一步，卻恰"
                                            "好令$N" HIW "的攻擊失之毫釐。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "這一招來的好快，然後$n"
                                            HIW "一閃，似乎不費半點力氣，卻將$N"
                                            HIW "這一招剛好避開。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" HIW "輕輕一躍，已不見了蹤影，$N"
                                            HIW "心中大駭，卻又見$n" HIW "擦肩奔過，"
                                            "當真令人思索菲儀。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "只見$n" HIY "微微一笑，身子輕輕晃動，"
                                 "頓時出現了無數個$n" HIY "的幻影，可是$N"
                                 HIY "精通易理，將其中虛實辨得清清楚楚。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "往旁邊歪歪斜斜的邁出一步，然而$N"
                                 HIY "錯步跟隨，方位毫釐不差。\n" NOR;
                        break;
                case 2:
                        result = HIY "$n" HIY "一閃，似乎不費半點力氣，卻將$N"
                                 HIY "這一招剛好避開，可是$N"
                                 HIY "招中有招，進攻卻是不止。\n" NOR;
                        break;
                default:
                        result = HIY "但見$n" HIY "輕輕一躍，已不見了蹤影，$N"
                                 HIY "不假思索，反身出招，更是巧妙無方。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("lingbo-weibu", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 80;
        if (lvl < 250) return 100;
        if (lvl < 300) return 120;
        if (lvl < 350) return 140;
        return 150;
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太差了，難以練習凌波微步。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠了，無法練習凌波微步。\n");

        me->receive_damage("qi", 65);
        addn("neili", -65, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lingbo-weibu/" + action;
}
void skill_improved(object me)
{
        if( me->query_skill("lingboweibu",1) == 80 && !query("lbwb", me )
        &&  me->query_skill("literate", 1) > 80)
        {
                tell_object(me, HIY "$N一步步走下來，只覺的心情舒暢，不知不覺內力有所積累。\n" NOR);
                addn("max_neili", random(30)+20, me);
                addn("lbwb", 1, me);
        }
        if( me->query_skill("lingboweibu",1) == 120 && query("lbwb", me) == 1
        &&  me->query_skill("literate", 1) > 100)
        {
                tell_object(me, HIM "$N六十四卦走完，剛好繞了一個大圈，回到原地，精神大振。\n" NOR);
                addn("max_neili", random(30)+20, me);
                addn("lbwb", 1, me);
        }
        if( me->query_skill("lingboweibu",1) == 160 && query("lbwb", me) == 2
        &&  me->query_skill("literate", 1) > 120)
        {
                tell_object(me, CYN "$N越走越快，內息隨着步法不住運轉，隱隱然自己的內力已經有了提高！\n" NOR);
                addn("max_neili", random(30)+20, me);
                addn("lbwb", 1, me);
        }
        if( me->query_skill("lingboweibu",1) == 200 && query("lbwb", me) == 3
        &&  me->query_skill("literate", 1) > 140)
        {
                message_vision(RED "$N步法嫻熟，隨意踏出，腳步成圓，只感神清氣爽，全身精力瀰漫！\n" NOR, me);
                addn("max_neili", random(30)+20, me);
                addn("lbwb", 1, me);
        }
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) {
        if (me->query_family() =="xiaoyao")        return 1.5;
        return 1.0;
}

int help(object me)
{
        write(HIC"\n凌波微步："NOR"\n");
        write(@HELP

    洛神賦：“凌波微步，羅襪生塵……轉盼流精，光潤玉顏。含
辭未吐，氣若幽蘭。華容婀娜，令我忘餐。［禾農］纖得衷，修短
合度，肩若削成，腰如紅素，延頸秀項，皓質呈露，芳澤無加，鉛
華弗御。雲髻峨峨，修眉連娟。丹脣外朗，皓齒內鮮。明眸善睞，
輔薜承權。環姿豔逸，儀靜體閒。柔情綽態，媚於語言……皎若太
陽升朝霞，灼若芙蓉出綠波”。
    凌波微步原載於北冥神功帛卷卷末，按伏羲六十四卦而排，內
勁行遍一週天，腳步亦踏遍六十四卦一週天。步法輕靈迅捷，有如
凌波而行，羅襪生塵，巧妙已極。
    凌波微步乃逃命之妙法，非害人之本領也，練之有百利而無一
害。

        學習要求：
          北冥神功10級
HELP
        );
        return 1;
}
