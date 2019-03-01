// Room: /d/huijiang/gebi2.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "戈壁");
        set("long", @LONG
焦熱的陽光曬著茫茫的戈壁，軟綿的黃沙開始被大大小小的礫石所
代替。砂石之間的地面上開始出現青草，前面傳來潺潺的流水聲。看來
不遠就有水源了。
LONG);
        set("outdoors", "huijiang");
        set("exits", ([ /* sizeof() == 2 */
                "west" : __DIR__"xiaoxi",
                "east" : __DIR__"shamo4",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50010);
        set("coor/y", 9000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
