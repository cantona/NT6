// Room: /d/shaolin/wuqiku.c
// Date: YZC 96/01/19

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "武器庫");
        set("long", @LONG
少林寺的武器庫可稱天下第一，十八般兵器，這裡可謂應有盡有。
四面一望，令你頓感眼花繚亂。牆上砌了一個個小格子，每個都插滿
了各種各樣的兵器。牆角一個健壯的僧人正乒乒乓乓地在打造一根禪
杖。另一位灰衣僧人正在牆角拂拭一把戒刀。看到你進來，他緩緩起
身，向你迎了過來。
LONG );
        set("exits", ([
                "west" : __DIR__"zhulin2",
                "north" : __DIR__"fangjuku",
        ]));

        create_door("west","木門","east",DOOR_CLOSED);
        set("objects",([
                CLASS_D("shaolin") + "/dao-chen" : 1,
                __DIR__"npc/datie-seng" : 1,
                __DIR__"obj/zhujian" : 1,
                __DIR__"obj/mudao" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
}
