// Code of JHSH
// room: bshantan.c 碧水寒潭

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "碧水寒潭");
        set("long", @LONG
此處只見一個深潭，潭水呈碧綠色。因地處山陰，常年北風颳過，
只到潭邊一站，已然寒氣逼人。表面潭水早已結成厚冰，只有幾個人
工鑿去的缺口，望下去碧沉沉地，深不見底。
LONG );

        set("exits", ([
                "east" : __DIR__"tohsq3",
        ]));
        set("outdoors", "mingjiao" );
        set("cost", 3);

        setup();
        replace_program(ROOM);
}