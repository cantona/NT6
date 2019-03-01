#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
        set("short", "太湖湖畔");
        set("long", @LONG
太湖處江浙之間。她襟帶三江，東南之水盡匯于此，周行五百裡，
古稱五湖。矗立湖 (river)岸，唯見長天遠波，放眼皆碧，七十二峰
蒼翠挺立在三萬六千頃波濤之中，使人心襟大開直欲仰天長嘯，方能
表此喜樂。
LONG );
        //set("arrive_room", "/d/yanziwu/bozhou");
        set("to", __DIR__"bozhou");
        set("exits", ([
                "northeast" : "/d/suzhou/road5",
        ]));
        set("objects", ([  
                __DIR__"npc/yufu" : 1,
        ]));  

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("outdoors", "yanziwu");
        setup();
        replace_program(RIVER);
}
