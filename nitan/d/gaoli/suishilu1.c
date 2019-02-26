// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "碎石路");
        set("long", @LONG        
這裏是一條碎石路，北邊是一條寬敞的青石路。這裏綠樹環繞，空
氣清新。從這裏可以隱約聽到敲鐘的聲音，看來不遠處有一個寺院。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northeast" : __DIR__"dadao9",
                "west":__DIR__"suishilu2",
               ]));
       setup();
        replace_program(ROOM);
}        
