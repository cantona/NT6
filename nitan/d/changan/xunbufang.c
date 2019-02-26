//Room: xubufang.c

inherit ROOM;

void create ()
{
        set ("short", "巡捕房");
        set("long", @LONG
這裏是長安城裏維持治安的巡捕工作的地方。房門口放着兩個青
銅獅，房內是一個大廳，牆上漆着白色的漆，漆得很厚，彷彿不願人
看出這牆是石壁，是土，還是銅鐵所做。有幾個橫眉立目，嘴臉兇頑
的巡捕坐在一起，似乎在商量着什麼。南邊有一個小門，似乎上了鎖。
LONG );
        set("exits", ([
                "west" : "/d/changan/fengxu5",
        ]));
        set("objects", ([
                "/d/changan/npc/butou"  : 1,
                "/d/changan/npc/guanbing" : 2,
        ]));

        set("coor/x", -10690);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_open", "open");
}

int do_open(string arg)
{
        object me, key, nroom;
        me = this_player();
        if (! arg || arg != "door")
                return notify_fail("你要打開什麼？\n");

        if (! (key = present("laofang key", me)))
                return notify_fail("你沒有開這道門的鑰匙。\n");

        if (! (nroom = find_object("/d/changan/laofang")))
                      nroom = load_object("/d/changan/laofang");

        set("exits/south", "/d/changan/laofang");
        set("exits/north", __FILE__, nroom);
        message("vision", "只聽喀嚓！一聲，鑰匙斷了。好"
                "在牢門已經開了。\n", this_object() );
        set_temp("used_laofang_key", 1, me);
        destruct(key);
        call_out("close_door",60);
        return 1;
}

void close_door()
{
        delete("exits/south");
        }