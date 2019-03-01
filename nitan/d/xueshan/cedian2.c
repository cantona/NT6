#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "側殿");
        set("long", @LONG
這裡是雪山寺的西側殿。這裡的牆壁上描繪著佛祖傳道的故事，
佛祖手拈金花寶相莊嚴。
LONG );
        set("exits", ([
                "northup" : __DIR__"zoulang2",
                "east"    : __DIR__"dadian",
        ]));
        set("objects", ([
                CLASS_D("xueshan")+"/samu" : 1,
                __DIR__"npc/xiang-ke" : 3,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((! myfam || myfam["family_name"] != "雪山寺")
           && dir=="northup"
           && objectp(present ("samu huofo", environment(me)))) 
                return notify_fail(CYN "薩木活佛說道：你非雪山寺"
                                   "弟子，不得入內。\n" NOR);

        return ::valid_leave(me,dir);
}