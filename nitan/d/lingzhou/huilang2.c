// Room: /d/lingzhou/huilang2.c

inherit ROOM;

void create()
{
        set("short", "迴廊");
        set("long", @LONG
這是御花園外的迴廊，兩旁是硃紅的廊柱，廊頂是飛檐琉璃瓦，地
上鋪着白玉石板。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
                "south" : __DIR__"huilang",
                "north" : __DIR__"garden",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xixiagong");

        set("coor/x", -6275);
        set("coor/y", 2985);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}