//mudong.c
// This is a room made by Wsl.
inherit ROOM;
int do_use(string arg);
void create()
{
        set("short", "墓穴");
        set("long", @LONG
你隱約看到四周的牆上插着六柄火把。
LONG );
        setup();
}
void init()
{
        add_action("do_use", "use");
}
int do_use(string arg)
{
        object me,ob;
        me = this_player();
        if( !arg || arg=="" ) return 0;
        if (!present("fire",me)) return 0;
        if( arg=="fire" ) {
        remove_call_out("close");
        call_out("close", 5, this_object());
             write(
"你取出火折一晃，湊上前去點燃了其中的一隻火把，也不知是什麼機關，
其它的五隻火把一一燃了起來。\n");
        set("long", @LONG
洞內一片凌亂，各種盔甲兵刃散落在地上，洞壁上刻了各種各樣
的圖案，出口四通八達，也不知暗藏了什麼機關暗器。
LONG
        );
        set("exits", ([
                "north" : __DIR__"mudong"+random(11),
                "south" : __DIR__"mudong"+random(11),
                "east" : __DIR__"mudong"+random(11),
                "west" : __DIR__"mudong"+random(11),
        ]));
           if ( objectp(ob=present("fire", this_player())) )     {
            destruct(ob);
        return 1;
       }
        return notify_fail("你想點燃什麼？\n");
        }
}

void close(object room)
{
        message("vision","不一會兒，牆上的火把就熄滅了。\n", room);
        set("long", @LONG
你隱約看到四周的牆上插着六柄火把。
LONG
);
        delete("exits", room);
}
