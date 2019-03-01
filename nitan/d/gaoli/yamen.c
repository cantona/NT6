// /d/gaoli/yamen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "城防衙門");
        set("long", @LONG
這裡是高麗的城防衙的官衛房，大概有三丈見方，中間有張長案，
一位將軍在這裡辦公，這裡主要負責高麗城的防務安全，以及防盜，防
火，捉拿逃犯等事物。 
LONG
        );
set("exits", ([
                "west":__DIR__"yudao4",
//                "east": "/d/clone/room/cityroom/gaoli"    
        ]));
     set("objects",([
       __DIR__"npc/guanbingc":3,
       ]));
       setup();
        replace_program(ROOM);
}        
