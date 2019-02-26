inherit ROOM;
void create()
{
          set ("short", "延陵西路");
          set ("long", @LONG
從市中心往西走就到了延陵西路，這裏中州城內的一條老
街。兩邊的房屋看上去已經很陳舊了。街道的南面的一間鄰街
的房子看上去象是一家店鋪。
LONG);

        set("outdoors", "zhongzhou");

          set("exits", ([  
                    "west" : __DIR__"yanling1",
                    "south" : __DIR__"dangpu",
                    "east"  : __DIR__"shizhongxin",
        ]));

        set("coor/x", -9050);
	set("coor/y", -1000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}