// Room: /d/shaolin/chufang.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
炊煙繚繞，蒸汽騰騰，香味撲鼻而來。靠牆是一排數丈長的灶台，
支着十來口大鍋，最大的一口飯鍋上方竟有人從樑上懸空而下，手持
木棍在攪拌。除了燒飯的僧人外，幾位火工頭陀忙着劈柴運薪，灶下
爐火熊熊。一位中年僧人正來回催促着。
LONG );
        set("exits", ([
                "south" : __DIR__"fanting1",
        ]));
        set("objects",([
                __DIR__"npc/shaofan-seng" : 2,
        ]));
        set("resource/water", 1);
        setup();
        replace_program(ROOM);
}
