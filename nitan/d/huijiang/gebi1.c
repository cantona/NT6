// Room: /d/huijiang/gebi1.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "戈壁");
        set("long", @LONG
焦熱的陽光曬著茫茫的戈壁，天地之間只剩下黃色的沙，連綿起伏
的沙丘一眼望不到邊。前面不遠的沙地上微微隨風而動的是沙漠中的鐵
草，耐旱，看來你快走出這片沙漠了。
LONG );
        set("outdoors", "huijiang");
        set("exits", ([ /* sizeof() == 2 */
                "northeast" : "/d/xingxiu/shanjiao",
                "west"      : __DIR__"shamo1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", 9000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}