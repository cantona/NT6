inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short","居室");
        set("long",@LONG 
這是齊自勉的房間。齊自勉性格風雅，為人飄逸。牆上掛著
李白的《將進酒》，是齊自勉親手所書，字跡豪放奔放，走的是
張旭狂草的路子，從這依稀也能看出主人武功的性情。照壁上一
幅《雪月夜行圖》，是他當年一夜奔波八百裡，滅掉太行三十寨
的榮事。桌上燃著一束檀香，散發出恬靜的氣息。一張焦尾琴擺
在桌上，主人正在自斟自飲，自得其樂。
LONG);
        set("exits", ([
                    "north"  : __DIR__"zoulang4", 
        ]));
        set("objects", ([  
                __DIR__"npc/qi" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
