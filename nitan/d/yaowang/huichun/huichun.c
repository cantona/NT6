
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "回春堂" );
        set("long",
"你走進這裏就聞到濃重的藥味，門上高高的掛着一塊匾額"HBRED HIY"〖回春堂〗\n"NOR
"這裏就是天下聞名的回春堂藥局了，回春堂是藥王谷在佛山開設的藥局\n"
"出售藥王谷炮製的藥材。牆上掛着一個牌子(paizi)。\n"
);

        set("item_desc", ([
                "paizi" : YEL"本藥局出售各種藥材，另招收零工夥計。\n\n"
                                "看病、療傷的請到正廳。\n"
                                "買藥的請到南廳。\n"
                                "打工的請到北廳。\n"NOR,
        ]));
        set("exits", ([
        "north" : "/d/foshan/street1",
        "west" : __DIR__"tingyuan",
        ]));
        set("objects", ([
                __DIR__"npc/huoji" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
