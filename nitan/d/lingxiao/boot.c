#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裡是一座大山的山麓，抬頭仰望，山上積雪皚皚，在日光
下映得閃爍生輝。山上雲海迷茫，雪峰林立，陽光交輝在白雲與
飛雪之間，隱隱能看見有一座城在山頂。路旁有一塊木板(sign)。
LONG );

        set("item_desc", ([
                "sign": HIW "\n\n    萬  古  凌  霄  一  羽  毛\n\n" NOR "\n"
        ]) );
        set("exits",([
                "southeast"  : "/d/xuedao/sroad1",
                "westup"  : __DIR__"sroad1",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 2,
        ]));
        set("outdoors", "lingxiao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
