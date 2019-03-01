// Room: /d/shaolin/zhonglou4.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "鐘樓四層");
        set("long", @LONG
到這裡樓梯大概只能容一人上下，牆身也略薄了些。視線越過窗
欞，南邊的練武場，羅漢堂，般若堂歷歷在目，不少僧人正匯集在練
武場上習武，吆喝聲一陣陣傳進耳鼓。北邊的藏經樓，方丈樓也盡露
全貌。
LONG );
        set("exits", ([
                "up" : __DIR__"zhonglou5",
                "down" : __DIR__"zhonglou3",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
