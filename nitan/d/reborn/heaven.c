#include <ansi.h>
inherit ROOM;

#define FO  "/adm/npc/buddha"
void create()
{
        set("short", HIY "【極樂世界】" NOR);
        set("long", HIW @LONG
這裏是西方極樂世界，是佛祖和他的弟子聚居之所在。
到處都是雲海，霞光閃閃，金光四溢，説不出的莊嚴宏偉。
佛祖釋迦牟尼端坐在正中央，周圍是形態各異的五百羅漢。
佛祖形象十分偉岸，你覺得自己還不及佛祖一個腳趾高。
LONG NOR );
/*        set("exits", ([
                "down" : __DIR__"tianmen",
]));*/
        set("sleep_room", 1);
        set("no_fight", 1);       
        set("no_magic", 1);
        set("no_bid", 1);
        setup();  
        load_object(FO)->move(this_object());
      
}
