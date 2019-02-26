inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short","居室");
        set("long",@LONG 
這裏與其説是一間卧室，不如説是一間練功室。地上鋪滿了
渾圓的黃豆，怎麼也站不住。室內立了八根梅花樁，一名身掛披
風的男子正在上面縱躍如飛，看得人眼花繚亂。他正是凌霄城的
六代弟子汪萬翼。他的輕功卓絕，在凌霄城數一數二，甚至與白
自在不相上下，誰也不知道他是怎麼學上來的，也許可以向他問
問這件事。
LONG);
        set("exits",([
                    "north"  : __DIR__"zoulang1", 
        ]));
        set("objects", ([  
                __DIR__"npc/wang-wanyi" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
