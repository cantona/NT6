// Room: /d/gaochang/mishi2.c
// Last Modified by Winder on Jul. 15 2000

#include <ansi.h>;
inherit ROOM;
int do_study(string arg);

void create()
{
        set("short", "地下室");
        set("long", @LONG
這裡是宮殿底下的地下密室。密室雖小，卻也是五臟俱全，石桌石
椅，石幾石床，連室內放的幾件器皿，也都是石制的。看來似乎很久以
前有人在這裡住過。正中的石桌(table) 上平放著一塊薄薄的石板，上
面好象刻著些什麼。
LONG
        );
        set("had_sword", 1);
        set("exits", ([
                "south" : __DIR__"mishi",
        ]) );
        set("item_desc", ([
                "table" : "這是一整塊巨石雕成的石桌，上面刻了些奇怪的圖形。
桌上放著一口黑黝黝毫不起眼的重劍(zhongjian)。\n",
                "zhongjian": "這是一口玄鐵□制的玄鐵寶劍，正連鞘隔在石桌上。\n",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -36510);
        set("coor/y", 10110);
        set("coor/z", 30);
        setup();
}

void init()
{
        add_action("do_study", "study");
        add_action("do_take", "take");
        add_action("do_take", "qu");
        add_action("do_take", "jian");
        add_action("do_take", "pick");
        add_action("do_zuan","zuan");
        add_action("do_zuan","enter");
}

int do_study(string arg)
{
        object me = this_player();

        if ( !arg || ( arg != "table" ) )
                return notify_fail("什麼？\n");

        if ( (int)me->query_skill("literate", 1) < 1)
                return notify_fail("你是個文盲，先學點文化(literate)吧。\n");

        if( query("jing", me)<30 )
                return notify_fail("你現在精神無法集中！\n");

        me->receive_damage("jing", 10);

        message_vision("$N正專心研讀石桌上的古怪圖形。\n", me);
        if ( (int)me->query_skill("literate", 1) < 150)
        {
                me->improve_skill("literate",(query("int", me)/3));
                write("你對著石桌琢磨了一回兒，似乎對讀書識字有點心得。\n");
                set_temp("stone_learned", 1, me);
        }
        if( !query_temp("stone_learned", me) )
        {
                write("你對著石桌琢磨了一回兒，發現上面所說的太過淺顯，對你來說已毫無意義了。\n");
        }
        return 1;
}

int do_take(string arg)
{
        object sword, me=this_player();

        if( !arg || arg=="" ) return 0;
        if( arg=="zhongjian" )
        {
                if (!query("had_sword") || uptime() < 300)
                        message_vision("$N伸手去取劍，才發現只剩劍鞘了，玄鐵劍早就被別人取走了...。\n", me);
                else
                {
                        if (me->query_str() < 30)
                                return notify_fail("那玩意兒太重，你費了半天勁還是拿不起來。\n");
                        set("had_sword", 0);
                        message_vision("$N輕輕的從石桌上撿起一口劍來。\n", me);
                        sword = new(WEAPON_DIR"treasure/xuantie-sword");
                        if (sword->violate_unique())
                        {
                                destruct( sword );
                                return notify_fail("你伸手去取劍，才發現只剩劍鞘了，玄鐵劍早就被別人取走了...。\n");
                        } 
                        sword->move(me);
message("channel:rumor",MAG"【謠言】某人："+query("name", me)+"得了一口玄鐵劍啦。\n"NOR,users());
                        return 1;
                }
                return 1;
        }
        return 0;
}
int do_zuan(string arg)
{
        object me=this_player();
        
        if (!arg || arg!="table")
                return notify_fail("你要鑽到那裡去?\n");
        if (me->query_str()>30)
                return notify_fail("你的身形太大，鑽不到桌子底下。\n");
        message_vision("$N哧溜一下鑽到了桌子下面去。\n",me);
        me->move("d/gaochang/mishi3");
        message("vision",query("name", me)+"從外面鑽了進來。\n",environment(me),({me}));
        return 1;
}