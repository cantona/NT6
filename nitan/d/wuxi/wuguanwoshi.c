// Room: /d/wuxi/wuguanwoshi.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "卧室");
        set("long", @LONG
這是秦教頭的卧室，由於秦教頭門下弟子眾多，秦教頭手頭也頗為
寬綽，房裏佈置得自然是相當華麗。紅木大牀上鋪着錦緞花被，雲絲羅
帳低垂，屋角燃着檀香，顯得十分安靜。
LONG );
        set("exits", ([
                "west" : __DIR__"wuchang",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1070);
	set("coor/y", -700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}