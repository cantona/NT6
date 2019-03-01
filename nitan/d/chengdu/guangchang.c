// Room: guangchang.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "蜀都廣場");
        set("long", @LONG
這裡是成都提督府前廣場。好空曠的地方，只有稀稀落落幾個沒
精打採的行人。北面就是提督府了，南邊是提督街。廣場周圍種了一
圈遮陽樹，但驕陽仍把青石廣場地面曬得滾燙冒煙。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "east"  : __DIR__"shuduroad1",
            "west"  : __DIR__"shuduroad2",
            "south" : __DIR__"tiduroad",
            "north" : __DIR__"tidugate",
        ]));
//        set("no_clean_up", 0);
        set("objects", ([
            "/d/city/npc/wujiang" : 2,
                "/clone/npc/walker"  : 1, 
        ]));
        set("coor/x", -15220);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}