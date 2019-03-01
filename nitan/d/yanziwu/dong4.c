// Room: /d/yanziwu/dong4.c
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
                "south"  : __DIR__"dong3",
                "north"  : __DIR__"dong2",
                "east"   : __DIR__"dong4",
                "west"   : __DIR__"dong5",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1210);
        set("coor/y", -1270);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}