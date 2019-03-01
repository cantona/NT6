// Room: /d/wuxi/wuguanwoshi.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "臥室");
        set("long", @LONG
這是秦教頭的臥室，由于秦教頭門下弟子眾多，秦教頭手頭也頗為
寬綽，房裡布置得自然是相當華麗。紅木大床上舖著錦緞花被，雲絲羅
帳低垂，屋角燃著檀香，顯得十分安靜。
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