inherit ROOM;

void create()
{
        set("short", "鯉魚脊");
        set("long", @LONG
這是華山著名的險地『鯉魚脊』。只見一條長約二十余丈，寬僅
數尺的小徑直達對峰，兩旁皆是雲霧縈繞，深不見底的峽谷，罡風吹
過，使人飄飄若起，武林高手平時也不敢冒險越過此處。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "south"   : __DIR__"laojun",
                "northup" : __DIR__"houzhiwangyu",
        ]));
        set("objects", ([ 
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "huashan" );
        setup();
        replace_program(ROOM);
}
