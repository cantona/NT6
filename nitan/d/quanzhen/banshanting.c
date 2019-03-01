// banshanting.c 半山亭
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "半山亭");
        set("long", @LONG
這裡是半山腰的一個小涼亭，遊客們爬山爬的累了，就轉個彎到
這裡來坐一坐，歇一歇腳。從這裡看下去，剛好可以看見翠屏峰的峰
頂。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "southdown" : __DIR__"shijie5",
        ]));

        set("objects",([
                __DIR__"npc/youke" : 2,
                "/clone/npc/walker"  : 1,
        ]));

        set("coor/x", -3150);
        set("coor/y", 140);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}
