inherit ROOM;

void create()
{
        set("short", "內城南門");
        set("long", @LONG
洛陽內城南門高三丈，寬約二丈有余，尺許厚的城門上鑲滿了拳頭般
大小的柳釘。門洞長約四丈，大約每隔兩個時辰就換官兵把守。洞側帖滿
了懸賞捉拿之類的官府通諜，一條筆直的青石板大道向南北兩邊延伸，北
去就是洛陽內城了，向南一條長長的山麓橫過你的視野。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"sroad7",
                  "south" : __DIR__"guandaos1",
                "east" : __DIR__"suishi6",
                  "west" : __DIR__"suishi7",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/guanbing" : 4,
                "/d/beijing/npc/ducha" : 1,
                "/clone/npc/walker" : 1,
        ]));

	set("coor/x", -6990);
	set("coor/y", 2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}