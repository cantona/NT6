// Room: /d/mingjiao/shanlu1.c
// Date: Java 97/04/9

inherit ROOM;

void create()
{
        set("short", "青石階");
        set("long", @LONG
這裡已是半山腰了。不遠的前面有一座竹亭，幾位劍客在這裡歇
息。山路到這裡更加陡峭，四下望去，層巒迭嶂，滿目滴翠遠山披銀
裝，雲海現奇觀。
LONG );
        set("exits", ([
                "eastdown" : __DIR__"shanmen",
                "westup" : __DIR__"shanlu2",
        ]));
        set("objects",([
             "/d/taishan/npc/jian-ke": 3,
             "/d/taishan/npc/dao-ke" : 2,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}
