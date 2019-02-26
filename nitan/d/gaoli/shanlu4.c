// /d/gaoli/xuanwumen
// Room in 高麗
inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裏是一條山路。這裏的山路崎嶇曲折，很難找到出路。一不小心，
就可能滾落下去。向東望去，可以看到高麗城的全貌。
LONG
        );

        set("exits", ([
                "eastdown" : __DIR__"shanlu3",
                "northup":__DIR__"shanlu5",
        ]));

         set("outdoors", "gaoli");
        setup();
        replace_program(ROOM);
}


