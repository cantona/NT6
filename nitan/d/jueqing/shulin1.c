inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這裏山青水碧，景色極盡清幽，只是四下寂無聲息，隱隱
透著兇險，偶爾卻可隱約聽見溪流飛瀑之聲迴盪于山谷。 
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "northup"   : __DIR__"shuitang",
               "southdown" : __DIR__"shanjiao",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}