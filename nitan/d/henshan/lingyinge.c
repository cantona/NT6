#include <ansi.h>
inherit ROOM;

string look_duilian();

void create()
{
        set("short", "鈴音閣");
        set("long", @LONG
此處是衡陽城唯一出售樂器的地方，店舖門口掛滿了風鈴，微風
吹過，玲音入耳，精神便為之一爽。進入店內，只見貨櫃上擺滿了各
色樂器，琳琅滿目，據說這裡的老板娘以前是個歌妓，雖然現在做起
樂器生意，但偶爾也會拂琴高歌，每次都會引來很多的路人駐足欣賞。
門前掛著一幅對聯(duilian)。
LONG );
        set("objects", ([
                __DIR__"npc/feiyan" : 1,
        ]));

        set("exits", ([
                "south" : __DIR__"hengyang11",
        ]));

        set("item_desc", ([
                "duilian" : (: look_duilian :),
        ]));

        set("no_fight", 1);

	set("coor/x", -6910);
	set("coor/y", -5690);
	set("coor/z", 0);
	setup();
                
}        

void init()
{
        tell_object(this_player(), HIW "\n你一走進玲音閣，風鈴被你走路所帶動"
                                   "的風吹得「叮叮」作響。\n\n" NOR);        
}

string look_duilian()
{
        return
        HIC "\n"
        "       ※※※※※※※         ※※※※※※※\n"
        "       ※※※※※※※         ※※※※※※※\n"
        "       ※※      ※※         ※※      ※※\n"
        "       ※※" HIW "　流　" HIC "※※         ※※" HIW "  空  " HIC "※※\n"
        "       ※※　 　 ※※         ※※      ※※\n"
        "       ※※" HIW "  泉  " HIC "※※         ※※" HIW "  谷  " HIC "※※\n"
        "       ※※      ※※         ※※      ※※\n"
        "       ※※" HIW "  水  " HIC "※※         ※※" HIW "  寂  " HIC "※※\n"
        "       ※※      ※※         ※※      ※※\n"
        "       ※※" HIW "  雲  " HIC "※※         ※※" HIW "  寞  " HIC "※※\n"
        "       ※※      ※※         ※※      ※※\n"
        "       ※※" HIW "  清  " HIC "※※         ※※" HIW "  天  " HIC "※※\n"
        "       ※※      ※※         ※※      ※※\n"
        "       ※※" HIW "  音  " HIC "※※         ※※" HIW "  賴  " HIC "※※\n"
        "       ※※      ※※         ※※      ※※\n"
        "       ※※" HIW "  幽  " HIC "※※         ※※" HIW "  絕  " HIC "※※\n"
        "       ※※      ※※         ※※      ※※\n"
        "       ※※" HIW "  蘭  " HIC "※※         ※※" HIW "  音  " HIC "※※\n"
        "       ※※    　※※         ※※      ※※\n"
        "       ※※※※※※※         ※※※※※※※\n"
        "       ※※※※※※※         ※※※※※※※\n\n" NOR;
}