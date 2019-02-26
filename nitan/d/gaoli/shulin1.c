// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "樹林");
        set("long", @LONG
你走在一片樹林之中。這裏樹木茂盛，參天蔽日，非常涼快。西邊
就是高麗的朝陽門了。有很多人從你身旁擦肩而過。看來高麗的繁華遠
勝過處在戰亂中的中原。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southwest" : __DIR__"baihumen",
                "northeast":__DIR__"shulin2",
        ]));
       setup();
        replace_program(ROOM);
}        
