// Room: /t/wanjiegu/grassland.c

inherit ROOM;

void create()
{
        set("short", "草地");
        set("long", @LONG
這是一大片草地，前面一排松樹擋住了去路。只見一株大鬆上削
下了丈許長、尺許寬的一片，漆着白漆，寫着九個大字，『姓段者入
此谷殺無赦』。樹上掛着一個鐵錘。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 1 */
            "enter" : __DIR__"tunnel2",
        ]));
        set("no_clean_up", 0);

        set("item_desc", ([ /* sizeof() == 2 */
            "鐵錘" : "一個鐵錘，可以用來敲(knock)東西。\n",
            "hammer" : "一個鐵錘，可以用來敲(knock)東西。\n",
        ]));

        setup();
}

void init()
{
        add_action("do_knock","knock");
}

int do_knock(string arg)
{
        if( !arg ) return 0;
        if( arg != "段" && arg != "duan" ) return 0;
        if( arg == "段" || arg == "duan" ) {
        message_vision("$N拿起鐵錘在第二個字“段”上敲了一下。\n", this_player());
        message_vision("只聽裏面有人應了一聲，“來了！”\n", this_player() );
        message_vision("有人從裏面將門打開了。\n", this_player() );
        set("exits/north", __DIR__"xiaoting");
        call_out("close_passage", 10);
        return 1;
        }
}

void close_passage()
{
        object room;

        if( !query("exits/north") ) return;
        delete("exits/north");
        message("vision","門被人關上了。\n", this_object() );
}