// Room: /d/wuyi/3qu.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "三曲");
        set("long", @LONG
溪水在回流中打轉，碧透的水中，遊魚匆匆。南面可以看到大藏峰
峻直的巖壁和壁洞中的稻草。朱熹《九曲棹歌》曰：“……二曲君看架
壑船，不知停棹幾何年？桑田海水今如許，泡沫風燈敢自憐。……”
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "southeast" : __DIR__"2qu",
                "southwest" : __DIR__"4qu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1380);
        set("coor/y", -5000);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
