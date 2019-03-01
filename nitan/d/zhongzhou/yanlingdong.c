inherit ROOM;

void create()
{
          set ("short", "延陵東路");
          set ("long", @LONG
從市中心往東走就到了延陵東路，這裡中州城內的一條老
街。兩邊的房屋看上去已經很陳舊了。出門在外到這種地方來
轉一轉也別有一番滋味。
LONG);

        set("outdoors", "zhongzhou");

          set("exits", ([  
                    "west" : __DIR__"shizhongxin",
                    "east"  : __DIR__"yanlingdong1",
        ]));
       
        set("objects", ([
                "d/city/npc/liumang" : 1,
        ]));

        set("coor/x", -9030);
	set("coor/y", -1000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}