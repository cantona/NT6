inherit ROOM;

void create()
{
        set("short", "湖邊小路");
        set("long", @LONG
這是聖湖邊的小路。路側的湖水極為清澈。陽光下映着白頂雪山
顯出一片藍幽幽的寧靜。但是周圍卻是被極濃的霧氣所籠罩，使你的
眼前一片朦朧，瞧不清四周。
LONG );
        set("outdoors", "xuedao");
        set("exits", ([
                "west" : __DIR__"shenghu",
                "east" : __DIR__"hubian2",
        ]));
        setup();
}