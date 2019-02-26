// Room: /d/taishan/duzunju.c
// Last Modified by Winder on Aug. 25 2001
// Modified by Zeratul Jan 11 2001 江湖閲歷低於10000不能見盟主

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "獨尊居");
        set("long", @LONG
這裏是處於岱頂後山的天下大宗師居所。青竹扎就的居所，東西兩
面開着窗户，窗外還是青綠的竹林和林間透進的白雲。北面牆上是一幅
中堂，痛快淋漓地三個大字草書：[31;1m
                            大
                            宗
                            師[0m
    大宗師在這裏會見天下的英豪，品評他們的武功。如果你願意接受
品評，就問問大宗師，看他是否願意出手吧。不過要小心，生死與天神
巫師不相干的哦。
LONG );
        set("exits", ([
                "out" : __DIR__"fengchan",
        ]));
        set("objects",([
                "/clone/npc/dazongshi" : 1,
        ]));
        set("coor/x", 410);
        set("coor/y", 650);
        set("coor/z", 120);
        setup();
        replace_program(ROOM);
}
