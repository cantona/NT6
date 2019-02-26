// Room: /d/kunlun/hmszroad2.c
// Last Modified by winder on Jun. 29 2001

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條崑崙山上到處可見的山路。只是這裏已到處可見梅樹，梅
花盛開時到處一片火紅，花香飄溢。西邊是紅梅山莊。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
                "westup"   : __DIR__"hmszhuang",
                "eastdown" : __DIR__"hmszroad1",
        ]));
        set("outdoors", "hongmei");
        set("no_clean_up", 0);
        set("coor/x", -90020);
        set("coor/y", 10010);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}