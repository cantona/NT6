// Room: /d/yueyang/loumen.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "岳陽樓門");
        set("long", @LONG
這裏是岳陽樓的大門，門上是一幅黑底藍字對聯“洞庭天下水，嶽
陽天下樓”。岳陽樓建在岳陽城樓上，建築精巧雄偉，與洪都滕王閣、
武昌黃鶴樓並稱江南三大名樓，
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"huaiputing",
                "southdown" : __DIR__"ximen",
        ]));
	set("coor/x", -6220);
	set("coor/y", -3000);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}