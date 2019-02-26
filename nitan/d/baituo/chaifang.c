inherit ROOM;

void create()
{
          set("short", "柴房");
        set("long", @LONG
這是間不寬的柴房，木柴已經快燒光了，剩餘的幾堆乾柴亂七八
糟擺放在地面，牆角放着一柄柴刀。
LONG );
          set("exits", ([
                      "west" : __DIR__"chufang",
          ]));
          set("objects", ([
                    // "/d/wudu/obj/ganchai"   : 2,
                    "/clone/weapon/chaidao" : 1,
                "/d/baituo/npc/laocai" : 1,
          ]));
         set("coor/x", -49970);
        set("coor/y", 20050);
        set("coor/z", 30);
        setup();
         replace_program(ROOM);
}