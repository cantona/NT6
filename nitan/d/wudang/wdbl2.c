//Room: wdbl2.c 武當柏林
//Date: Sep 22 1997

inherit ROOM;

void create()
{
        set("short","柏林");
        set("long",@LONG
你穿行在一片茂密的柏林中，陰森鬱翠，怪石嶙峋，草深沒人。有
幾個伐木道士正在奮力砍(chop)樹，不時地驚起兔子從你的身邊飛跑而
過。
LONG);
        set("objects", ([
                __DIR__"obj/cypress" : 1,
                CLASS_D("wudang")+"/famu" : 1,
        ]));
        set("outdoors", "wudang");
        set("exits",([ /* sizeof() == 1 */
                "west"     : __DIR__"wdbl",
        ]));
        set("coor/x", -2050);
        set("coor/y", -820);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}