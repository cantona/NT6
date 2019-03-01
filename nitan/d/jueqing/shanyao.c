inherit ROOM;

void create()
{
        set("short", "山腰");
        set("long", @LONG
此處陽光照耀，地氣和暖，情花開放得早，這時已結了果
實。但見果子或青或紅，有的青紅相雜，還生著茸茸細毛。翹
首遠望，但見絕情峰上雲霧繚繞，壯觀之極。
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "west"      : __DIR__"shanlu1",
               "eastup"    : __DIR__"qinghuaao",
        ]));

        set("objects", ([
                __DIR__"npc/dizi2" : 2,
        ]));  

        set("no_clean_up", 0);

        setup();
}

int valid_leave(object me, string dir)
{
        object guard;

        if (dir != "eastup"
           || ! objectp(guard = present("lvshan shaonv", this_object())))
                return ::valid_leave(me, dir);

        return guard->permit_pass(me, dir);
}