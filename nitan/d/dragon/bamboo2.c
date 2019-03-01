// room: well.c
// Jay 4/8/96

#include <ansi.h>
inherit ROOM;

int do_use(string arg);
int do_tui(string arg);

void create()
{
        set("short", "竹徑");
        set("long",
"這裡竹子很茂密，光線極暗。空氣中有淡淡的竹子的清香。在這樣的\n"
"地方，會隱藏著什麼嗎？\n"
);
        set("exits", ([
                "east" : __DIR__"bamboo",
        ]));
        set("no_clean_up", 0);
        set("no_magic", 1);
        setup();
}

void init()
{
        add_action("do_use", "use");
        add_action("do_tui", "tui");
}

int do_use(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("moonsoul", me))  return 0;
        if( arg=="moonsoul" ) {
             write(
             "你掏出懷中的"+HIC"月魄"NOR+"，"+HIC"月魄"NOR+"發出幽藍的光芒。巖壁上似乎有道暗門，也許可以試著推(tui)一下。\n"
             );
             set_temp("marks/鑽1", 1, this_player());
             return 1;
       }
}

int do_tui(string arg)
{
        object me;
        me = this_player();

        if( query_temp("marks/鑽1", me)){
            message("vision", me->name() + "一下子就不見了。\n",
                    environment(me), ({me}) );
            me->move(__DIR__"moonroom");
            message("vision", me->name() + "從巖縫暗門裡跌了出來。\n",
                    environment(me), ({me}) );
            delete_temp("marks/鑽1", this_player());

            return 1;
        }
        else {
            write("亂推有什麼用?!\n");
            return 1;
        }
}
