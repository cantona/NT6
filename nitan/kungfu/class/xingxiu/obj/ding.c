// ding.c 神木王鼎

inherit ITEM;
#include <ansi.h>;
void create()
{
        set_name(YEL"神木王鼎"NOR, ({ "shenmu wangding", "ding" }));
        set_weight(500);
        set("count", 200);
        set_max_encumbrance(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "座");
                set("long", 
YEL"這是一座色作深黃的小小木鼎。木鼎雕琢甚是精細，木質堅潤似
似玉，木理之中隱隱約約的泛出"RED"紅絲"YEL"。鼎側有五個銅錢大的圓孔，
木鼎齊頸處有一道細縫，似乎分為兩截。\n    看來是練功用的(use)。\n"NOR);
                set("value", 2000);
        }
}

int is_container() { return 1; }

void init()
{
        add_action("do_use","use");
}

int do_use(string arg)
{
        object env, target, ob = this_object(), me = this_player();
        string targetname, bugname, bugunit;
        mapping fam;
        int hgdf_sk, poison_sk, skpoint;
        
        if (!present(ob,me)) return 0;

        if( !arg || sscanf(arg, "%s with %s", arg, targetname)!=2 )
                return notify_fail("用法是 use ding with 幫你練功的人\n");

        if ( !id(arg) )
                return notify_fail("你要用什麼？");

//        if( query("count") < 1)
//                return notify_fail("這個木鼎看來破爛不堪，恐怕不能用了。\n");

        env = environment(me);
        hgdf_sk = me->query_skill("huagong-dafa", 1);
        poison_sk = me->query_skill("poison", 1);

        if( query("no_fight", env) )
                return notify_fail("這裡不適合你用神木王鼎練功。\n");

        if( !objectp(target = present(targetname, env)) )
                return notify_fail("你附近沒有這個人。\n");

        if( target == me)
                return notify_fail("自己給自己做藥罐？太不值了吧。\n");

        if( query("race", target) != "人類" )
                return notify_fail("幫你練功的必須是人。\n");

        if( living(target) && !query_temp("noliving", target) )
                return notify_fail("你只能找個不省人事的人做你的練功藥罐。\n");

        if( !(fam=query("family", me)) || fam["family_name"] != "星宿派" )
                return notify_fail("你試圖想看看這木鼎有啥用，可是看不懂！\n");

        if( hgdf_sk < 20)
                return notify_fail("你化功大法火候不夠，不能使用神木王鼎！\n");

        if( poison_sk < 20)
                return notify_fail("你的基本毒技太低，沒法抵擋木鼎的毒力！\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用神木王鼎！\n");

        if( me->is_fighting() )
                return notify_fail("戰鬥中無法才能使用神木王鼎！\n");

        if( me->is_busy() )
                return notify_fail("你正忙著呢！哪有空做這水磨功夫？\n");

//        add("count", -1);
        skpoint = poison_sk + random(hgdf_sk);

        switch( random(5))
        {
                case 0:
                        bugunit = HIR"一條紅艷艷的";
                        bugname = HIR"大蜈蚣"HIG;
                        break;
                case 1:
                        bugunit = HIC"一只青灰色的";
                        bugname = HIC"大蜘蛛"HIG;
                        break;
                case 2:
                        bugunit = BLK"一只花斑黑格";
                        bugname = BLK"大蠍子"HIG;
                        break;
                default:
                        bugunit = HIW"一條白身黑章";
                        bugname = HIW"大蟒蛇"HIG;
        }

        message_vision(HIG"
$N取了一只深黃色的小木鼎出來，放在地下，又從鼎底取出一個小小
布包，打了開來，裡面是幾塊黃色、黑色、紫色的香料。$N從每一塊
香上捏了少許，放入鼎中，用火刀、火石打著了火，燒了起來，然後合
上鼎蓋。

過了一陣，忽聽得草叢中瑟瑟聲響，綠草中"+bugunit+bugname+"徑直爬
向木鼎，從鼎下的孔中鑽了進去，便不再出來。

$N把$n的手伸進木鼎，"+bugname+"一伸嘴，就一口咬住了$n的中指。
過了好一會，但見$n的中指上隱隱罩上了一層深紫之色。紫色由淺而
深，慢慢轉成深黑，再過一會，黑色自指而掌，更自掌沿手臂上升。

過得片刻，木鼎的孔中有一滴滴黑血滴了下來。$N臉現喜色，忙伸掌
將血液接住，盤膝運功，將血液都吸入掌內。過了好一會，木鼎再無黑
色滴下，$N雙掌一搓，瞧自己手掌時，但見兩只手掌如白玉無瑕，更
無半點血污。\n"NOR, me, target);

        target->receive_wound("qi", 40); 
        if (hgdf_sk > 20 && hgdf_sk < 150)
        {
                if( SKILL_D("huagong-dafa")->valid_learn(me) )
                {
                        me->improve_skill("huagong-dafa", random(skpoint));
                        tell_object(me, HIC"你的「化功大法」進步了。\n"NOR);
                }
        }
        if (poison_sk > 20 && poison_sk < 100)
        {
                if( SKILL_D("poison")->valid_learn(me) )
                {
                        me->improve_skill("poison", random(skpoint));
                        tell_object(me, HIC"你的「基本毒技」進步了。\n"NOR);
                }
        }
        me->start_busy(3);
        return 1;
}
