inherit ROOM;

void create()
{
          set ("short", "官道");
          set ("long", @LONG
這是一條由官府舖設的道路，可容八馬並驅。是南北交通
要道。行人明顯多了，不時還有騎馬的和趕車的經過。
LONG);

          set("outdoors", "zhongzhou");
          set("exits", ([
                  "south" : __DIR__"beimen",
                  "north" : __DIR__"guandao6",
        ]));
          setup();
}