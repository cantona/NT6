inherit ROOM;

void create()
{
        set("short", "永徽道");
        set("long", @LONG
站在永徽大街上，你會發現這條街有快慢道之分，街道兩旁栽植鬆柏，
到處是張燈結彩。大街兩旁排列著許多店舖。臨街店舖裡經營著汴繡、字
畫、陶瓷、古董、名酒、小吃等，熱鬧非凡。北邊是廟會所在，非常的熱
鬧，人山人海，人聲鼎沸，在裡面可以找到你所想要的東西，南邊是一家
胭脂店，有不少年輕女子前來光顧。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"eroad5",
                  "north" : __DIR__"miaohui",
                  "south" : __DIR__"jinyin",
                  "west" : __DIR__"eroad3",
        ]));
        set("objects", ([
                "/d/beijing/npc/girl1" : 1,
                "/d/beijing/npc/xiaofan" : 1,
        ]));
	set("coor/x", -6950);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}