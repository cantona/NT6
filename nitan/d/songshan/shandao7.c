// Room: /d/songshan/shandao7.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "極頂山道");
        set("long", @LONG
你走在嵩山極頂山道，青松翠柏，山風嵐霧，時來飄蕩。遠望山下
犬吠雞啼，頓起仙凡之感。西上就是封禪台了。
LONG );
        set("exits", ([
                "eastdown" : __DIR__"junjigate",
                "westup"   : __DIR__"shandao8",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "songshan");
        set("coor/x", -23);
        set("coor/y", 850);
        set("coor/z", 83);
        setup();
        replace_program(ROOM);
}