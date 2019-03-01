inherit ROOM;

void create()
{
          set ("short", "延陵東路");
          set ("long", @LONG
這是中州的一條老路延陵路。它東西橫跨中州城。再往東
就可以出中州城了。因到了城東了比較偏僻，這裡的本地人大
都把房子租給外地的人住了。
LONG);

        set("outdoors", "zhongzhou");

          set("exits", ([
                    "northwest" : __DIR__"yanlingdong1",
                    "east"  : __DIR__"dongmeng",
        ]));

        set("objects",([
                __DIR__"npc/gugong":1,
                __DIR__"npc/laogugong":2,
        ]));

        set("coor/x", -9010);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}