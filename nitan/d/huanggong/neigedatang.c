// Room: /d/huanggong/neigedatang.c

inherit ROOM;

void create()
{
        set("short", "內閣大堂");
        set("long", @LONG
內閣大堂內設典籍庫, 主要收集國朝; 檔案, 實錄和聖訓等書.
LONG
        );
        set("exits", ([
                "northeast"  : __DIR__"wenhua",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2800);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}