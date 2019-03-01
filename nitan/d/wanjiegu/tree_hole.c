// Room: /t/wanjiegu/tree_hole.c

inherit ROOM;

void create()
{
        set("short", "樹洞");
        set("long", @LONG
樹洞內非常狹窄，光線黑暗，地上鋪滿是枯草。洞的牆上有一隻
大蜘蛛正在編織一個蜘蛛網。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "out" : __DIR__"entrance",
        ]));
        set("no_clean_up", 0);
        set("item_desc", ([ /* sizeof() == 2 */
            "枯草":"一堆枯草，裏面有一個大鐵環(ring)。\n",
            "grass":"一堆枯草，裏面有一個大鐵環(ring)。\n",
        ]));

        setup();
}

void init()
{
        add_action("do_pull","pull");
}

int do_pull(string arg)
{
        if( !arg ) return 0;
        if( arg != "大鐵環" && arg != "ring" ) return 0;
        if( arg == "大鐵環" || arg == "ring" ) {
        message_vision("$N用勁拉起大鐵環，拎起一塊木板，下面露出一洞。\n", this_player() );
        set("exits/enter", __DIR__"tunnel1");
        call_out("close_passage", 10);
        return 1;
        }
}

void close_passage()
{
        object room;

        if( !query("exits/enter") ) return;
        delete("exits/enter");
        message("vision","木板晃了晃，將下面的洞口蓋住了。\n", this_object() );
}
