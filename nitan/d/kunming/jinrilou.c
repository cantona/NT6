inherit ROOM;

void create()
{
        set("short",  "近日古樓" );
        set("long", @LONG
近日樓地處昆明市中心，南來北往的人都從這裡通過，二
樓懸有一巨鐘，北邊是平西王府，一般人很少去那裡，西邊是
金馬枋，南邊熱鬧非凡，熙熙攘攘，人來人往。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "west" : __DIR__"jinmafang", 
                "east"  :__DIR__"bijifang",
                "south" :__DIR__"nandajie1",
                "north" :__DIR__"beidajie",
                "up"    :__DIR__"zhonglou",                           
        ]));

        set("objects", ([
                "/clone/npc/xunbu" : 1,
                "/d/beijing/npc/richman1" : 1,
        ]));                       
	set("coor/x", -16840);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}