#include <room.h>

inherit ROOM;

void create()
{
        set("short", "物品房");
        set("long", @LONG
這是物品房，一個大架子。上面放的整整齊齊，看來這裡
的管家是很認真負責的，一些人正在跟管物品工具的青年說著
什麼。
LONG);
        set("no_fight", 1);
        set("exits", ([
               "south" : __DIR__"guofu_lang4",
               "north" : __DIR__"guofu_lang6",
               "west" : __DIR__"guofu_shilu-1",
        ]));
        set("objects", ([
           	__DIR__"npc/wuxiuwen" : 1,
        ]));
        setup();
        replace_program(ROOM);
}