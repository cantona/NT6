// Room: /d/yanziwu/yunjin1.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "雲錦一樓");
        set("long", @LONG
小樓檐下一塊匾額，寫着“雲錦樓”三個墨綠篆字，樓下前後左右
種的都是茶花。但這些茶花在大理都不過是三四流貨色，和這精緻的樓
閣亭榭相比，未免不襯。
LONG );
        set("exits", ([
                "north"  : __DIR__"path8",
                "south"  : __DIR__"garden",
                "up"     : __DIR__"yunjin2",
        ]));
        set("objects", ([
                "/d/dali/obj/chahua11" :1,
                __DIR__"npc/xiaocha" :1,
        ]));
        set("coor/x", 1230);
        set("coor/y", -1260);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}