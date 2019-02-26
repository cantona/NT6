//Room: bed.c

inherit ROOM;

void create()
{
        set("short", "牀上");
        set("long", @LONG
一張白色的軟榻，看上去極為精緻，紗衾鴛枕之間散發出一絲絲
幽香．
LONG );
        set("exits", ([
                "out": "/d/changan/kzsleep",
        ]));
        set("no_fight", 1);
               set("no_magic", 1);
        set("sleep_room",1);
        set("if_bed",1);

        setup();
        replace_program(ROOM);
}
