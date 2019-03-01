// Room: /d/qilian/shalu1.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "碎石沙路");
        set("long", @LONG
你走在一條荒僻的碎石沙路上，東北面有一座雄偉的關隘，西南通
向酒泉。
LONG );
        set("outdoors", "qilian");
        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : "/d/xingxiu/jiayuguan",
                "southwest" : __DIR__"shalu2",
        ]));
        set("coor/x", -20000);
        set("coor/y", 300);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}