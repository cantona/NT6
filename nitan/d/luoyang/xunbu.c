inherit ROOM;

void create()
{
        set("short", "巡捕房");
        set("long", @LONG
這裏是官府發放通緝令的地方，凡是出現什麼江洋大盜，大魔頭，殺
人犯，都要有這裏頒佈命令，整個洛陽城裏的捕頭們才可以展開追捕行動。
巡捕房面積不大，裏面放着一個紅木大桌用來辦公。平時，普通百姓是不
允許進來的。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"laofang",
                  "south" : __DIR__"wroad3",
        ]));
        set("objects", ([
                "clone/npc/xunbu" : 2,
        ]));

	set("coor/x", -7020);
	set("coor/y", 2190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}