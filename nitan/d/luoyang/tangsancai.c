inherit ROOM;

void create()
{
        set("short", "唐三彩");
        set("long", @LONG
瓷器之中以唐三彩最為名貴，而洛陽的唐三彩又是出的最多，而且最
有名的。這家店鋪的主人獨闢蹊徑，在此開了一家唐三彩專賣店，生意相
當興隆。據説，唐三彩上色時所有的顏色均只以紅，黃，懶三原色為基礎
手工調製而成，故極其的珍貴。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"nroad1",
        ]));
        set("objects", ([
                __DIR__"npc/qin" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}