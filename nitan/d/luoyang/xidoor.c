inherit ROOM;

void create()
{
        set("short", "內城西門");
        set("long", @LONG
洛陽內城西門高三丈，寬約二丈有餘，尺許厚的城門上鑲滿了拳頭般
大小的柳釘。門洞長約四丈，大約每隔兩個時辰就換官兵把守。洞側帖滿
了懸賞捉拿之類的官府通諜，一條筆直的青石板大道向東西兩邊延伸，東
去就是洛陽內城了，向西一橋高高跨過洛陽城護城河。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"wroad7",
                "west" : __DIR__"wbridge",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/guanbing" : 4,
                "/d/beijing/npc/ducha" : 1,
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -7050);
	set("coor/y", 2180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}