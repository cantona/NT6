//LUCAS 2000-6-18
// walle2.c

inherit ROOM;

void create()
{
        set("short", "城頭");
        set("long", @LONG
遠山渺渺，冷風蕭蕭。試拂鐵衣，只見衣色似雪，在這凌霄
之處，惟有雨雪連綿，以陪弋人。大漠蒼蒼，遠空一鷹高翔，振
翅直飛九霄，忽而又直衝而下，翱翔九天，瞬間無蹤，只有白雲
千載，仍在這座孤城上悠悠飄蕩。
LONG );
        set("outdoors", "lingxiao");
        set("no_clean_up", 0);

        set("exits", ([
                "west" : __DIR__"walle2",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 1,
        ])); 
        setup();
        replace_program(ROOM);
}
