//chufang.c
inherit ROOM;
void create()
{
        set("short","廚房");
        set("long", @LONG
這是間寬敞的廚房，廚師們在展示各自的烹飪絕活。整個房間彌
漫着令人垂涎欲滴的菜香。
LONG );
        set("exits",([
            "north" : __DIR__"xiaoting",
        ]));
        set("objects",([
             __DIR__"npc/nanpu" : 1,
        ]));
        set("resource/water", 1);
        setup();
        replace_program(ROOM);
}