inherit ROOM;

void create()
{
        set("short", "南疆沙漠");
        set("long", @LONG
這就是浩瀚的塔克拉馬幹大沙漠，一走進來，你仿佛迷失
了方向。你感到口內十分焦渴，還是快些離開吧。
LONG );
        set("exits", ([
                "northeast" : __DIR__"nanjiang",
                "southwest" : __FILE__,
                "southeast" : __DIR__"nanjiang2",
                "northwest" : __FILE__,
                "north"     : __FILE__,
                "south"     : __FILE__,
                "west"      : __FILE__,
                "east"      : __FILE__,
        ]));

        set("outdoors", "xiyu");
        set("no_map", "這裡的地形令人迷惑，無法繪制地圖。\n");

        setup();
}

int valid_leave(object me, string dir)
{
        int current_water;

        if (! interactive(me))
                return ::valid_leave(me, dir);

        current_water=query("water", me);
        if (current_water == 0)
        {
                write("你已經感到不行了，冥冥中你覺得有人把你抬到天山腳下。\n");
                me->move(__DIR__"shanjiao");
                me->unconcious();
                return -1;
        }

        if (current_water <= 20)
        {
                write("你過于缺水，眼冒金星。\n");
                set("water", 0, me);
        } else
        if( !objectp(present("bigu fu", me)) && query("reborn/times", me) < 3 )
                addn("water", -20, me);

        if (random(2))
        {
                me->move(sprintf(__DIR__"nanjiang%d", random(3) + 1));
                return -1;
        }

        return ::valid_leave(me, dir);
}
