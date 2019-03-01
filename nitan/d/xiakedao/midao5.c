// midao5.c 密道

inherit ROOM;

void create()
{
        set("short", "秘密通道");
        set("long", @LONG
這是一個石室，隱約可以感覺到四周是冰冷而堅硬的石壁，地
上和角落都是灰塵，大概好久沒人來過了。
LONG );

        set("exits", ([
               "east" : __DIR__"midao4",
               "out"  : __DIR__"neiting",
        ]));
        set("objects", ([
//               NOSTRUM_DIR"binghuojiu" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3090);
        set("coor/y", -25000);
        set("coor/z", -20);
        setup();
}

int valid_leave(object me,string dir)
{
        if(dir=="out")
                tell_object(me,"你走出了秘密通道，神秘地出現在內廳之中。\n");
        return ::valid_leave(me,dir);
}