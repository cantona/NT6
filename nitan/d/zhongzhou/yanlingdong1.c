inherit ROOM;

void create()
{
          set ("short", "延陵東路");
          set ("long", @LONG
這是中州的一條老路延陵路。它東西橫跨中州城。路北的
一片房子看是雖然不是很新，可一看就知道是大户人家。兩個
家丁叉腰守着門口，彷彿可到這户人家做家丁是很了不起的事。
LONG);
        set("outdoors", "zhongzhou");

          set("exits", ([
                    "west" : __DIR__"yanlingdong",
                    "north" : __DIR__"yuanwan",
                    "southeast"  : __DIR__"yanlingdong2",
        ]));

        set("objects" , ([
                __DIR__"npc/jiading" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -9020);
	set("coor/y", -1000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}