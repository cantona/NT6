// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "沙灘");
        set("long", @LONG        
你走在沙灘之上，腳下是鬆軟的海沙。南邊是一望無際的大海。遠
遠望去，還有幾艘大船停泊在岸邊，在海浪的衝擊下不住的搖晃。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northwest" : __DIR__"dadao9",
                "southeast":__DIR__"shatan2",
        ]));
       setup();
        replace_program(ROOM);
}        
