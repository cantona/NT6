// midao3.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "祕密通道");
        set("long", @LONG
這是一段又長又黑的祕密通道，隱約可以感覺到四周是冰冷而堅硬
的石壁，你什麼了看不清楚，只可以靠摸索着前進。
LONG );
        set("exits", ([
                "south" : __DIR__"midao2",
                "out" : __DIR__"muwu1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -1000);
        set("coor/z", -40);
        setup();
}

int valid_leave(object me,string dir)
{
        if(dir=="out") 
         tell_object(me,"你走出了祕密通道，神祕地出現在一間木屋之中。\n");
         return ::valid_leave(me,dir);
}
