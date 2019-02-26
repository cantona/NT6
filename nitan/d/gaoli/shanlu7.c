// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一條山路上。南邊就是高麗的玉龍門了。這裏的地形起伏，
有些崎嶇。這裏的行人比較多。有幾個人正在附近挖野菜。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southwest" : __DIR__"shanlu6",
                "north":__DIR__"shanlu8",
        ]));
       setup();
        
}

