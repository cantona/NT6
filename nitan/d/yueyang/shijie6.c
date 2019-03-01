// Room: /d/yueyang/shijie6.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "青石階");
        set("long", @LONG
這是酒香亭傍的石階，這裡往南，就是懸崖。北面是酒香亭。懸崖
下，有龍虎猴三洞，崖的高處，有一座石台。每年的丐幫君山大會，都
是在那台上舉行。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"jiuxiangting",
                "westup" : __DIR__"xuanyuantai",
        ]));
        set("coor/x", -1780);
        set("coor/y", 2270);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}