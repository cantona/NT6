// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "樹林");
        set("long", @LONG
你走在一片樹林之中。這裡樹木茂盛，參天蔽日，非常涼快。四下
望了望，看不到樹林的邊界，看來這片樹林非常大。一陣清風吹過，樹
木發出沙沙的聲音。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southwest" : __DIR__"shulin1",
                "north":__DIR__"shulin3",
        ]));
       setup();
        replace_program(ROOM);
}        
