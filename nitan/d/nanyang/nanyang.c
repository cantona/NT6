// Room: /d/nanyang/nanyang.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;

void create()
{
        set("short", "南陽城");
        set("long", @LONG
這裡便是當年諸葛先生的故居。南陽城雖不大，因為地出要沖，南
來北往的客人特別多，所以也五臟俱全，酒樓，客棧，馬店，滿城子都
是。本地人口甚少，到處都是行色匆匆的江湖客人。
LONG );
        set("exits", ([
                "south" : __DIR__"dajie1",
                "north" : __DIR__"dajie2",
                "east"  : __DIR__"kedian1",
                "west"  : __DIR__"jiulou1",
        ]));
        set("objects",([
                "/d/shaolin/npc/xiao-fan" : 1,
        ]));
        set("outdoors", "nanyang");
	set("coor/x", -6940);
	set("coor/y", 770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}