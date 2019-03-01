// canglong.c

inherit ROOM;

void create()
{
        set("short", "蒼龍嶺");
        set("long", @LONG
華山五峰中最驚險的是北峰，北峰之上最陡峭的則是蒼龍嶺。此
嶺高約百米，寬僅一米，而登山之路則在其山脊之上，兩側脊坡光滑
挺拔，其下懸崖深邃，雲濤隱伏，嶺體蜿蜒逶迤，體青背黑，如蒼龍
騰空，故有是名。嶺側有一石碑(shibei)。    從這裡往東是下山的
路，再往南是上其它四峰的路，西面是華山極險處之一，叫做『舍身
崖』。
LONG );
        set("exits", ([ /* sizeof() == 3 */
            "eastdown"  : __DIR__"shangtianti",
            "northup"   : __DIR__"yuntai",
            "westup"    : __DIR__"sheshen",
        ]));
        set("item_desc", ([
                "shibei" :
"石碑刻著幾個大字：「韓退之投書處」，據說當年韓癒爬上此嶺之後，再\n"
"也不敢下來，自以為要死在山上，就在山上寫信投下來，和家人訣別。後\n"
"來還是華陰縣的縣官派人上山拿繩子把他捆著吊下來的。\n"
])  ) ;
        set("objects", ([
            __DIR__"npc/liang-fa" : 1,
        ]));
        // set("no_clean_up", 0);
        set("outdoors", "huashan");

        setup();
        replace_program(ROOM);
}
 