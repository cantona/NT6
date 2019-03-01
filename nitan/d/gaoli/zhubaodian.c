// /d/gaoli/zhubaodian
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "珠寶店");
        set("long", @LONG
這是一家專門出售貴重寶物的珠寶店。整個珠寶店設計的古香古色，
別具特色。你看這各種奇珍異寶不禁眼花繚亂，流連忘反。
LONG
        );
set("exits", ([
                "east":__DIR__"zhuque-1",   
        ]));
      set("objects", ([
                "/d/gaoli/npc/zhu" : 1,
        ]));
       setup();
        replace_program(ROOM);
}
