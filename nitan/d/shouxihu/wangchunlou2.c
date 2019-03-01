// Room: /yangzhou/wangchunlou2.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short","望春樓");
        set("long",@LONG
望春樓樓上均為活動門窗，卸去則成露台，為賞月佳處。上懸鄭板
橋墨跡“望春樓”匾，兩柱懸掛張九齡李白集句楹聯(lian)。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : HIG"
        飛        雙
        閣        橋
        凌        落
        芳        彩
        樹        虹
\n"NOR,
        ]));
        set("objects", ([
                "/d/city/npc/lady2" : 1,
        ]));
        set("exits", ([
                "down" : __DIR__"wangchunlou",
        ]));
        set("coor/x", -30);
        set("coor/y", 100);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}