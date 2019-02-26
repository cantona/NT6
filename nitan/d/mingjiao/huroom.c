// huroom.c
inherit ROOM;

void create()
{
        set("short", "醫居");
        set("long", @LONG
你走進了烈火旗的大院後進，這裏是個很寧靜的小屋。四周擺了
不少醫學典籍，還有很多散落堆放的膏、丸、散等。一個老頭在此呆
呆出神，似乎有無限心事。
LONG );
        set("exits", ([
                "out"     : __DIR__"lhqyuan",
        ]));
        set("objects", ([
                __DIR__"npc/hu" : 1,   //蝴蝶谷/d/wudang/wroad2 
        ]));
        set("outdoors", "mingjiao");
        set("no_fight", 0);
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
