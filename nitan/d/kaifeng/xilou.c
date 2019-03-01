inherit ROOM;

void create()
{
        set("short", "戲樓");
        set("long", @LONG
一座木頭粗粗搭起的高台，台的後端用大的簾子遮了起來那後頭
就是戲子裝扮上台的地方。由于是關帝廟的緣故，演的無非是桃園三
結義，單騎走千裡。杯酒斬文聵等故事。
LONG );
        set("objects", ([
                  __DIR__"npc/qingyi" : 1,
                  __DIR__"npc/xiaosheng" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"paifang",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5010);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}