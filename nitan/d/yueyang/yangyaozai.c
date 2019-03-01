// Room: /d/yueyang/yangyaozai.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "楊麼寨");
        set("long", @LONG
楊麼寨在西山，相傳是南宋初年洞庭湖農民起義軍領袖楊麼兵營的
遺址。山寨三關依舊，寨柵仍在，當可想見當初英雄們氣吞萬裡如虎的
氣勢和驚天動地的業績。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"jiuxiangshan",
        ]));
        set("coor/x", -1790);
        set("coor/y", 2290);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}