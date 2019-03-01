inherit ROOM;

#include <ansi.h> 

void create()
{
        set("short","後園");
        set("long",@LONG 
這裡是凌霄派的後園。小橋流水，菏塘低閣。層台聳翠，上
出重霄。飛閣流丹，下臨無地。在這萬裡雪山之上，象這種溫暖
如春的地方，實不多見，也難怪當年凌霄祖師要建派于此了。菏
塘中的一方假山上，一縷清泉汩汩流出，霧氣藹藹，如夢如幻。
LONG);
        set("outdoors", "lingxiao");
        set("objects", ([
                CLASS_D("lingxiao") + "/first" : 1,
        ]));
        set("exits", ([
            "north"  : __DIR__"houyuan2",  
            "south"  : __DIR__"zhongting", 
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
