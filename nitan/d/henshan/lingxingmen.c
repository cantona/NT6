inherit ROOM;

void create()
{
        set("short", "欞星門");
        set("long", @LONG
這裡是南岳大廟的第一道門，由漢白玉，花崗石打就的石牌坊。
南岳衡山是祝融遊息之地，道教奉為第三小洞天。在此遠望衡山，山
勢如飛，如雲霧中凌空的大鳥。
LONG );
        set("exits", ([
                "north"  : __DIR__"kuixingge",
                "south"  : __DIR__"hengyang",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}