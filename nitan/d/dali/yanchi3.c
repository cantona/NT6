//Room: /d/dali/yanchi1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","沿池堤岸");
        set("long", @LONG
這裡是滇池遊客聚集之處，演鄯候高生世就時時承舟優勝于煙水
緲藹的滇池，欣賞『梵剎于滇波向仰抑』的美景，並常停舟官渡，飲
酒賦詩，被稱之為『停舟煙會』。這裡的東浦彩虹、西山白雨、空中
鷺鷥、晚霞潮紅、歸帆遠影、無不給人以美的享受。
LONG );
        set("objects", ([
           "/d/dali/npc/guigongzi": 1,
           "/d/dali/npc/enu": 2,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "west"      : "/d/dali/yanchi2",
            "southeast" : "/d/dali/luojiadian",
        ]));
	set("coor/x", -19080);
	set("coor/y", -6860);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}