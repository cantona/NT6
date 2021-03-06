// Room: /d/lingzhou/huilang.c

inherit ROOM;

void create()
{
        set("short", "迴廊");
        set("long", @LONG
這是連接前殿和後宮的迴廊，兩旁是硃紅的廊柱，廊頂是飛檐琉璃
瓦，地上鋪着白玉石板。西面通向西偏殿，北面打了個彎向東折向後宮。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
                "west"  : __DIR__"xidian",
                "east"  : __DIR__"yushanfang",
                "south" : __DIR__"ysdian",
                "north" : __DIR__"huilang2",
        ]));
        set("objects", ([
                __DIR__"npc/shiwei" : 4,
        ]));
        set("outdoors", "xixiagong");

        set("coor/x", -6265);
        set("coor/y", 2975);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}