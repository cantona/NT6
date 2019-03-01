// Room: /t/wanjiegu/entrance.c

inherit ROOM;

void create()
{
        set("short", "大森林");
        set("long", @LONG
這裏是好大一座森林，黑壓壓的一片望不到邊。最特別是左首一
排並列着九株參天大松樹，每顆樹都高聳入雲。樹下草叢茂密，擋住
了去路。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 1 */
            "east" : __DIR__"shan_road4",
        ]));
        set("no_clean_up", 0);

        set("item_desc", ([ /* sizeof() == 2 */
            "草叢" : "一片茂密的草叢，你可以試着把它撥開(pushaside)。\n",
            "grass" : "一片茂密的草叢，你可以試着把它撥開(pushaside)。\n",
        ]));

        setup();
}

void init()
{
        add_action("do_push","pushaside");
}

int do_push(string arg)
{
        if( !arg ) return 0;
        if( arg != "草叢" && arg != "grass" ) return 0;
        if( arg == "草叢" || arg == "grass" ) {
            message_vision("$N撥開長草，樹上出現一洞。\n", this_player() );
            set("exits/enter", __DIR__"tree_hole");
            call_out("close_passage", 10);
            return 1;
        }
}

void close_passage()
{
        object room;

        if( !query("exits/enter") ) return;
        delete("exits/enter");
        message("vision","一陣風吹來，長草將樹洞蓋住了。\n", this_object() );
}
