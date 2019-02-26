// rope.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "繩牀");
        set("long", @LONG
一條掛在側廂中的細麻繩。
LONG );
        set("no_clean_up", 0);
        set("coor/x", -3180);
        set("coor/y", -40);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}
