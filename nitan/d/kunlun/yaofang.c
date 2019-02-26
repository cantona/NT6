// Room: /d/kunlun/yaofang.c
// Last Modified by winder on Nov. 15 2000

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "藥房");
        set("long", @LONG
這裏是崑崙派的藥房，房間裏瀰漫着濃濃的藥香，房間內排滿了裝
滿各類藥材的大藥櫃，每個藥櫃都有上百個裝藥的抽屜貼滿了各類藥名。
西邊是一個巨大紅杉木櫃，櫃上貼着方丈印的封條。一位年輕女子正來
回忙碌着指點眾執役稱量藥品，熬藥煎湯。
LONG );
        set("exits", ([
                "southeast" : __DIR__"jiuqulang6", 
        ]));
        set("objects", ([
                __DIR__"npc/kl-dizi1" : 1, 
        ]));
        set("no_clean_up", 0);
        set("coor/x", -120010);
        set("coor/y", 40120);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}