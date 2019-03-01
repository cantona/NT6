// fu-datang 富家大堂
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "富家大堂");
        set("long", @LONG
這裡是侯員外家的大堂，堂樑上掛著一塊匾(bian)。堂內擺
放著一些八仙桌和椅子，堂壁上梅蘭竹菊的竹簾被掛成了蘭竹菊
梅，看來這家也不過是附庸風雅的暴發戶而已。
LONG
        );
        set("exits", ([
                "east" : __DIR__"fu-ceting",
                "west" : __DIR__"fu-zhangfang",
                "north" : __DIR__"fu-xiaoyuan",
                "south" : __DIR__"fu-houyuan",
        ]));
        set("item_desc", ([
           "bian": HIR"
＃＃＃＃＃＃＃＃＃＃＃＃＃
＃＃　　　　　　　　　＃＃
＃＃　忠　義　傳　家　＃＃
＃＃　　　　　　　　　＃＃
＃＃＃＃＃＃＃＃＃＃＃＃＃
"NOR
        ]) );
        set("no_clean_up", 0);
        set("coor/x", -12240);
	set("coor/y", 780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}