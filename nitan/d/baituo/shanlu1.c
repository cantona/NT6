inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裡是白駝山莊廣場西邊的一條小路，尋常百姓平時都是經過這
條小路上山。
LONG );
          set("exits", ([
                      "north" : __DIR__"shulin",
                      "south" : __DIR__"shanlu",
             ]));
          set("outdoors", "baituo");
          set("objects", ([
                      __DIR__"npc/qiaofu" : 1 ,
              ]));
          set("coor/x", -49990);
        set("coor/y", 19990);
        set("coor/z", 0);
        setup();
          replace_program(ROOM);
}