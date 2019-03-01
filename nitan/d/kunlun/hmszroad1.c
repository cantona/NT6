// Room: /d/kunlun/hmszroad1.c
// Last Modified by winder on Jun. 29 2001

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條昆侖山上到處可見的山路。只是這裡已到處可見梅樹，梅
花盛開時到處一片火紅，花香飄溢。
LONG        );
        set("exits", ([ /* sizeof() == 1 */
                "westup"    : __DIR__"hmszroad2",
                "southeast" : __DIR__"bayankala",
        ]));
        set("outdoors", "hongmei");
        set("no_clean_up", 0);
        set("coor/x", -90010);
        set("coor/y", 10010);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}