inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這裏是少林寺的練武場。由無數塊巨大的花崗巖石板鋪就。上千
年的踩踏已使得這些石板如同鏡子般平整光滑。練武場中間豎立着不
少木人和草靶。西邊角上還有兩個大沙坑，十來個僧人正在練習武藝。
東西兩面各有一長溜僧房。
LONG );

        set("exits", ([
                "south" : __DIR__"fzlou",
                "east" : __DIR__"hsyuan1",
                "west" : __DIR__"hsyuan4",
                "north" : __DIR__"guangchang5",
                "northup" : __DIR__"dmyuan",
        ]));

        set("outdoors", "shaolin");

        set("objects",([
                CLASS_D("shaolin") + "/dao-cheng" : 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        if( !query("luohan_winner", me) && !wizardp(me) )
        {
                if (dir == "northup")
                {
                        return notify_fail("你級別不夠，不能進入達摩院。\n");
                }
        }
        return ::valid_leave(me, dir);
}
