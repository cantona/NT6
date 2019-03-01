#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void init()
{
        add_action("do_du", "yanjiu");
        add_action("do_du", "research");
}

void create()
{
        set_name(CYN "聖火令" NOR, ({ "shenghuo ling", "shenghuo", "ling" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "把");
                set("value", 10000);
                set("material", "steel");
                set("no_sell", "他奶奶的，這是什麼玩意？");
                set("long", CYN "這是一柄兩尺來長的黑牌，非金非鐵。質地堅硬無比，\n"
                                "似透明，令中隱隱似有火燄飛騰，實則是令質映光，顏\n"
                                "色變幻。令上刻得有不少波斯文字。 \n" NOR);
                set("wield_msg", CYN "$N“唰”的一聲，從腰間抽出一片黑黝的鐵牌握在手中。\n");
                set("unwield_msg", CYN "$N將聖火令插回腰間。\n" NOR);
        }
        init_sword(100);
        setup();
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int pxlevel; 

        if (!(arg=="shenghuo ling" || arg == "shenghuo" || arg == "ling" ))
        return 0;
        if (me->is_busy()) {
                write("你現在正忙著呢。\n");
                return 1;
        }
        if( me->is_fighting() ) {
                write("你無法在戰鬥中專心下來研讀新知！\n");
                return 1;
        }
        if (!id(arg)) { 
                write("你要讀什麼？\n");
                return 1;
        }
        if( !me->query_skill("literate", 1) ){
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }
        if( me->query_skill("sanscrit", 1) < 199){
                write("你的梵文水平太低，無法看懂聖火令裡所記載的內容。\n");
                return 1;
        }

        message("vision", me->name() + "正專心地研讀聖火令。\n", environment(me), me);

        if( query("jing", me)<80){
                write("你現在過于疲倦，無法專心下來研讀新知。\n");
                return 1;
        }
        if( query("qi", me)<80){
                write("你現在過于疲倦，無法專心下來研讀新知。\n");
                return 1;
        }
        pxlevel = me->query_skill("shenghuo-ling", 1);

        if( query("combat_exp", me)<100000){
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }
        if( query("combat_exp", me)<pxlevel*pxlevel/10*pxlevel){
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }
        if( me->query_skill("shenghuo-ling", 1) > 49){
                write("你研讀了一會兒，但是發現聖火令上所記載的對你而言都太淺了，沒有學到任何東西。\n");
                return 1;
        }
        me->receive_damage("qi", 50);
        me->receive_damage("jing", 50);
        me->improve_skill("shenghuo-ling", (int)me->query_skill("literate", 1)/5+1);
        write("你研讀聖火令，頗有心得。\n");
        return 1;
}
