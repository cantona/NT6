// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "寺院");
        set("long", @LONG        
這裏是一座寺院，抬頭可以看到一個大匾，上面寫着：靈靜寺。這
是中原的僧人在這裏掌管的寺院，以在高麗宣揚佛法。裏面傳來了陣陣
的誦佛之聲，聲音悠揚久遠，經久不息。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"caodi1",
                "enter":__DIR__"baodian",
               ]));
       set("objects",([
         __DIR__"npc/sengren":1,
         ]));
       setup();
        replace_program(ROOM);
}        
