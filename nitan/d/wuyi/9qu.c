// Room: /d/wuyi/9qu.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "九曲");
        set("long", @LONG
九曲在兩峰夾縫中流淌，西面往去，就是一馬平川了。溪流在此
慢慢閃動，全長二十裡的九曲溪由此東去，穿越叢峰，直抵崇陽溪。
朱熹《九曲棹歌》曰：“……九曲將窮眼豁然，桑麻雨露見平川。漁
郎更覓桃源路，除是人間別有天。”
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : __DIR__"8qu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1320);
        set("coor/y", -5030);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
