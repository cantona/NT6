//ROOM: xiaohuayuan.c

inherit ROOM;

void create()
{
        set("short", "小花園");
        set("long", @LONG
從昏暗的地道中出來，你發現自己竟是置身于一個極精致的小花
園中，紅梅綠竹，青鬆翠柏，布置得頗具匠心，往東去是一間精雅小
舍。
LONG );
        set("exits", ([
            "south" : __DIR__"didao6",
            "enter" :__DIR__"xiaoshe",   
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}