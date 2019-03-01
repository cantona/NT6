inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
你走在青石板舖成的石階上。這裡就是傳說中神秘的白駝山。遠
遠望去，兩座白沙堆積形成的山峰好像一只駱駝的脊背。一座山門立
在你的眼前。
LONG );
        set("exits", ([
                "east"      : __DIR__"caoping",
                "northup"   : __DIR__"damen",
                "southdown" : __DIR__"guangchang" ,
        ]));
        set("outdoors", "baituo");
        set("coor/x", -49980);
        set("coor/y", 19990);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}