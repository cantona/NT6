//gudao1.c

inherit ROOM;
void create()
{
        set("short","古道");
        set("long",
"一條石板古道，兩邊樹木蒼翠，山勢平緩，南面是唐家鎮的小樹林。\n"
"遠處有一片宏偉建築，一堵裏許長的紅牆隔開，越過牆頭可見一座高樓聳\n"
"立，好像正是蜀中唐門的門樓。\n"
);
        set("outdoors", "tangmen");
        set("exits",([ 
            "west"    : __DIR__"gudao2",
            "southdown"    : __DIR__"ximenroad2",
        ]));
        set("no_clean_up", 0);
        set("objects", ([ /* sizeof() == 2 */
        ]));
        setup();
        replace_program(ROOM);
}
