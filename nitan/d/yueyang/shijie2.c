// Room: /d/yueyang/shijie2.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
這是一條青石階，連接山上的朗吟亭和山下的二妃墓。石階兩邊茶
樹連綿，竹響隨人，真是個清幽所在。遠望洞庭，湖水簇擁君山，白浪
抱青山，好一片風光。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "westup"    : __DIR__"langyinting",
                "northeast" : __DIR__"erfeimu",
                "southwest" : __DIR__"xiaolu3",
        ]));
        set("coor/x", -1680);
        set("coor/y", 2290);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}