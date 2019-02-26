// Room: /d/huanggong/wenhua.c

inherit ROOM;

void create()
{
        set("short", "文華殿");
        set("long", @LONG
這裏是文華殿, 在這陳列着許許多多千奇百怪的奇珍異寶. 這裏是
皇帝舉行經筵講習的地方, 每年春秋兩季, 由經筵講官在此向皇帝講解
四書五經, 再由皇帝復講一遍, 並有王公大臣陪讀.
LONG
        );
        set("exits", ([
                "west"      : __DIR__"guangchang",
                "east"      : __DIR__"donghuamen",
                "south"     : __DIR__"wenyuange",
                "southeast" : __DIR__"guoshiguan",
                "southwest" : __DIR__"neigedatang",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2790);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}