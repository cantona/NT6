#include <room.h>

inherit ROOM;

void create()
{
              set("short", "北間操練房");
        set("long", @LONG
這裡擺滿了大刀長劍、沙袋綁腿等，是武當弟子日常練功的地方。
LONG );

              set("exits", ([
                    "south"   : __DIR__"caolianfang",
              ]));
              set("for_family", "武當派");
        set("coor/x", -390);
        set("coor/y", -290);
        set("coor/z", 100);
        setup();
              replace_program(ROOM);
}