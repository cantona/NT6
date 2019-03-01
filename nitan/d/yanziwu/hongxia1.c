// Room: /d/yanziwu/hongxia.c
// Date: Jan.28 2000 by Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIR"紅霞一樓"NOR);
        set("long", @LONG
這是一座很別致的小樓。樓檐下一塊匾額上寫著“紅霞樓”三個粉
紅篆字，樓下前後左右種的都是茶花。“滇中茶花記”載：“大理茶花
最甲海內，種類七十有二，大于牡丹，一望若火齊雲錦，爍日蒸霞。”
雲錦樓和紅霞樓均是莊主人愛人及花所建。
LONG );
        set("exits", ([
                "south"    : __DIR__"path7",
                "north"    : __DIR__"path15",
                "eastdown" : __DIR__"huafang",
                "up"       : __DIR__"hongxia2",
        ]));
        set("objects", ([
                __DIR__"obj/chahua13" : 1,
        ]));
        set("coor/x", 1250);
        set("coor/y", -1250);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}