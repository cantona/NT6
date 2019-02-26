// Room: /d/shaolin/cjlou.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "藏經樓");
        set("long", @LONG
大明寺藏經之富，天下罕有其匹。這裏都是密密麻麻，高及頂棚的
書架，書架間僅有容身一人通行的空隙。幾排大書架中間，間隔地放着
數丈長的書桌。
LONG );
        set("exits", ([
                "south" : __DIR__"daxiongbaodian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -30);
        set("coor/y", 180);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}