inherit ROOM;

void create()
{
        set("short", "兵器室");
        set("long", @LONG
   這裡就是藥王谷的兵器室，裡面的兵器都是供藥王弟子平時
練功用的，竹刀竹劍應有盡有。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"tulu2",
]));

        set("objects", ([
        "/d/village/obj/zhujian" : 10,
//      WEAPON_DIR"zhui" : 60,
]));

        setup();
        replace_program(ROOM);
}
