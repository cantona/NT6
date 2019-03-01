#include <ansi.h>
inherit ROOM;

void create()
{
              set("short", "解劍巖");
        set("long", @LONG
這是武林中極負盛名的武當解劍巖，巖下解劍池水明澈照人。武
林人士經此都自覺解劍，以示對武當派的尊敬。千百年來，概無例外。
LONG );
              set("objects", ([
                   CLASS_D("wudang") + "/shan": 1,
              ]));
              set("outdoors", "wudang");
              set("exits", ([
                  "eastdown"  : __DIR__"slxl2",
                  "westup"    : __DIR__"slxl3",
              ]));
        set("coor/x", -350);
        set("coor/y", -180);
        set("coor/z", 10);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;

        me = this_player();
        if( (query_temp("weapon", me )
            || query_temp("secondary_weapon", me) )
           && dir == "westup"
           && objectp(present("zhang cuishan", environment(me))))
        {
            message_vision(CYN "\n張翠山喝道：各色人等，到解劍巖都需解劍，千百"
                               "年來概無例外！\n" NOR, me);
            return notify_fail(HIC "你懾于武當山規，不敢硬爭，只得退了一步。\n"
                               NOR);
        }
        return ::valid_leave(me, dir);
}