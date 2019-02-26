// ximenroad.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long",
"唐家鎮郊外的樹林，松枝挺拔，喬木橫斜。林間小道，逶迤隨遠。林\n"
"中蟬鳴廝鬧，鳥啼宛轉，使你頓時煩意盡消。再往前就到了蜀中唐門了。\n"
);
        set("exits", ([
                "northup" : __DIR__"ximenroad2",
                "southeast" : __DIR__"ximen",
        ]));
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}