// 書房 shufang.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "書房");
        set("long", @LONG
這裡是胡青牛的書房，靠牆邊有個大書櫃，一排一排的書架上分
門別類地擺放著各種各樣的醫學書籍，連失傳已久的《黃帝蝦嫫經》、
《西方子明堂灸經》、《太平聖惠方》、《灸甲乙經》、《千金方》、
《此事難知》也在其中，書櫃正對著一個書桌，上面擺放著一個筆筒，
筆筒旁邊擱著一本打開的書。
LONG );

        set("exits", ([
            "west" : __DIR__"xfang3",
        ]));

        setup();
}