// Room: /d/wuyi/8qu.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "八曲");
        set("long", @LONG
八曲崖岸的駱駝峯，是由三塊巨大的巖峯排列而成。小頭，聳立
的駝峯，寬大的駝背，真是感歎天工的造化。朱熹《九曲棹歌》曰：
“……八曲風煙勢欲開，鼓樓巖下水瀠洄。莫言此地無佳景，自是遊
人不上來。……”
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "southup"   : __DIR__"mopanshi",
                "northwest" : __DIR__"pinziyan",
                "northeast" : __DIR__"7qu",
                "southwest" : __DIR__"9qu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1330);
        set("coor/y", -5020);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
