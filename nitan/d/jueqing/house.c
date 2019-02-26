inherit ROOM;

void create()
{
        set("short", "小屋");
        set("long", @LONG
這是絕情谷底的一間小茅屋，這裏似乎很久沒有來過了。
LONG);
        set("exits", ([
               "out"  :  __DIR__"underya2",
        ]));

        if (random(8) == 1)
               set("objects", ([
                      "/d/gumu/obj/fengmi" : 2,
                      "/kungfu/class/gumu/yang" : 1,
               ]));

        else 
               set("objects", ([
                      "/d/gumu/obj/fengmi" : 2,                      
               ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
