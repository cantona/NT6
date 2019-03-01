// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "沙灘");
        set("long", @LONG        
你走在沙灘之上，腳下是鬆軟的海沙。南邊是一艘大戰船，正停泊
在那裡。據說這是高麗的海面部隊之一，近來局勢混亂，高麗的戰船也
是嚴加戒備。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northwest" : __DIR__"shatan1",
                "south":__DIR__"jiaban",
        ]));
       setup();
        replace_program(ROOM);
}        
