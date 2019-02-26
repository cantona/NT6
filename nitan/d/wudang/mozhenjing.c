#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "磨針井");
        set("long", @LONG
相傳當年真武進山修煉，日久思歸，偶遇一老婦持鐵杵研磨。問
磨杵為何？答以磨針。又問鐵杵豈能磨針？答雲功到自然成。真武由
此醒悟，終於修煉成仙。後人因建磨針井道觀以為紀念。殿前立大鐵
杵一根，殿旁有老母亭，亭正中有井。
LONG );
        set("exits", ([
                "west" : __DIR__"shanlu1",
        ]));
        set("item_desc",([ 
                "jing" : HIC "\n井沿古樸，水色悠藍，可以裝瓶飲用。\n\n" NOR,
        ]));
        set("resource/water", 1);
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -360);
        set("coor/y", -230);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}