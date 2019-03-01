inherit ROOM;

void create()
{
          set("short", "戲鳳閣");
        set("long", @LONG
這裡是靈鷲宮弟子練功的地方。有幾個妙齡女子正在專心致致地
練武，有幾個手持竹劍，在互相拆招，身法靈動，猶如穿花蝴蝶一般，
你不禁看花了眼，別的人則坐在地上的蒲團上苦練內力。
LONG );
          set("exits",([
                      "west" : __DIR__"changl4",
                      "up"   : __DIR__"liangong2",
          ]));
          set("for_family", "靈鷲宮");
          setup();
          replace_program(ROOM);
}