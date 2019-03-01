// Room: /d/wuyi/xiangshengyan.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "響聲巖");
        set("long", @LONG
位于六曲溪南的響聲巖，又名下城高。因有空谷傳聲的感應，故名
響聲巖。朱熹手跡“逝者如斯”四字于此，為武夷山最早的摩崖石刻。
隔溪斜對面，就是雲窩了。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "northdown" : __DIR__"6qu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1350);
        set("coor/y", -5020);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
