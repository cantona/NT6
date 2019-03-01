//room: shoushe.c
inherit ROOM;

void create()
{
        set("short","獸舍");
        set("long", @LONG
這裡是丐幫弟子的獸舍。這裡豢養了各種猛獸，以供出道的丐幫
弟子使用。獸舍裡猛獸長聲嘶嚎，老遠都聽得見。尤其是夜晚聽來，
更有是撕心裂肺的慘烈。獸舍裡養了一群豬(pig) ，看來是前程不是
很遠大。
LONG );
        set("exits",([
                "east"  : __DIR__"pomiao",
        ]));
        set("outdoors", "yangzhoue");
        set("item_desc",([
                "pig":
"   ^..^  ^. .^   ^..^   ^..^ ^..^ ^　^  ^..^         ^..^ ^qp^  ^cc^  ^@@^
   (oo) ( o o )  (OO)  (oo ) (@@) (oo)         (00)  (qp) (oo)  (oo)  (oo)

    豬   肥豬   澎恰恰 牙痛  台灣 睡豬 黑暗中 仰泳中 感冒 哭泣 有斜視 近視豬
                型的豬 的豬  土豬       的豬   的豬  的豬 的豬  的豬
",
        ]));
        set("objects",([
                "/d/baituo/npc/fox" :1,
                "/d/baituo/npc/wolf" :1,
                "/d/baituo/npc/tiger" :1,
                "/d/baituo/npc/lion" :1,
        ]));
        set("coor/x", 60);
        set("coor/y", 60);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}