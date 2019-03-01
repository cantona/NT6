//Room: /d/dali/yanan1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","滇池沿岸");
        set("long", @LONG
滇池名曰池，實際上是個很大的湖，四面山上水源眾多，也澆灌
了大片的農田。池水清澈涼爽，許多羅伽部的婦女在此洗衣挑水。擺
夷並不以漁業為主，不過岸邊仍然建有小碼頭，時常有遊船停靠，也
有少量竹舟下水打魚。西邊有條彎彎曲曲的小路沿著滇池南岸而去。
LONG );
        set("objects", ([
           "/d/dali/npc/cunfu": 2,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "northeast" : "/d/dali/luojiadian",
            "west"      : "/d/dali/yanan2",
        ]));
	set("coor/x", -19080);
	set("coor/y", -6880);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}