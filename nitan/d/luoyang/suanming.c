inherit ROOM;

void create()
{
        set("short", "茅草屋");
        set("long", @LONG
這是一座歪歪斜斜的茅草屋，牆頭的顏色很怪，一種血色幹凝的暗紅
色。屋裡更是鬼氣森森。房子無窗，一盞油燈忽明忽暗。以太極八卦圖為
底的招牌上用篆體刻著「刺青」二字，也是黯淡無光的紅色。
LONG);
        set("no_clean_up", 0);
    set("no_sleep_room",1);
        set("exits", ([
                  "south" : __DIR__"hutong3",
        ]));

        set("objects", ([ //sizeof() == 3
               "/clone/npc/walker"  : 1, 
        ]));
	set("coor/x", -6940);
	set("coor/y", 2190);
	set("coor/z", 0);
	setup();
        "/adm/npc/qingyangzi"->come_here();
        replace_program(ROOM);
}