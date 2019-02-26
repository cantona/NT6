// midao7.c 密道

inherit ROOM;

void create()
{
        set("short", "祕密通道");
        set("long", @LONG
這是一個石室，地上和角落都是灰塵，大概好久沒人來過了。在
石縫之間，長着幾棵小草(cao) ，你仔細一看，原來它就是斷腸蝕骨
腐心草。
LONG );
       set("exits", ([
               "east"    : __DIR__"midao6",
               "out"     : __DIR__"dating",
               "northup" : __DIR__"midao8",
       ]));
       set("objects", ([
               "/clone/medicine/vegetable/fuxincao" : 1,
       ]));
        set("coor/x", -3090);
        set("coor/y", -25000);
        set("coor/z", -20);
        setup();
}

int valid_leave(object me,string dir)
{
        if(dir=="out")
            tell_object(me,"你走出了祕密通道，神祕地出現在大廳之中。\n");
        return ::valid_leave(me,dir);
}