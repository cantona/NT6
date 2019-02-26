#include <room.h>
inherit ROOM;

void create()
{
              set("short", "南間操練房");
        set("long", @LONG
這裏擺滿了大刀長劍、沙袋綁腿等，是武當弟子日常練功的地方。
LONG );

              set("exits", ([
                    "north"   : __DIR__"caolianfang",
              ]));
              set("for_family", "武當派");
        set("coor/x", -390);
        set("coor/y", -310);
        set("coor/z", 100);
        setup();
              replace_program(ROOM);
}