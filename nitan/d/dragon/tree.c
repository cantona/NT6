#include <room.h>
inherit ROOM;

void create()
{
      set("short","樹上");
      set("long",
"這是人蔘果樹上。枝葉遮天蔽日，一點一點的金光在樹葉間閃爍。仔\n"
"細看看，原來是象一個個小孩子的果子，天地的至寶——人蔘果！\n"
);
      set("exits",([ /* sizeof() == 1 */
          "down"  : __DIR__"ground",
      ]));
      set("objects", ([
//           "/d/wudang/obj/renshenguo"   : 2,
      ]));
      set("no_magic", 1);
        setup();
}
