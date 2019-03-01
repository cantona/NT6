inherit ROOM;

void create()
{
        set("short", "馬莊後院");
        set("long", @LONG
這裡是馬莊的後院，布景和大院差不多。四周雖然聚集著
許多乞丐，但院內卻是打整得很幹凈，便似一個大戶人家的庭
園一般。通往大廳的門前守衛著幾個乞丐。
LONG);
        set("outdoors", "yangzhou");
        set("region", "yangzhou");
        set("exits", ([
                "south" : __DIR__"ma_zhengting",
                "north" : __DIR__"ma_dayuan",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                "/d/gaibang/npc/6dai" : 1 + random(2),
                "/d/gaibang/npc/7dai" : random(2),
                CLASS_D("gaibang") + "/quan" : 1,
        ]));
	set("coor/x", 30);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        object guard;

        if (dir != "south"
           || ! objectp(guard = present("quan guanqing", this_object())))
                return ::valid_leave(me, dir);

        return guard->permit_pass(me, dir);
}