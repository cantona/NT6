// Room: /wuliang/shanlu4.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "棧道");
        set("long", @LONG
這是一段建在山坡脊上的棧道。雲貴一帶常有這樣的棧道，這段
棧道不過因坡而建，雖然山風吹拂，枝木搖響，可是一點履險意味都
沒有。
LONG );
        set("outdoors", "wuliang");
        set("no_clean_up", 0);
        set("exits", ([
                "westdown" : __DIR__"shanlu3",
                "northup"  : __DIR__"shanlu5",
        ]));
        set("coor/x", -70990);
        set("coor/y", -79990);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}