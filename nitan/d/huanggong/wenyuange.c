// Room: /d/huanggong/wenyuange.c

inherit ROOM;

void create()
{
        set("short", "文淵閣");
        set("long", @LONG
這裡是中央圖書館. 收藏了＜永樂大典＞, ＜四庫全書＞, ＜古今
圖書集成＞, ＜武英殿聚珍版叢書＞ 等豪著.
LONG
        );
        set("exits", ([
                "north"      : __DIR__"wenhua",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2790);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}