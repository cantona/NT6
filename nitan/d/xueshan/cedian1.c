#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "側殿");
        set("long", @LONG
   這裡是雪山寺的東側殿。殿內有神態各異的十八羅漢塑像，金旒
玉鑲，很是莊嚴。
LONG );
        set("exits", ([
                "northup" : __DIR__"zoulang1",
                "west"    : __DIR__"dadian",
        ]));
        set("objects", ([
                CLASS_D("xueshan")+"/jiamu" : 1,
                __DIR__"npc/xiang-ke"       : 3,
        ]));
        setup();

}
int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((! myfam || myfam["family_name"] != "雪山寺")
           && dir=="northup"
           && objectp(present ("jiamu huofo", environment(me))))
          return notify_fail(CYN "嘉木活佛說道：爾非雪山寺弟"
                                   "子，不能入內。\n" NOR);

        return ::valid_leave(me, dir);
}