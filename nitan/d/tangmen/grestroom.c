//brestroom.c  by winder

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "女弟子休息室");
        set("long",
"這是一個昏暗的房間，窗口被厚厚的黑布遮住，只有一絲光線從門縫\n"
"中透過，只能隱約的看到幾個人影躺在靠牆的大床上休息。\n"
);        
        set("valid_startroom",1);
        set("no_steal", "1");
        set("no_fight", "1");
        set("sleep_room",1);
        set("exits", ([
                "north" : __DIR__"nzlangw3",
        ]));
        setup();
        replace_program(ROOM);
}