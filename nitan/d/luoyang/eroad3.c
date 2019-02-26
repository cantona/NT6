inherit ROOM;

void create()
{
        set("short", "永徽道");
        set("long", @LONG
站在永徽大街上，你會發現這條街有快慢道之分，街道兩旁栽植松柏，
到處是張燈結綵。大街兩旁排列着許多店鋪。臨街店鋪裏經營着汴繡、字
畫、陶瓷、古董、名酒、小吃等，熱鬧非凡。北邊是一家瓷器店，南邊是
一個替人照看孩子的地方，叫育嬰堂。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"eroad4",
                  "north" : __DIR__"ciqi",
                  "south" : __DIR__"yuying",
                  "west" : __DIR__"eroad2",
        ]));
        set("objects", ([
                "/d/beijing/npc/xianren" : 1,
        ]));
	set("coor/x", -6960);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}