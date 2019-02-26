// Room: /d/songshan/shandao6.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "峻極山道");
        set("long", @LONG
你走在嵩山峻極山道上，青松翠柏，山風嵐霧，時來飄蕩。遠望山
下犬吠雞啼，頓起仙凡之感。上面就是嵩山峻極禪院。
LONG );
        set("exits", ([
                "northup"   : __DIR__"junjigate",
                "southdown" : __DIR__"chaotian",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "songshan");
        set("coor/x", -20);
        set("coor/y", 840);
        set("coor/z", 70);
        setup();
        replace_program(ROOM);
}