// Room: /d/wuyi/7qu.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "七曲");
        set("long", @LONG
七曲城高巖上，高高刻着“放生潭”三個大字。九曲溪之所以能
夠綠水長流、生靈歡悦，大抵與這個放生潭的警醒不無關係。數百年
來，這三個大字已不僅僅是一種摩崖石刻了。朱熹《九曲棹歌》曰：
“……七曲移舟上碧灘，隱屏仙掌更回看。卻憐昨夜峯頭雨，添得飛
泉幾道寒。……”
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"6qu",
                "north"     : __DIR__"path7",
                "southwest" : __DIR__"8qu",
                "southeast" : __DIR__"shuiguishi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1340);
        set("coor/y", -5010);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
