inherit ROOM;

void create()
{
          set("short", "戲鳳閣二樓");
        set("long", @LONG
這裏是靈鷲宮弟子練功的地方。有幾個妙齡女子正在專心致致地
練武，有幾個手持竹劍，在互相拆招，身法靈動，猶如穿花蝴蝶一般，
你看了也忍不住躍躍欲試。
LONG );
          set("exits",([
                      "down" : __DIR__"liangong",
                      "up"   : __DIR__"liangong3",
          ]));
          set("for_family", "靈鷲宮");
          setup();
          replace_program(ROOM);
}