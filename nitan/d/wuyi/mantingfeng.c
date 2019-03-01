// Room: /d/wuyi/mantingfeng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "幔亭峰");
        set("long", @LONG
大王峰北側的幔亭峰，俗稱鐵佛峰，為仙家招宴之所。此峰丹霞峻
拔，蒼鬆環簇，宛如一個巨大的翠屏。山的半壁“幔亭”二字，為明代
吳思學所書。山頂地勢平坦，中有一塊狀如香鼎的巨石，名叫宴仙壇。
相傳武夷君和皇太姥、魏王子騫在此設幔亭宴會鄉人。“幔亭”之名由
此而來。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "north"     : __DIR__"huanguyan",
                "southdown" : __DIR__"path3",
        ]));
        set("objects", ([
                "/d/taishan/npc/shu-sheng" : 1,
        ]));
        set("coor/x", 1390);
        set("coor/y", -4970);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
