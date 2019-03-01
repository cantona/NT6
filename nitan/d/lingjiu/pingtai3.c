inherit ROOM;

void create()
{
          set("short", "山間平台");
        set("long", @LONG
這是失足巖左側的一塊大平台，平台周圍聚滿了人。左邊通向靈
鷲宮的必經之路，山道被一塊鷹喙突出的巨巖截斷，巨巖光可鑒人，
只有中間一條窄窄的石階通向山道的那一頭。你身後不遠處堆著幾叢
稻草，有幾個武林人士正躺在上面呼呼大睡。你看了也不禁想走過去
休息一會兒。
LONG );
        set("sleep_room", 1);
        set("no_fight", 1);
        set("outdoors", "lingjiu");
        set("exits",([
                "north" : __DIR__"shandao",
        ]));

        setup();
        replace_program(ROOM);
}