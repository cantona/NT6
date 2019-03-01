inherit ROOM;

void create()
{
        set("short", "永徽道");
        set("long", @LONG
站在永徽大街上，你會發現這條街有快慢道之分，街道兩旁栽植鬆柏，
到處是張燈結彩。大街兩旁排列著許多店舖。臨街店舖裡經營著汴繡、字
畫、陶瓷、古董、名酒、小吃等，熱鬧非凡。北邊是一所私塾，南邊是替
人締結婚約和解除婚約的地方，叫一線牽。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"eroad3",
                  "north" : __DIR__"sishu",
                  "south" : __DIR__"yuelao",
                  "west" : __DIR__"eroad1",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy1" : 1,
                "/d/beijing/npc/old2" : 1,
        ]));
	set("coor/x", -6970);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}