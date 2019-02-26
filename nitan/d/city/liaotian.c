inherit ROOM;

int is_chat_room()
{
	return 1;
}

void create()
{
        set("short", "客店茶房");
        set("long", @LONG
這裏是揚州客棧的茶園，有許多無所事事的人都愛呆在這裏，店
小二穿梭在客人中間，忙個不停。許多商人小販也喜歡在這裏向大家
兜售貨物。
LONG );
        set("no_fight", 1);
        set("can_trade", 1);
        set("no_sleep_room", 1);

        set("exits", ([
                "south" : __DIR__"kedian",
        ]));

	set("coor/x", 10);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}