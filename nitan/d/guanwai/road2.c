// /guanwai/road2.c
inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
這裏是通往關外的官道，幾米寬的大道，全部由黃土鋪成，可並行三四
輛馬車而不顯擁擠。這裏是進出關口的必經之路，路上三倆成羣的行人都是
往來販運皮貨，藥材的生意人。偶爾有身着官兵騎馬飛馳而過。
LONG );
        set("exits", ([
                "northeast" : __DIR__"road3",
                "southwest" : __DIR__"road1",
        ]));
        set("no_clean_up", 0);
         set("outdoors", "guanwai");
        set("coor/x", 3960);
	set("coor/y", 9140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
