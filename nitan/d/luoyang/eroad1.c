inherit ROOM;

void create()
{
        set("short", "永徽道");
        set("long", @LONG
站在永徽大街上，你會發現這條街有快慢道之分，街道兩旁栽植松柏，
到處是張燈結綵。大街兩旁排列着許多店鋪。臨街店鋪裏經營着汴繡、字
畫、陶瓷、古董、名酒、小吃等，真是熱鬧非凡。向西就是洛陽中心廣場
了，南北兩邊分別是武器店和盔甲店，同屬一個老闆所開。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"eroad2",
                  "north" : __DIR__"armor",
                  "south" : __DIR__"weapon",
                  "west" : __DIR__"center",
        ]));
        set("objects", ([
                "/d/beijing/npc/maiyi1" : 1,
                "/d/beijing/npc/kid1" : 2,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}