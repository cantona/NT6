// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "碎石路");
        set("long", @LONG        
這裏是一條碎石路，這裏已經是高麗城的南郊了。西邊有一片草地。
從這裏向西望去，可以看到一個寺廟了。不時有上香的人從你的身旁走過。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"suishilu1",
                "northwest":__DIR__"caodi1",
               ]));
       setup();
        replace_program(ROOM);
}        
