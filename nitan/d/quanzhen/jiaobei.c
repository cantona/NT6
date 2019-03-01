// jiaobei.c 教碑
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "教碑");
        set("long", @LONG
這裏是全真教的教碑所在地，路旁立着一塊大碑(bei)。再往東
走就是天下聞名的道家玄門正宗--全真教的大門了。北面有一條石
階，不知道通向哪裏，往西是下山的路。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "south"   : "/d/quanzhen/dajiaochang",
                "northup" : __DIR__"shijie6",
                "eastup" : __DIR__"damen",
                "west" : __DIR__"shijianyan",
        ]));
        set("item_desc", ([
        "bei": CYN"
        ＊＊＊＊＊
　　　　＊　　　＊
　　　　＊　全　＊
　　　　＊　　　＊
　　　　＊　真　＊
　　　　＊　　　＊
　　　　＊　古　＊
　　　　＊　　　＊
　　　　＊　教　＊
　　　　＊　　　＊
　　　　＊＊＊＊＊
\n"NOR
        ]) );

        set("objects",([
                CLASS_D("quanzhen") + "/zhou" : 1,
        ]));
        set("coor/x", -3140);
        set("coor/y", 110);
        set("coor/z", 160);
        setup();
        replace_program(ROOM);
}