// Room: /d/yanziwu/dong1.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "潮聲洞");
        set("long", @LONG
洞裡伸手不見五指。隱隱聽到湖浪沖擊巨巖，延綿不絕。你在洞裡
摸索前行，聽著潮聲引導，試圖找到出洞的方向。
LONG );
        set("exits", ([
                "out"    : __DIR__"path20",
                "south"  : __DIR__"dong2",
                "north"  : __DIR__"dong3",
                "east"   : __DIR__"dong4",
                "west"   : __DIR__"dong1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1200);
        set("coor/y", -1270);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}