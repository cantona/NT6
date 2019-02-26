#include <ansi.h>
inherit ROOM;

string look_pool();

void create()
{
      set("short", "洗象池");
        set("long", @LONG
洗象池原只是一亭，亭前有一個石砌的小池(pool)，池邊不遠就
是危巖。洗象池寓於一片冷杉林中，有若白雲深處的仙山瓊閣。若是
雲收霧斂、碧空萬里、月朗中天時，便覺萬籟俱寂，清光無限，宛若
身在天宮，徹體生涼。這正是著名的「象池池夜」。由此向南上攀，
便至雷洞坪，東下至蓮花石。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "eastdown"  : __DIR__"ztpo2",
          "southup"   : __DIR__"lingyunti",
      ]));
      set("item_desc", ([
          "pool" : (: look_pool :),
      ]));
      set("no_clean_up", 0);
        set("coor/x", -560);
        set("coor/y", -240);
        set("coor/z", 160);
        setup();
}

string look_pool()
{
    return WHT "\n這是一個石砌的六角小池，傳説普賢乘象至"
           "此，必先在此池沐\n浴其象，而後才升至金頂，故"
           "為「洗象池」。\n" NOR;
}