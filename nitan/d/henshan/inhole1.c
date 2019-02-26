inherit ROOM;

void create()
{
        set("short", "水簾洞內");
        set("long", @LONG
這裏是水蓮洞內洞，雖然不如外洞高，但也甚為寬敞，此處靠近
外洞還隱隱地聽得見瀑布落下拍打在石頭上的聲音。走到這裏入口便
一分為二，出現兩個洞口。從這裏看去洞口漆黑無光，令人不禁有些
心寒。
LONG );

        set("exits",([
              "northwest" : __DIR__"inhole2",
              "northeast" : __DIR__"inhole3",                
              "out"       : __DIR__"inhole",              
        ]));        
                     
       setup();
       replace_program(ROOM);
}