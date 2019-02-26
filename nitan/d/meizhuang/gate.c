#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "梅莊大門");
        set("long", @LONG
走過一大片梅林，走上一條青石板大路，來到一座朱門白牆的大
莊院外，行到近處，見大門外寫着『梅莊』兩個大字，旁邊署着『虞
允文題』四字。那虞允文是南宋破金的大功臣，這幾個字儒雅之中透
着勃勃英氣。
LONG );
        set("outdoors", "meizhuang");
        set("exits", ([
                "south"    : __DIR__"xiaolu",
        ]));

        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_knock", "knock");
}

int do_knock(string arg)
{
        object room, me = this_player();

        if (query("exits/north"))
                return notify_fail("門已經是開着的，不用再費力去敲了！\n");

        if (arg == "4")
        {
                message_vision(HIC "$N" HIC "走上前去將門上銅環敲了四下。\n" NOR, me);
                set_temp("step", 1, me);
                return 1;
        }

        if (arg == "2")
        {
                message_vision(HIC "$N" HIC "走上前去將門上銅環敲了兩下。\n" NOR, me);
                if( query_temp("step", me) == 1 )
                        set_temp("step", 2, me);
                else
                        set_temp("step", 0, me);
                return 1;
        }

        if (arg == "5")
        {
                message_vision(HIC "$N" HIC "走上前去將門上銅環敲了五下。\n" NOR, me);
                if( query_temp("step", me) == 2 )
                        set_temp("step", 3, me);
                else
                        set_temp("step", 0, me);
                return 1;
        }

        if (arg == "3")
        {
                message_vision(HIC "$N" HIC "走上前去將門上銅環敲了三下。\n" NOR, me);
                if( query_temp("step", me) == 3 )
                {
                        set_temp("step", 0, me);
                        set("exits/north", __DIR__"tianjing");
                        message("vision", HIY "你靜靜的等候，過了半晌，大門終於緩緩"
                                          "的打開了。\n" NOR, this_object() );

                        if (! (room = find_object(__DIR__"tianjing")))
                                room = load_object(__DIR__"tianjing");

                        set("exits/south", __FILE__, room);
                        message("vision", HIY "梅莊大門上的銅環有節奏地響了"
                                "四聲，大門給打開了。\n" NOR, room );
                        remove_call_out("close_passage");
                        call_out("close_passage", 10);
                } else
                {
                        set_temp("step", 0, me);
                }
                return 1;
        }
        message_vision(HIC "$N" HIC "走上前去將門上銅環敲了幾下。\n" NOR, me);
        return 1;
}

void close_passage()
{
        object room;

        if (! query("exits/north"))
                return;

        message("vision", HIY "只聽“嘎嘎嘎”幾聲，梅莊內的護院將大門"
                "輕輕關上了。\n" NOR, this_object());

        if (room = find_object(__DIR__"tianjing"))
        {
                delete("exits/south", room);
                message("vision", "大門被護院輕輕關上了。\n", room );
        }
        delete("exits/north");
}
