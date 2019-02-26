#include <ansi.h>
inherit ROOM;
void create()
{
  set("short","石室");
  set("long",
"石室形作八角，共有八門，陣陣陰風吹來，你不由的打了一個寒戰。\n"
"往裏走上幾步看到門口一灘血跡，牆壁上也斑斑點點散滿了血水。好像這\n"
"裏剛剛經過一場激烈的搏殺。\n"
);
        set("no_magic", "1");
    set("exits", ([
            "1" : __DIR__"stone1",
            "2" : __DIR__"stone2",
            "3" : __DIR__"stone3",
            "4" : __DIR__"stone4",
            "5" : __DIR__"stone5",
            "6" : __DIR__"stone6",
            "7" : __DIR__"stone7",
 //21              "west" : __DIR__"chukou",
            "8" : __DIR__"stone8",
         "out" :"/d/city/guangchang",
            "east": __DIR__"lou0",
   ]));
    setup();
}
