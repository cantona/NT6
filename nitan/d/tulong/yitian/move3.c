#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這是一片茂密的樹林，北面就是萬安寺了，到處都是親兵，守備很是深嚴。
LONG );

        set("outdoors", "beijing");
        setup();
}