inherit ROOM;

void create()
{
        set("short", "雜貨舖");
        set("long", @LONG
這裡是北京城東長安街最東邊的一家雜貨舖，雜貨舖不大，門前
高高的掛著一條橫幅，上面寫著『南北貨』三個大字，橫幅紙張已經
泛黃，看來這家店舖在這裡已經有一段歷史了。店舖裡大箱小箱堆滿
了一地，都是一些普通的日常用品。店舖掌櫃懶洋洋地躺在一只躺椅
上，招呼著過往行人。
LONG );
        set("exits", ([
                "west" : "/d/beijing/caroad_e2",
        ]));
        set("objects", ([
                "/d/beijing/npc/hu": 1,
        ]));

	set("coor/x", -2760);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}