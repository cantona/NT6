inherit ROOM;

void create()
{
      set("short", "中峰寺");
        set("long", @LONG
中峰寺在白雲峰下，始建于晉代，原為道觀。傳說觀內的道人每
年在三月三日都獻身給山中一條大蟒，以為可升仙。後來有個從資州
來的明果禪師，殺了那條大蟒，道士們始知上當，感激不已，自願改
信佛教，從此改觀為寺。這裡往北可到清音閣，東下至神水庵。
LONG );
      set("objects", ([
               __DIR__+"npc/guest": 1,
      ]));
      set("exits", ([
          "west"     : __DIR__"qingyinge",
          "eastdown" : __DIR__"shenshuian",
      ]));
      set("outdoors", "emei");
        set("coor/x", -450);
        set("coor/y", -230);
        set("coor/z", 80);
        setup();
      replace_program(ROOM);
}