inherit ROOM;

void create()
{
          set("short", "戲鳳閣三樓");
        set("long", @LONG
這裏是三樓，人比樓下的少多了，只聽見樓下隱隱約約的傳來陣
陣嬌吒，不那麼真切。
LONG );
          set("exits",([
                      "down" : __DIR__"liangong2",
          ]));
          set("for_family", "靈鷲宮");
          setup();
          replace_program(ROOM);
}