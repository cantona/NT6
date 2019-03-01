

inherit ROOM;

void create()
{
        set("short", "打鐵舖");
        set("long", @LONG
這是一家簡陋的打鐵舖，中心擺著一個火爐，爐火把四周照得一片
通紅，你一走進去就感到渾身火熱。牆角堆滿了已完工的菜刀、鐵錘、
鐵棍、匕首、盔甲等物。一位鐵匠滿頭大汗揮舞著鐵錘，專心致志地在
打鐵。門口有一牌子(paizi)。
LONG
        );

        set("exits", ([
                "west" : __DIR__"xuanwu-1",
        ]));

        set("objects", ([
__DIR__"npc/tiejiang1" : 1,
        ]));
        set("item_desc", ([ /* sizeof() == 1 */
                "paizi" : "牌子上寫道：東西都在牆角堆著。\n"]));
        set("no_clean_up", 0);
        set("objects", ([
                "/d/gaoli/npc/tiejiang" : 1,
        ]));

        setup();
        replace_program(ROOM);
}

