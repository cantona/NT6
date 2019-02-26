//Room: /d/dali/center.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","中心廣場");
        set("long", @LONG
這裏就是大理城的中心，彩色石塊鋪成的大道向四方伸延。廣場
呈菱形，一圈圍的都是小販，藝人，和看熱鬧的。熙熙攘攘的人羣中
也少不了幾個跑江湖之人，一些在中原聞所未聞的事物令一些剛入江
湖之人興奮不已。
LONG );
        set("objects", ([
           "/d/dali/npc/jianghuyiren": 1,
                "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 4 */
            "north"  : "/d/dali/taihejiekou",
            "south"  : "/d/dali/shizilukou",
            "east"   : "/d/dali/taiheju",
        ]));
	set("coor/x", -19130);
	set("coor/y", -6890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}