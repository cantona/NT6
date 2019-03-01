#include <room.h>
inherit TRANS_ROOM; 

void create()
{
        set("short", "唐門驛站");
        set("long",
"這是一間用木板從大木棚隔出的一間小房，裝飾的還算不錯，一個笑\n"
"嘻嘻的伙計站在那裡，見你進來連忙上來招呼，櫃台側面有一個大門，門\n"
"虛掩著，裡面傳來馬的嘶鳴聲，如果你想坐車，就看看(paizi)吧。\n"
);

        set("valid_startroom", 1);

        set("exits", ([
                 "east" : __DIR__"bdajie1",
        ]));
        set("objects", ([
                "/d/tangmen/npc/tmxer" : 1,
        ]));

        set("area", "唐門");
        set("che_id", "tmmache");

        setup();
}
