// Room: /d/wuxi/guangchang.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "三陽廣場");
        set("long", @LONG
這是無錫的正中心，一個很寬闊的廣場，都是用很大很整齊的青石
鋪成，關於這裏為什麼叫做“三陽”，卻沒人説得上來了。一些遊手好
閒的人在這裏溜溜達達。你可以看到北邊有來自各地的行人來來往往，
南面人聲鼎沸，一派繁華景象，西邊好像很熱鬧，東邊則有些肅靜。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"northroad1",
                "south" : __DIR__"southroad1",
                "east"  : __DIR__"eastroad1",
                "west"  : __DIR__"westroad1",
        ]));
        set("coor/x", 1040);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}