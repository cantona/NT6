inherit ROOM;

void create()
{
      set("short", "武當柏林");
        set("long", @LONG
你穿行在一片茂密的柏林中，陰森鬱翠，怪石嶙峋，草深沒人。
不時地有兔子從你的身邊飛跑而過。
LONG );
      set("outdoors", "wudang");
      set("exits", ([
              "northdown": __DIR__"yuzhengong",
              "southup"  : __DIR__"haohanpo",
      ]));
      set("objects", ([
              "/clone/quarry/tu" : 2,
      ]));
        set("coor/x", -370);
        set("coor/y", -210);
        set("coor/z", 50);
        setup();
      replace_program(ROOM);
}