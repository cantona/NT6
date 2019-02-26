//Room: taiziyan.c 太子巖
//Date: Sep 22 1997

inherit ROOM;

void create()
{
      set("short","太子巖");
        set("long", @LONG
這裏是羣山環抱中的太子巖，巖上有一塊三清石和一座太子亭。
LONG );
      set("exits",([ /* sizeof() == 1 */
           "northdown":__DIR__"shanlu4",
          "southdown": __DIR__"langmeiyuan",
      ]));
      set("outdoors", "wudang");
      set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -310);
        set("coor/z", 110);
        setup();
      replace_program(ROOM);
}